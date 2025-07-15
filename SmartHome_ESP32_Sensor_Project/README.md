---

title: "SmartHome-ESP32-Sensor-Project"
author: "Trang Đặng, Vĩ Thắng, Lê Hoài Đạt, Nguyễn Viết Đức"
date: "`8/6/2025`"

------------------------

# Giới thiệu

**SmartHome-ESP32-Sensor-Project** là dự án kết hợp hệ thống IoT nhúng và giao diện web để giám sát, điều khiển nhà thông minh thời gian thực. Phần nhúng sử dụng ESP32 kết nối với các cảm biến (DHT22, LDR, HC-SR04, MQ2) cho phép gửi dữ liệu đồng bộ lên Firebase Realtime Database.

# Tính năng

* Giám sát **nhiệt độ**, **độ ẩm**, **cường độ ánh sáng**, **khoảng cách**
* Gửi dữ liệu **nhiệt độ**, **độ ẩm**, **cường độ ánh sáng**, **khoảng cách** lên firebase
* Lưu trữ và hiển thị **lịch sử hoạt động**
* **Dashboard** web responsive cho phép điều khiển và giám sát qua trình duyệt

# Công nghệ sử dụng

* **Phần cứng:** ESP32 DevKitC, DHT22, HC-SR04, Photoresistor (LDR), MQ2
* **Phần mềm nhúng:** Arduino framework, PlatformIO; thư viện FirebaseESP32, DHT sensor, LiquidCrystal\_I2C, ERa
* **Realtime Database:** Firebase Realtime Database & Firebase Authentication
* **Mô phỏng:** Wokwi (diagram.json + wokwi.toml)

# Yêu cầu

* **Phần cứng:** ESP32, cảm biến DHT22, HC-SR04, LDR, MQ2
* **Phần mềm:**

  * PlatformIO IDE hoặc VSCode + PlatformIO Extension
  * Tài khoản Firebase và một Realtime Database
  * Node.js & npm (nếu có frontend riêng)

# Hướng dẫn cài đặt

## 1. Cấu hình Firebase

Mở `main.cpp`, cập nhật thông tin dự án Firebase:

```cpp
#define FIREBASE_HOST "https://<YOUR_FIREBASE_PROJECT>.firebaseio.com/"
#define FIREBASE_AUTH "<YOUR_DATABASE_SECRET>"
```

## 2. Cài đặt thư viện (PlatformIO tự động)

```ini
[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
lib_deps =
  olikraus/U8g2@^2.36.5
  adafruit/Adafruit Unified Sensor@^1.1.15
  adafruit/DHT sensor library@^1.4.6
  marcoschwartz/LiquidCrystal_I2C@^1.1.4
  eoh-ltd/ERa@^1.6.2
```

## 3. Build & Upload firmware

Kết nối ESP32 qua USB và chạy:

```bash
pio run --target upload
```

## 4. Mở Serial Monitor

```bash
pio device monitor -b 115200
```

## 5. Mô phỏng Wokwi trong VS Code

Cài extension Wokwi Arduino Simulator từ Marketplace

Mở file diagram.json hoặc wokwi.toml trong workspace

Bấm biểu tượng chạy (▶️) trên góc file để khởi động mô phỏng ngay trong VS Code

Quan sát dòng log và tương tác nút điều khiển mô phỏng ngay trên editor

## 🧪 Mô phỏng với Wokwi (portal web)

Nếu không muốn dùng VS Code, bạn có thể chạy mô phỏng trực tiếp trên web:

Truy cập Wokwi ESP32 Simulator

Chọn Import Project và tải lên diagram.json + wokwi.toml

Nhấn Start Simulation để quan sát dữ liệu và hoạt động LED, buzzer


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
├── diagram.json
├── era_partition_8MB.csv
├── era_partition_16MB.csv
├── era_partition.csv
├── ERa.txt
├── platformio.ini         # Cấu hình PlatformIO
├── README.md
├── state_led_bzzer.txt
└── wokwi.toml
```

# Nhóm phát triển

* **Trang Đặng Vĩ Thắng**
* **Lê Hoài Đạt**
* **Nguyễn Viết Đức**


