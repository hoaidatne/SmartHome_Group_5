Smart Home

Giới thiệu
Smart Home là một ứng dụng web giúp người dùng quản lý và điều khiển các thiết bị thông minh trong ngôi nhà như đèn, quạt, điều hòa, và cảm biến môi trường (nhiệt độ, độ ẩm, chất lượng không khí). Dự án được phát triển bởi Nhóm 5, cung cấp giao diện trực quan để giám sát và điều khiển các phòng như phòng khách, phòng ngủ, và nhà bếp.
Tính năng

Điều khiển thiết bị thông minh: Bật/tắt và điều chỉnh các thiết bị như đèn, quạt, điều hòa, TV, và lò nướng.
Giám sát môi trường: Theo dõi nhiệt độ, độ ẩm, và chất lượng không khí với các cảnh báo trực quan.
Giao diện responsive: Hỗ trợ trên cả máy tính và thiết bị di động.
Tích hợp Firebase: Lưu trữ và quản lý dữ liệu thiết bị trong thời gian thực.
Chuyển đổi phòng dễ dàng: Điều hướng nhanh giữa các phòng qua menu dropdown.

Yêu cầu hệ thống

Trình duyệt: Chrome, Firefox, Safari (phiên bản mới nhất).
Node.js: 16.x hoặc cao hơn (để chạy local server nếu cần).
Firebase: Tài khoản Firebase để cấu hình cơ sở dữ liệu.
Internet: Kết nối ổn định để tải tài nguyên và giao tiếp với Firebase.

Cài đặt

Clone repository:
git clone https://github.com/username/smart-home.git


Di chuyển vào thư mục dự án:
cd smart-home


Cài đặt các phụ thuộc:
npm install

Lưu ý: Đảm bảo bạn đã cài Node.js và npm.

Cấu hình Firebase:

Tạo một dự án trên Firebase Console.
Sao chép cấu hình Firebase vào file firebase.js (đã được cung cấp trong dự án).
Đảm bảo các thông tin như apiKey, authDomain, databaseURL được cập nhật chính xác.


Chạy ứng dụng:

Nếu sử dụng local server (ví dụ: http-server hoặc live-server):npm install -g http-server
http-server .


Hoặc mở trực tiếp file index.html trong trình duyệt (lưu ý: một số tính năng Firebase có thể yêu cầu server).


Truy cập ứng dụng:

Mở trình duyệt và truy cập http://localhost:8080 (hoặc cổng được chỉ định bởi server).



Cách sử dụng

Trang chủ:

Truy cập index.html để xem giới thiệu dự án, thành viên nhóm, và liên kết đến các phòng.
Nhấp vào nút "View More" để tìm hiểu thêm hoặc nút "Điều Khiển" để vào các phòng cụ thể.


Điều khiển phòng:

Sử dụng menu dropdown (nút Home ở góc dưới bên phải) để chuyển đổi giữa các phòng: Living Room (living_room.html), Kitchen (kitchen.html), Bedroom (bed_room.html).
Trong mỗi phòng, bạn có thể:
Theo dõi nhiệt độ, độ ẩm, và chất lượng không khí qua các đồng hồ đo (arc-gauge).
Bật/tắt thiết bị bằng công tắc (switch).
Điều chỉnh mức độ (độ sáng, tốc độ quạt, âm lượng, nhiệt độ) qua thanh trượt (slider).




Ví dụ điều khiển thiết bị:

Để bật đèn phòng khách:
Truy cập living_room.html.
Tìm mục "Main Light", bật công tắc và điều chỉnh thanh trượt độ sáng.


Dữ liệu được cập nhật thời gian thực qua Firebase (nếu được cấu hình đúng).


Cảnh báo môi trường:

Nhiệt độ: Cảnh báo từ "Cold" đến "May Catch Fire" dựa trên giá trị đo.
Độ ẩm: Cảnh báo từ "Very Dry" đến "Stuffy".
Chất lượng không khí: Cảnh báo từ "Good" đến "Hazardous".



Cấu trúc dự án

index.html: Trang chủ, giới thiệu dự án và nhóm.
bed_room.html, kitchen.html, living_room.html: Giao diện điều khiển cho từng phòng.
firebase.js: Cấu hình Firebase cho lưu trữ và phân tích dữ liệu.
main.js: Xử lý logic chính (menu, dropdown, hiển thị ngày giờ).
room_functions.js: Hàm cập nhật cảnh báo và điều khiển thiết bị.
main.css, style_room.css, menu-container.css: File CSS cho giao diện và hiệu ứng.

Đóng góp
Chúng tôi hoan nghênh mọi đóng góp! Để tham gia:

Fork repository:
Nhấp vào nút "Fork" trên GitHub.


Tạo branch mới:git checkout -b feature/ten-tinh-nang


Commit thay đổi:git commit -m "Thêm tính năng XYZ"


Push lên branch:git push origin feature/ten-tinh-nang


Tạo Pull Request trên GitHub.

Vui lòng đọc CONTRIBUTING.md (nếu có) để biết thêm chi tiết.
Giấy phép
Dự án này được cấp phép theo MIT License.
Liên hệ

Email:
support@smarthome.com
dat.le@example.com
thang.trang@example.com
duc.nguyen@example.com


GitHub Issues: Báo lỗi hoặc đề xuất
Điện thoại:
Lê Hoài Đạt: 039260xxxxx
Trang Đặng Vĩ Thắng: 037671xxxxx
Nguyễn Viết Đức: 086795xxxxx




Cảm ơn bạn đã sử dụng Smart Home!

