# MyFirstGame GIAI_PHONG_MIEN_NAM

Đây là một game chiến đấu đơn giản với mục đích giúp các bạn trẻ hiểu hơn về lịch sử Chiến tranh chống Mỹ cứu nước của dân tộc ta.

Game gồm 1 nhân vật chính, lấy cảm hứng từ hình tượng nữ du kích miền Nam, biểu trưng cho ý chí chiến đấu và khát vọng hòa bình của dân tộc Việt Nam.

Nhân vật "phản diện" gồm có: lính Mỹ, trực thăng và xe tăng của quân địch

Nhiệm vụ của người chơi là đưa nhân vật đi các chướng ngại vật của địa hình và các hiểm họa từ đối phương để nhanh chóng trong 304 giây 
thì đến được đích_mô hình của Dinh Độc lập, kết thúc chiến tranh đồng thời kết thúc game và ghi về cho mình một số điểm tương ứng với số
kẻ thù bắn được.

Ngoài ra, trong quá trình chơi thì nhân vật có thể lấy các ngọn đuốc xung quanh địa hình, đây là biểu tượng cho tinh thần Việt Nam, ánh sáng của Cách mạng soi đường cho nhân dân ta.

Game chơi với chuột và bàn phím:
+ Chuột trái để bắn đạn, chuột phải để nhảy đơn
+ Phím trái, phải, xuống tương ứng với chức năng
+ Riêng phím lên tương ứng với việc nhảy kép

Game có một số phần được lấy ý tưởng thuật toán và code bên thứ 3 (ngoài slide bài giảng và trên Layzyfoo) đã ghi rõ nguồn tham khảo thêm trên http://phattrienphanmem123az.com/ và anh Pass Phạm

+ hàm CheckToMap (trong file MainObject.cpp và Enemy.cpp) -> tham khảo và có bổ sung
+ phần xử lý bản đồ khi đối tượng rơi xuống vực (đi xuống khỏi màn hình), xử lý đạn trong file MainObject.cpp 
và hàm LoadMap (trong file Map.cpp) -> kết hợp tham khảo trên Lazyfoo phần Tiling và có bổ sung 
+ cách fill ảnh vào ô Tile map (trong file Map.cpp) -> tham khảo
+ cách dùng biến để lưu dữ liệu trong hiển thị thông số game (file Geometric.cpp)
