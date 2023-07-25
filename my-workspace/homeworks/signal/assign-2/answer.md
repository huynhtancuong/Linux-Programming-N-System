## Realtime signal và standard signal là gì? Phân biệt sự khác nhau giữa chúng.
Realtime signal và standard signal đều là những signal dùng để giao tiếp liên tiến trình trong các hệ thống Unix và Unix-like.
Realtime signal là signal có giá trị nằm giữa SIGRTMIN và SIGRTMAX (được định nghĩa trong signal.h)
Standard signal là các signal còn lại. Ví dụ như SIGINT, SIGTERM, ...

Sự khác biệt giữa realtime signal và standard signal nằm ở việc xử lí hàng đợi dành cho các signal này.
Đối với standard signal, khi một standard signal được gửi đến process, nếu trong hàng đợi đã có signal cùng loại thì bọn chúng sẽ bị gọp lại với nhau và xem như là một signal duy nhất.
Còn đối với realtime signal, khi một realtime signal được gửi đến process, nếu trong hàng đợi đã có signal cùng loại thì bọn chúng sẽ KHÔNG bị gọp lại với nhau và xem như là các signal riêng lẻ.

Một điểm khác biệt nữa là realtime signal có thể mang thêm dữ liệu (có thể là số nguyên hoặc là một con trỏ). Xem thêm tại http://davmac.org/davpage/linux/rtsignals.html

Trong các hệ thống UNIX và UNIX-like, có một giới hạn về kích thước của hàng đợi signal. Điều này mở ra một khả năng tấn công từ dối dịch vụ bằng signal.

