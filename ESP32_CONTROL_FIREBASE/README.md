# ESP32-Firebase-Control 
# Vauthor: "Trang Đặng, Vĩ Thắng, Lê Hoài Đạt, Nguyễn Viết Đức"
# Date: "`8/6/2025`"
**Real-time IoT sensor data streaming from ESP32 to Firebase Realtime Database**


## 📖 Mô tả

ESP32-Firebase-Control  là dự án IoT cho phép thu thập dữ liệu từ nhiều cảm biến (nhiệt độ, độ ẩm, ánh sáng, khoảng cách, chất lượng không khí) được gửi lên firebase, rồi đồng bộ thời gian thực để điều khiển các ngoại vi nhu đèn, quat(motor), máy lạnh(motor), tivi(LCD).

## 🚀 Tính năng

* **Thu thập dữ liệu cảm biến trên firebase**: DHT22 (nhiệt độ & độ ẩm), LDR (ánh sáng), HC-SR04 (khoảng cách), MQ2 (khí gas).
* **Gửi dữ liệu trạng thái lên firebase**: đèn, quạt(motor), máy lạnh(motor), tivi(LCD).
* **Đồng bộ real-time** qua Firebase Realtime Database.
* **Cảnh báo**: LED nhấp nháy khi giá trị vượt ngưỡng cài đặt.
* **Lịch sử hoạt động**: Lưu trữ và truy vấn dữ liệu quá khứ.

## 🧰 Công nghệ

* **Phần cứng**: ESP32 DevKitC, Button, LED, Motor, LCD.
* **Firmware**: Arduino (PlatformIO), thư viện FirebaseESP32, DHT sensor, LiquidCrystal\_I2C.
* **Cloud**: Firebase Realtime Database, Firebase Authentication

## 🛠️ Cài đặt

1. **Clone repository**

   ```bash
   git clone https://github.com/yourusername/esp32-firebase-sensor-hub.git
   cd esp32-firebase-sensor-hub
   ```

2. **Cấu hình Firebase**

   * Tạo dự án trên [Firebase Console](https://console.firebase.google.com/) và bật Realtime Database.
   * Tạo `database secret` hoặc `API key` trong **Project Settings**.
   * Mở `src/main.cpp`, cập nhật:

     ```cpp
     #define FIREBASE_HOST "https://<YOUR_PROJECT_ID>.firebaseio.com/"
     #define FIREBASE_AUTH "<YOUR_DATABASE_SECRET>"
     ```

3. **Cài đặt thư viện**
   PlatformIO sẽ tự động cài:

   * `FirebaseESP32`
   * `DHT sensor library`
   * `LiquidCrystal_I2C`

4. **Upload firmware (nạp code)**

    Kết nối ESP32 qua USB và nạp chương trình:
    "pio run --target upload"

5. **Mở Serial Monitor**

    Quan sát log và dữ liệu:
    "pio device monitor -b 115200"

## 📁 Cấu trúc thư mục

```
ESP32_CONTROL_FIREBASE/
├── pio/
├── vscode/
├── include/
├── lib/                    # Các thư viện 
├── src/
│   └── main.cpp           # Mã nguồn ESP32
├── test/
├── .gitignore
├── platformio.ini         # Cấu hình PlatformIO
└── README.md
```


## 👥 Nhóm phát triển

* **Trang Đặng Vĩ Thắng**
* **Lê Hoài Đạt**
* **Nguyễn Viết Đức**

