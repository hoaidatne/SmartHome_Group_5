#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// WiFi & Firebase config
#define WIFI_SSID "702_wifi_2"
#define WIFI_PASSWORD "2345678910"
#define FIREBASE_HOST "https://smarthomenhom5-f0d22-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyDTOpVjmPkXaxVx7eCSAFPyhslvHwEIpn0"

// Firebase object
FirebaseData fbdo;
FirebaseConfig config;
FirebaseAuth auth;
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Khai báo chân điều khiển moto
#define ENA 4
#define IN1 16
#define IN2 17
#define IN3 26
#define IN4 27
#define ENB 14
#define BUTTON_PIN 15 
#define BUTTON_TV_PIN 5
#define BUTTON_LED_PIN 18
#define FAN_PIN 19
#define LED_CANHBAO 13
#define LED_MAINLIGHT 12
#define LED_CANHBAO2 25

#define PWM_CHANNEL_LED  1
#define PWM_FREQ 5000
#define PWM_RESOLUTION 8

String newACState, newTVState, newLedstate, newFANState;

int reversedSpeed, volume, aic, dutyled, speedfan, distance;

unsigned long lastFirebaseRead = 0;
const unsigned long firebaseReadInterval = 1000; // đọc mỗi 1000ms
bool debugMode = true;

void backward(int speed);
void fordward(int speed);
void stopMotorfan();
void stopMotorac();
void KT_NUT_NHAN_FAN();
void KT_NUT_NHAN_AC();  
void KT_NUTNHAN_TV();
void KT_FIREBASE();
void KT_NUT_NHAN_LED();

void setup() {
  Serial.begin(115200);   // Bật Serial để debug
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  pinMode(BUTTON_TV_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LED_PIN, INPUT_PULLUP);
  pinMode(FAN_PIN, INPUT_PULLUP);
  pinMode(LED_CANHBAO, OUTPUT);   
  pinMode(LED_CANHBAO2, OUTPUT);
  ledcSetup(PWM_CHANNEL_LED, PWM_FREQ, PWM_RESOLUTION); // cấu hình kênh PWM
  ledcAttachPin(LED_MAINLIGHT, PWM_CHANNEL_LED);       // gán chân GPIO vào kênh PWM

  Wire.begin();         // Khởi động I2C
  lcd.init();           // Khởi động LCD
  Serial.print(" kết nối LCD thành công");
  // Kết nối WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nĐã kết nối WiFi!");

  // Cấu hình Firebase
  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  // Thiết lập các chân là OUTPUT
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotorac();
  stopMotorfan();
}

void loop() {
    KT_NUT_NHAN_AC();
    KT_NUTNHAN_TV();
    KT_NUT_NHAN_LED();
    KT_NUT_NHAN_FAN();
      // Chỉ đọc Firebase khi đến thời gian
    if (millis() - lastFirebaseRead >= firebaseReadInterval) {
      lastFirebaseRead = millis();
      KT_FIREBASE();
    }
    if (newACState == "ON") {
      backward(reversedSpeed);
    } else {
      stopMotorac();
    }
    if (newFANState == "ON") {
      fordward(speedfan);
    } else {
      stopMotorfan();
    }
    if (newTVState == "ON") {     // Xóa màn hình
      lcd.backlight();      // Bật đèn nền
      lcd.setCursor(0, 0);  // Đưa con trỏ về đầu dòng 1
      lcd.print(" TV DA BAT "); // In chữ lên dòng 1 (thêm khoảng trắng cho cân)
      lcd.setCursor(0, 1);  // Đưa con trỏ về đầu dòng 2
      lcd.print("volume:  ");
      lcd.print(volume); // In chữ lên dòng 2
    } else {
      lcd.clear();         
      lcd.noBacklight(); 
    }
    if (aic >100) {
      digitalWrite(LED_CANHBAO, HIGH); // Bật đèn 
      delay(10); 
      digitalWrite(LED_CANHBAO, LOW); 
    } else {
      digitalWrite(LED_CANHBAO, LOW); // Tắt đèn
    }
    if (newLedstate == "ON") {
      ledcWrite(PWM_CHANNEL_LED, dutyled); // Bật đèn LED với độ sáng 
    } else {
      ledcWrite(PWM_CHANNEL_LED, 0); // Tắt đèn LED
    }
    if (distance <100) {
      digitalWrite(LED_CANHBAO2, HIGH); // Bật đèn 
      delay(10); 
      digitalWrite(LED_CANHBAO2, LOW); 
    } else {
      digitalWrite(LED_CANHBAO2, LOW); // Tắt đèn
    }
}
void KT_NUT_NHAN_AC() {
    static unsigned long lastDebounceTime = 0;
    static int lastButtonState = HIGH;
    static int buttonStableState = HIGH;  // Trạng thái ổn định cuối cùng

    int buttonReading = digitalRead(BUTTON_PIN);

    if (buttonReading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > 30) {
        if (buttonReading != buttonStableState) {
            buttonStableState = buttonReading;
            // CHỈ khi nút chuyển từ HIGH sang LOW (nhấn xuống)
            if (buttonStableState == LOW) {
              Serial.print("Nút AC được nhấn ");
              if (Firebase.getString(fbdo, "/LivingRoom/air-conditioner/state")) {
                String statetemp = fbdo.stringData();
                Serial.print("trạng thái AC: ");
                Serial.println(statetemp);
                newACState = (statetemp == "ON") ? "OFF" : "ON";
                Serial.print("trạng thái AC mới: ");
                Serial.println(newACState);
                unsigned long startTime = millis();
                while (!Firebase.setString(fbdo, "/LivingRoom/air-conditioner/state", newACState)) {
                  if (millis() - startTime > 2000) {
                    Serial.print("❌ Lỗi cập nhật trạng thái lên firebase : ");
                    Serial.println(fbdo.errorReason());
                    break;
                  }
                  delay(50); // giảm xuống 50ms để phản hồi nhanh hơn mà vẫn an toàn
                }

                if (millis() - startTime <= 2000) {
                  Serial.println("✅ Đã đổi trạng thái mới");
                }
            }
          }
        } 
    }

    lastButtonState = buttonReading;
}
void KT_NUT_NHAN_FAN() {
    static unsigned long lastDebounceTime = 0;
    static int lastButtonState = HIGH;
    static int buttonStableState = HIGH;  // Trạng thái ổn định cuối cùng

    int buttonReading = digitalRead(FAN_PIN);

    if (buttonReading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > 30) {
        if (buttonReading != buttonStableState) {
            buttonStableState = buttonReading;
            // CHỈ khi nút chuyển từ HIGH sang LOW (nhấn xuống)
            if (buttonStableState == LOW) {
              Serial.print("Nút FAN được nhấn ");
              if (Firebase.getString(fbdo, "/LivingRoom/fan/state")) {
                String statefan = fbdo.stringData();
                Serial.print("trạng thái FAN: ");
                Serial.println(statefan);
                newFANState = (statefan == "ON") ? "OFF" : "ON";
                Serial.print("trạng thái FAN mới: ");
                Serial.println(newFANState);
                unsigned long startTime = millis();
                while (!Firebase.setString(fbdo, "/LivingRoom/fan/state", newFANState)) {
                  if (millis() - startTime > 2000) {
                    Serial.print("❌ Lỗi cập nhật trạng thái lên firebase : ");
                    Serial.println(fbdo.errorReason());
                    break;
                  }
                  delay(50); // giảm xuống 50ms để phản hồi nhanh hơn mà vẫn an toàn
                }

                if (millis() - startTime <= 2000) {
                  Serial.println("✅ Đã đổi trạng thái mới");
                }
            }
          }
        } 
    }

    lastButtonState = buttonReading;
}
void KT_NUT_NHAN_LED() {
    static unsigned long lastDebounceTime = 0;
    static int lastButtonState = HIGH;
    static int buttonStableState = HIGH;  // Trạng thái ổn định cuối cùng

    int buttonReading = digitalRead(BUTTON_LED_PIN);

    if (buttonReading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > 30) {
        if (buttonReading != buttonStableState) {
            buttonStableState = buttonReading;
            // CHỈ khi nút chuyển từ HIGH sang LOW (nhấn xuống)
            if (buttonStableState == LOW) {
              Serial.print("Nút Led được nhấn ");
              if (Firebase.getString(fbdo, "/LivingRoom/main-light/state")) {
                String stateled = fbdo.stringData();
                Serial.print("trạng thái led: ");
                Serial.println(stateled);
                newLedstate = (stateled == "ON") ? "OFF" : "ON";
                Serial.print("trạng thái mới: ");
                Serial.println(newLedstate);
                unsigned long startTime = millis();
                while (!Firebase.setString(fbdo, "/LivingRoom/main-light/state", newLedstate)) {
                  if (millis() - startTime > 2000) {
                    Serial.print("❌ Lỗi cập nhật trạng thái lên firebase : ");
                    Serial.println(fbdo.errorReason());
                    break;
                  }
                  delay(50); // giảm xuống 50ms để phản hồi nhanh hơn mà vẫn an toàn
                }

                if (millis() - startTime <= 2000) {
                  Serial.println("✅ Đã đổi trạng thái mới");
                }
              }
          }
        } 
    }

    lastButtonState = buttonReading;
}
void KT_NUTNHAN_TV() {
  static unsigned long lastDebounceTime = 0;
  static int lastButtonState = HIGH;
  static int buttonStableState = HIGH;  // Trạng thái ổn định cuối cùng

  int buttonReading = digitalRead(BUTTON_TV_PIN);

  if (buttonReading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > 30) {
    if (buttonReading != buttonStableState) {
      buttonStableState = buttonReading;
      // CHỈ khi nút chuyển từ HIGH sang LOW (nhấn xuống)
      if (buttonStableState == LOW) {
        Serial.print("Nút TV được nhấn ");
        if (Firebase.getString(fbdo, "/LivingRoom/smartTV/state")) {
          String statetv = fbdo.stringData();
          Serial.print("trạng thái TV: ");
          Serial.println(statetv);
          newTVState = (statetv == "ON") ? "OFF" : "ON";
          Serial.print("trạng thái mới: ");
          Serial.println(newTVState);
          unsigned long startTime = millis();
          while (!Firebase.setString(fbdo, "/LivingRoom/smartTV/state", newTVState)) {
            if (millis() - startTime > 2000) {
              Serial.print("❌ Lỗi cập nhật trạng thái lên firebase : ");
              Serial.println(fbdo.errorReason());
              break;
            }
            delay(50); // giảm xuống 50ms để phản hồi nhanh hơn mà vẫn an toàn
          }

          if (millis() - startTime <= 2000) {
            Serial.println("✅ Đã đổi trạng thái mới");
          }
        } 
      }
      }
    }

    lastButtonState = buttonReading;
}
void KT_FIREBASE() {
  FirebaseJson jsonData;
  FirebaseJsonData result;

  // Đọc toàn bộ nhánh /LivingRoom từ Firebase
  if (Firebase.getJSON(fbdo, "/LivingRoom", &jsonData)) {
    Serial.println("Doc du lieu Firebase thanh cong!");

    // Đọc air_quality
    if (jsonData.get(result, "air_quality")) {
      aic = result.intValue;
      Serial.print("Air Quality: ");
      Serial.println(aic);
    }

    // Đọc main-light/state
    if (jsonData.get(result, "main-light/state")) {
      newLedstate = result.stringValue;
      Serial.print("LED State: ");
      Serial.println(newLedstate);
    }

    // Đọc main-light/brightness
    if (jsonData.get(result, "main-light/brightness")) {
      dutyled = result.intValue;
      Serial.print("LED Brightness: ");
      Serial.println(dutyled);
    }

    // Đọc fan/state
    if (jsonData.get(result, "fan/state")) {
      newFANState = result.stringValue;
      Serial.print("FAN State: ");
      Serial.println(newFANState);
    }

    // Đọc fan/speed
    if (jsonData.get(result, "fan/speed")) {
      int speed = result.intValue;
      Serial.print("FAN Speed: ");
      Serial.println(speed);
      speedfan = map(speed, 0, 100, 100, 255);  
    }

    // Đọc air-conditioner/state
    if (jsonData.get(result, "air-conditioner/state")) {
      newACState = result.stringValue;
      Serial.print("AC State: ");
      Serial.println(newACState);
    }

    // Đọc air-conditioner/temp
    if (jsonData.get(result, "air-conditioner/temp")) {
      int Speed = result.intValue;
      Serial.print("AC Temp (speed): ");
      Serial.println(Speed);
      reversedSpeed = 255 - map(Speed, 16, 30, 0, 155);
    }

    // Đọc smartTV/state
    if (jsonData.get(result, "smartTV/state")) {
      newTVState = result.stringValue;
      Serial.print("TV State: ");
      Serial.println(newTVState);
    }

    // Đọc smartTV/volume
    if (jsonData.get(result, "smartTV/volume")) {
      volume = result.intValue;
      Serial.print("TV Volume: ");
      Serial.println(volume);
    }
    // Đọc khoảng cách

    if (jsonData.get(result, "data/distance")) {
      distance = result.intValue;
      Serial.print("khoảng cách: ");
      Serial.println(distance);
    }
  } else {
    Serial.print("Doc du lieu Firebase that bai: ");
    Serial.println(fbdo.errorReason());
  }
}

void backward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);
}

void stopMotorac() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}
void fordward(int speed) {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void stopMotorfan() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}