# MÔ TẢ GAME PARKOUR 2D

## I. GIỚI THIỆU TỔNG QUAN

### 1.1. Tên game
**GAME PARKOUR 2D - MÊ CUNG PHIÊU LƯU**

### 1.2. Thể loại
- **Thể loại chính**: Platformer 2D, Action-Adventure
- **Phong cách chơi**: Parkour, Thu thập vật phẩm, Chiến đấu

### 1.3. Mô tả ngắn gọn
Game Parkour 2D là một trò chơi phiêu lưu hành động được phát triển bằng ngôn ngữ C/C++ với thư viện đồ họa WinBGIM. Người chơi điều khiển nhân vật vượt qua mê cung rộng lớn với nhiều tầng platform, thu thập chìa khóa, chiến đấu với quái vật và tìm đường thoát. Game kết hợp yếu tố vật lý thực tế, hệ thống va chạm chính xác và AI quái vật thông minh.

---

## II. MỤC TIÊU GAME

### 2.1. Mục tiêu chính
- **Thu thập đủ 3 chìa khóa vàng** ẩn trong các vị trí khác nhau trên bản đồ
- **Tìm và mở cửa thoát** ở góc phải dưới của map
- **Sống sót** qua các cuộc tấn công của quái vật

### 2.2. Mục tiêu phụ
- Tiêu diệt quái vật để kiếm điểm thưởng
- Đạt điểm số cao nhất có thể
- Hoàn thành game với HP còn lại nhiều nhất

---

## III. CƠ CHẾ GAMEPLAY

### 3.1. Điều khiển

| Phím | Chức năng |
|------|-----------|
| **W** hoặc **Space** | Nhảy lên |
| **A** | Di chuyển sang trái |
| **D** | Di chuyển sang phải |
| **Chuột trái** | Bắn đạn (hướng theo con trỏ chuột) |
| **ESC** | Thoát game |

### 3.2. Hệ thống vật lý

#### 3.2.1. Thông số vật lý
- **Trọng lực**: 0.8 (tác động liên tục lên nhân vật)
- **Tốc độ rơi tối đa**: 15 (giới hạn vận tốc rơi)
- **Lực nhảy**: 12 (độ cao nhảy)
- **Ma sát**: 0.85 (làm chậm dần khi không di chuyển)
- **Tốc độ di chuyển**: 5 (tốc độ ngang)

#### 3.2.2. Cơ chế di chuyển
- Nhân vật chịu tác động của **trọng lực** liên tục
- Chỉ có thể **nhảy khi đang đứng trên mặt đất**
- Vận tốc ngang giảm dần do **ma sát** khi không nhấn phím
- Không thể **xuyên qua tường** - phải tìm đường đi hợp lý

### 3.3. Hệ thống chiến đấu

#### 3.3.1. Bắn đạn
- **Hướng bắn**: Theo vị trí con trỏ chuột
- **Tốc độ đạn**: 10
- **Giới hạn**: Tối đa 20 viên đạn cùng lúc trên màn hình
- **Sát thương**: 1 HP/viên đạn
- **Tốc độ bắn**: Giới hạn 200ms/viên (5 viên/giây)

#### 3.3.2. Va chạm
- **Player - Enemy**: Mất 10 HP, bị đẩy lùi
- **Bullet - Enemy**: Quái vật mất 1 HP
- **Player - Wall**: Không thể xuyên qua
- **Bullet - Wall**: Đạn biến mất

---

## IV. CÁC THÀNH PHẦN TRONG GAME

### 4.1. Nhân vật chính (Player)

| Thuộc tính | Giá trị |
|------------|---------|
| **Màu sắc** | Xanh dương |
| **Kích thước** | 30x40 pixels |
| **HP ban đầu** | 100 |
| **Tốc độ di chuyển** | 5 |
| **Lực nhảy** | 12 |
| **Khả năng đặc biệt** | Bắn đạn theo hướng chuột |

**Vị trí xuất phát**: Góc trái trên của map (cột 2, hàng 1)

### 4.2. Quái vật (Enemies)

| Thuộc tính | Giá trị |
|------------|---------|
| **Màu sắc** | Đỏ |
| **Kích thước** | 35x35 pixels |
| **HP** | 3 |
| **Tốc độ di chuyển** | 2 |
| **Số lượng** | 6 con |
| **Sát thương** | -10 HP/lần chạm |

#### 4.2.1. AI quái vật
- **Tuần tra tự động**: Di chuyển qua lại trên platform
- **Phát hiện tường**: Đổi hướng khi va chạm tường
- **Phát hiện bờ vực**: Đổi hướng khi gặp bờ vực (tránh rơi)
- **Thanh máu**: Hiển thị HP còn lại phía trên đầu

#### 4.2.2. Vị trí quái vật
1. **Quái 1**: Platform hàng 3 (bên trái)
2. **Quái 2**: Platform hàng 3 (bên phải)
3. **Quái 3**: Platform hàng 8 (bên trái)
4. **Quái 4**: Platform hàng 12 (giữa map)
5. **Quái 5**: Platform hàng 20 (bên trái)
6. **Quái 6**: Platform hàng 25 (bên phải)

### 4.3. Chìa khóa (Keys)

| Thuộc tính | Giá trị |
|------------|---------|
| **Màu sắc** | Vàng |
| **Số lượng** | 3 chìa |
| **Điểm thưởng** | +50 điểm/chìa |
| **Chức năng** | Cần đủ 3 chìa để mở cửa |

#### 4.3.1. Vị trí chìa khóa
1. **Chìa 1**: Platform hàng 5 (bên trái) - Dễ
2. **Chìa 2**: Platform hàng 15 (giữa map) - Trung bình
3. **Chìa 3**: Platform hàng 22 (bên phải) - Khó

### 4.4. Cửa thoát (Door)

| Thuộc tính | Giá trị |
|------------|---------|
| **Màu sắc** | Xám (đóng) → Xanh lá (mở) |
| **Vị trí** | Góc phải dưới (platform hàng 26) |
| **Điều kiện mở** | Cần 3 chìa khóa |
| **Điểm thưởng** | +200 điểm khi mở |

---

## V. BẢN ĐỒ (MAP)

### 5.1. Thông số kỹ thuật

| Thông số | Giá trị |
|----------|---------|
| **Kích thước map** | 40 cột × 28 hàng |
| **Kích thước tile** | 25×25 pixels |
| **Kích thước màn hình** | 1000×700 pixels |
| **Tổng số tiles** | 1,120 tiles |

### 5.2. Thiết kế map
- **Mê cung nhiều tầng**: 9 tầng platform khác nhau
- **Độ rộng**: Sử dụng toàn bộ 40 cột (gấp đôi so với phiên bản cũ)
- **Độ phức tạp**: Nhiều đường đi, nhiều lựa chọn di chuyển
- **Phân bố items**: Chìa khóa và quái vật ở các vị trí xa nhau
- **Độ khó tăng dần**: Từ trên xuống dưới, từ trái sang phải

### 5.3. Cấu trúc map
```
Hàng 0:    Tường trên (biên giới)
Hàng 1-2:  Khu vực xuất phát
Hàng 3:    Platform tầng 1 (4 đoạn)
Hàng 5:    Platform tầng 2 (3 đoạn dài)
Hàng 8:    Platform tầng 3 (4 đoạn)
Hàng 10:   Platform tầng 4 (4 đoạn nhỏ)
Hàng 12:   Platform tầng 5 (5 đoạn)
Hàng 15:   Platform tầng 6 (4 đoạn)
Hàng 17:   Platform tầng 7 (4 đoạn)
Hàng 20:   Platform tầng 8 (4 đoạn)
Hàng 22:   Platform tầng 9 (4 đoạn)
Hàng 25:   Platform tầng dưới (4 đoạn)
Hàng 27:   Tường dưới (sàn)
```

---

## VI. HỆ THỐNG ĐIỂM

### 6.1. Bảng điểm thưởng

| Hành động | Điểm thưởng |
|-----------|-------------|
| Tiêu diệt quái vật | **+100** |
| Thu thập chìa khóa | **+50** |
| Mở cửa thoát | **+200** |

### 6.2. Điểm tối đa
- **Tiêu diệt 6 quái**: 6 × 100 = 600 điểm
- **Thu thập 3 chìa**: 3 × 50 = 150 điểm
- **Mở cửa**: 1 × 200 = 200 điểm
- **TỔNG ĐIỂM TỐI ĐA**: **950 điểm**

---

## VII. ĐIỀU KIỆN THẮNG/THUA

### 7.1. Điều kiện thắng
✅ Thu thập đủ **3 chìa khóa**  
✅ Đến **cửa thoát** ở góc phải dưới  
✅ Mở cửa thành công  

→ **Màn hình "YOU WIN!"** hiển thị với điểm số đạt được

### 7.2. Điều kiện thua
❌ HP giảm xuống **0** (do bị quái vật tấn công nhiều lần)  

→ **Màn hình "GAME OVER!"** hiển thị với điểm số đạt được

---

## VIII. CÔNG NGHỆ SỬ DỤNG

### 8.1. Ngôn ngữ & Thư viện

| Công nghệ | Mô tả |
|-----------|-------|
| **Ngôn ngữ** | C/C++ |
| **Thư viện đồ họa** | graphics.h / WinBGIM |
| **IDE** | Dev-C++ / Code::Blocks |
| **Hệ điều hành** | Windows 7 trở lên |
| **Compiler** | MinGW GCC |

### 8.2. Cấu trúc code

```
main.cpp (749 dòng)
├── Định nghĩa hằng số (40 dòng)
│   ├── Cấu hình màn hình
│   ├── Thông số nhân vật
│   ├── Thông số đạn
│   ├── Thông số quái vật
│   └── Thông số bản đồ
│
├── Cấu trúc dữ liệu (50 dòng)
│   ├── struct Player
│   ├── struct Bullet
│   ├── struct Enemy
│   ├── struct Key
│   └── struct Door
│
├── Biến toàn cục (50 dòng)
│   ├── Player player
│   ├── Bullet bullets[20]
│   ├── Enemy enemies[10]
│   ├── Key keys[3]
│   ├── Door doors[3]
│   └── int map[28][40]
│
├── Hàm khởi tạo (120 dòng)
│   ├── initGame()
│   ├── initPlayer()
│   ├── initBullets()
│   ├── initEnemies()
│   ├── initKeys()
│   └── initDoors()
│
├── Hàm cập nhật logic (180 dòng)
│   ├── updatePlayer()
│   ├── updateBullets()
│   ├── updateEnemies()
│   └── checkCollisions()
│
├── Hàm vẽ đồ họa (150 dòng)
│   ├── drawMap()
│   ├── drawPlayer()
│   ├── drawBullets()
│   ├── drawEnemies()
│   ├── drawKeys()
│   ├── drawDoors()
│   └── drawUI()
│
├── Hàm xử lý input (80 dòng)
│   ├── handleInput()
│   ├── shootBullet()
│   └── checkMapCollision()
│
└── Game loop chính (80 dòng)
    └── main()
```

### 8.3. Thuật toán chính

#### 8.3.1. Collision Detection (Phát hiện va chạm)
```
Thuật toán: Kiểm tra 4 góc của hình chữ nhật
- Input: Tọa độ (x, y), kích thước (w, h)
- Output: True nếu va chạm, False nếu không
- Độ phức tạp: O(1)
```

#### 8.3.2. AI Enemy (Trí tuệ nhân tạo quái vật)
```
Thuật toán: Patrol với phát hiện tường và bờ vực
1. Di chuyển theo hướng hiện tại
2. Kiểm tra va chạm tường → Đổi hướng
3. Kiểm tra bờ vực phía trước → Đổi hướng
4. Lặp lại
- Độ phức tạp: O(1) mỗi frame
```

#### 8.3.3. Bullet Trajectory (Quỹ đạo đạn)
```
Thuật toán: Vector hóa hướng bắn
1. Tính vector từ player đến chuột: (dx, dy)
2. Chuẩn hóa vector: (dx/distance, dy/distance)
3. Nhân với tốc độ đạn: velocity = normalized * speed
4. Cập nhật vị trí mỗi frame: pos += velocity
- Độ phức tạp: O(1)
```

---

## IX. TÍNH NĂNG KỸ THUẬT NỔI BẬT

### 9.1. Hệ thống vật lý thực tế
- ✅ Mô phỏng trọng lực chính xác
- ✅ Giới hạn tốc độ rơi tự nhiên
- ✅ Ma sát làm chậm dần chuyển động
- ✅ Nhảy có độ cao và thời gian thực tế

### 9.2. Va chạm chính xác
- ✅ Kiểm tra 4 góc của hitbox
- ✅ Phân biệt va chạm ngang và dọc
- ✅ Xử lý va chạm đa đối tượng
- ✅ Không có bug xuyên tường

### 9.3. AI quái vật thông minh
- ✅ Tuần tra tự động không cần input
- ✅ Tránh rơi xuống bờ vực
- ✅ Đổi hướng khi gặp chướng ngại
- ✅ Hiển thị thanh máu trực quan

### 9.4. Giao diện người dùng
- ✅ UI bar hiển thị thông tin real-time
- ✅ Thanh HP, số chìa khóa, điểm số
- ✅ Hướng dẫn điều khiển trên màn hình
- ✅ Màn hình thắng/thua rõ ràng

---

## X. KIẾN THỨC ÁP DỤNG

### 10.1. Lập trình C/C++
- ✅ Cấu trúc dữ liệu (struct)
- ✅ Mảng 1 chiều và 2 chiều
- ✅ Vòng lặp và câu lệnh điều kiện
- ✅ Hàm và module hóa code
- ✅ Con trỏ và tham chiếu

### 10.2. Đồ họa máy tính
- ✅ Vẽ hình cơ bản (rectangle, circle, line)
- ✅ Tô màu và fill pattern
- ✅ Hệ tọa độ 2D
- ✅ Double buffering (cleardevice)
- ✅ Xử lý màu sắc

### 10.3. Game Development
- ✅ Game loop cơ bản
- ✅ FPS control (delay)
- ✅ Input handling (keyboard, mouse)
- ✅ Collision detection
- ✅ Game state management

### 10.4. Thuật toán
- ✅ Tính khoảng cách Euclidean
- ✅ Vector và chuẩn hóa vector
- ✅ Pathfinding đơn giản (AI)
- ✅ Quản lý object pool (bullets)

---

## XI. HƯỚNG PHÁT TRIỂN

### 11.1. Tính năng có thể thêm
- [ ] **Nhiều level**: Thiết kế 5-10 màn chơi khác nhau
- [ ] **Hệ thống vũ khí**: Súng máy, rocket launcher, laser
- [ ] **Power-ups**: Tăng tốc, bất tử, tăng sát thương
- [ ] **Boss fight**: Quái vật khổng lồ cuối màn
- [ ] **Lưu/Load game**: Checkpoint system
- [ ] **Bảng xếp hạng**: High score table
- [ ] **Âm thanh**: Nhạc nền và sound effects
- [ ] **Animation**: Sprite sheets cho nhân vật
- [ ] **Nhiều loại quái**: Flying enemy, shooting enemy
- [ ] **Nhiệm vụ phụ**: Bonus objectives

### 11.2. Cải tiến kỹ thuật
- [ ] **Tối ưu collision**: Spatial partitioning
- [ ] **Particle effects**: Explosion, dust, blood
- [ ] **Camera follow**: Smooth camera tracking player
- [ ] **Parallax scrolling**: Background layers
- [ ] **Sprite animation**: Frame-based animation
- [ ] **Config file**: JSON/XML settings
- [ ] **Map editor**: Tool để thiết kế map
- [ ] **Networking**: Multiplayer mode

---

## XII. KẾT LUẬN

### 12.1. Ưu điểm
✅ **Code rõ ràng**: Dễ đọc, dễ hiểu, có comment đầy đủ  
✅ **Gameplay hấp dẫn**: Kết hợp nhiều yếu tố: parkour, combat, puzzle  
✅ **Vật lý thực tế**: Mô phỏng chuyển động tự nhiên  
✅ **Map rộng lớn**: 40×28 tiles, nhiều tầng, nhiều thử thách  
✅ **AI thông minh**: Quái vật có hành vi tự động hợp lý  
✅ **Mở rộng dễ dàng**: Cấu trúc code module, dễ thêm tính năng  

### 12.2. Ứng dụng học tập
Game này phù hợp cho:
- 📚 Đồ án môn **Lập trình C/C++**
- 📚 Đồ án môn **Kỹ thuật lập trình**
- 📚 Đồ án môn **Đồ họa máy tính**
- 📚 Đồ án môn **Cấu trúc dữ liệu và giải thuật**
- 📚 Học về **Game Development** cơ bản
- 📚 Thực hành **Lập trình hướng đối tượng**

### 12.3. Đánh giá
Game Parkour 2D là một dự án hoàn chỉnh, thể hiện được kiến thức toàn diện về lập trình C/C++, đồ họa máy tính và game development. Với map rộng gấp đôi, 6 quái vật, 3 chìa khóa và hệ thống vật lý thực tế, game mang lại trải nghiệm chơi thú vị và đầy thử thách.

---

**Phát triển bởi**: [Tên sinh viên]  
**MSSV**: [Mã số sinh viên]  
**Lớp**: [Lớp học]  
**Môn học**: Lập trình C/C++  
**Năm học**: 2024-2025  
**Ngày hoàn thành**: 27/01/2026

---

© 2026 - Game Parkour 2D. All rights reserved.
