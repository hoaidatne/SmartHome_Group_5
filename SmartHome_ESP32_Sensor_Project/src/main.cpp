#include <WiFi.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <FirebaseESP32.h>

// Định nghĩa chân kết nối
#define DHTPIN 4
#define DHTTYPE DHT22
#define LDR_PIN 34
#define TRIG_PIN 12
#define ECHO_PIN 13
#define MQ2_PIN 35

// Wi-Fi cấu hình
const char* ssid = "Wokwi-GUEST";
const char* pass = "";

// Firebase cấu hình
#define FIREBASE_HOST "https://smarthomenhom5-f0d22-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyDTOpVjmPkXaxVx7eCSAFPyhslvHwEIpn0"

DHT dht(DHTPIN, DHTTYPE);
FirebaseData fbdo;

unsigned long previousMillis = 0;
const long readInterval = 2000;


float lastTemperature = -1;
float lastHumidity = -1;
int lastLDRValue = -1;
float lastDistance = -1;

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  if (distance < 2 || distance > 400) {
    return -1;
  }
  return distance;
}

void setup() {
  Serial.begin(115200);
  Serial.println("===================================");
  Serial.println("ESP32 IoT System Starting...");
  Serial.println("===================================");

  dht.begin();
  Serial.println("DHT22 Sensor Initialized");
  analogReadResolution(12);  // ESP32 hỗ trợ ADC 12 bit (0-4095)
  pinMode(LDR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  Serial.println("I/O Pins Configured");

  Serial.print("Connecting to WiFi: ");
  WiFi.begin(ssid, pass);
  unsigned long wifiTimeout = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - wifiTimeout < 10000) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to WiFi!");
    return;
  }
  Serial.println("\nWiFi Connected Successfully");

  Serial.println("Initializing Firebase...");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase Initialized");

  Serial.println("System Setup Complete");
  Serial.println("===================================");
  previousMillis = millis();
}
void sendToFirebase(float temperature, float humidity, int ldrValue, float distance, float AQI) { 
  String path = "/LivingRoom";
  FirebaseJson json;
  json.set("temperature", temperature);
  json.set("humidity", humidity);
  json.set("data/ldrValue", ldrValue);
  json.set("data/distance", distance);
  json.set("air_quality", AQI);
  if (Firebase.RTDB.updateNode(&fbdo, path.c_str(), &json)) {
    Serial.println("Data sent to Firebase successfully");
  } else {
    Serial.print("Failed to send data to Firebase: ");
    Serial.println(fbdo.errorReason());
  }
}
float calculateAQI(float temperature, float humidity, int gasValue) {
  float gasIndex = (gasValue / 4095.0) * 500.0;
  float tempIndex = ((temperature - 20.0) / 20.0) * 100.0;
  float humidityIndex = ((60.0 - humidity) / 60.0) * 100.0;

  // Chuyển về giới hạn 0-100 nếu cần
  if (tempIndex < 0) tempIndex = 0;
  if (humidityIndex < 0) humidityIndex = 0;

  // Tính chỉ số AQI custom
  float AQI = 0.5 * gasIndex + 0.3 * tempIndex + 0.2 * humidityIndex;
  return AQI;
}
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= readInterval) {
    // Đọc dữ liệu từ cảm biến
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    int ldrValue = analogRead(LDR_PIN);
    float distance = readDistance();
    int gasValue = analogRead(MQ2_PIN);  // Đọc giá trị ADC (0-4095)
    float AQI = calculateAQI(temperature, humidity, gasValue);
    Serial.println("===================================");
    Serial.print("Temperature: "); 
    if (isnan(temperature)) {
      Serial.println("Failed to read");
    } else {
      Serial.print(temperature, 1);
      Serial.println(" °C");
    }
    Serial.print("Humidity   : "); 
    if (isnan(humidity)) {
      Serial.println("Failed to read");
    } else {
      Serial.print(humidity, 0);
      Serial.println(" %");
    }
    bool hasError = false;
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Error: DHT22 sensor reading failed!");
      hasError = true;
    }
    Serial.print("  LDR Value: ");
    Serial.print(ldrValue);
    Serial.println(" (0-4095)");
    Serial.print("  Distance: ");
    if (distance == -1) {
      Serial.println("Out of range (2-400 cm)");
    } else {
      Serial.print(distance, 1);
      Serial.println(" cm");
    }
    Serial.print("Gas Value  : "); Serial.println(gasValue);
    Serial.print("=> Estimated AQI: "); Serial.println(AQI);
    Serial.println("===================================");
    sendToFirebase(temperature, humidity, ldrValue, distance, AQI);
    previousMillis = currentMillis;
  }
}