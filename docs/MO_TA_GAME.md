# 🎮 ESCAPE THE LABYRINTH - HƯỚNG DẪN CHƠI GAME

<div align="center">

**GAME PARKOUR 2D - MÊ CUNG PHIÊU LƯU**

*Một trò chơi phiêu lưu hành động 2D được phát triển bằng C/C++ với WinBGIM*

---

[![Language](https://img.shields.io/badge/Language-C%2FC%2B%2B-blue.svg)](https://isocpp.org/)
[![Graphics](https://img.shields.io/badge/Graphics-WinBGIM-green.svg)](http://winbgim.codecutter.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)
[![Status](https://img.shields.io/badge/Status-Complete-success.svg)]()

</div>

---

## 📖 MỤC LỤC

1. [Giới thiệu](#-giới-thiệu)
2. [Cài đặt & Chạy game](#-cài-đặt--chạy-game)
3. [Cách chơi](#-cách-chơi)
4. [Hệ thống game](#-hệ-thống-game)
5. [Các màn chơi](#-các-màn-chơi)
6. [Mẹo & Chiến thuật](#-mẹo--chiến-thuật)
7. [Công nghệ](#-công-nghệ)
8. [Credits](#-credits)

---

## 🎯 GIỚI THIỆU

### Câu chuyện
Bạn là một nhà thám hiểm dũng cảm bị mắc kẹt trong một mê cung bí ẩn đầy rẫy nguy hiểm. Để thoát ra, bạn phải thu thập đủ 3 chìa khóa vàng để mở cửa thoát. Nhưng hãy cẩn thận - mê cung được canh giữ bởi những kẻ thù nguy hiểm!

### Thể loại
- **Platformer 2D**: Nhảy, leo trèo qua các tầng platform
- **Action-Adventure**: Chiến đấu với quái vật, thu thập vật phẩm
- **Puzzle**: Tìm đường đi, giải quyết thử thách

### Đặc điểm nổi bật
✨ **5 màn chơi** với độ khó tăng dần  
✨ **Vật lý thực tế** - Trọng lực, ma sát, nhảy tự nhiên  
✨ **Hệ thống bắn đạn** - Bắn theo hướng chuột  
✨ **AI quái vật thông minh** - Tuần tra, tránh bờ vực  
✨ **Đồ họa tự vẽ** - Sử dụng thuật toán Bresenham, Midpoint, Flood Fill  
✨ **Hiệu ứng fractal** - Koch curves, Dragon curves trang trí  

---

## 💻 CÀI ĐẶT & CHẠY GAME

### Yêu cầu hệ thống
- **Hệ điều hành**: Windows 7 trở lên
- **Compiler**: MinGW GCC (TDM-GCC-32)
- **Thư viện**: WinBGIM (graphics.h)
- **RAM**: 512 MB trở lên
- **Màn hình**: 1100×800 pixels trở lên

### Cài đặt

#### Bước 1: Clone repository
```bash
git clone https://github.com/your-repo/escape-the-labyrinth.git
cd escape-the-labyrinth
```

#### Bước 2: Build game
```bash
# Chạy file build script
./build.bat

# Hoặc compile thủ công
g++ -g src/main.cpp src/graphics/Menu.cpp -o game.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

#### Bước 3: Chạy game
```bash
./game.exe
```

### Cấu trúc thư mục
```
escape-the-labyrinth/
├── src/                    # Source code
│   ├── main.cpp           # Entry point
│   ├── config.h           # Cấu hình game
│   ├── core/              # Thuật toán core
│   ├── entities/          # Player, Enemy, Items
│   ├── graphics/          # Menu, Drawing
│   ├── levels/            # Logic các màn
│   ├── map/               # Dữ liệu map
│   └── utils/             # Utilities
├── docs/                  # Tài liệu
├── build.bat             # Build script
└── game.exe              # Game executable
```

---

## 🎮 CÁCH CHƠI

### Điều khiển cơ bản

<table>
<tr>
<th>Phím</th>
<th>Chức năng</th>
<th>Mô tả</th>
</tr>
<tr>
<td><kbd>W</kbd> hoặc <kbd>Space</kbd></td>
<td><strong>Nhảy</strong></td>
<td>Nhảy lên cao (chỉ khi đứng trên mặt đất)</td>
</tr>
<tr>
<td><kbd>A</kbd></td>
<td><strong>Di chuyển trái</strong></td>
<td>Chạy sang bên trái</td>
</tr>
<tr>
<td><kbd>D</kbd></td>
<td><strong>Di chuyển phải</strong></td>
<td>Chạy sang bên phải</td>
</tr>
<tr>
<td><kbd>Chuột trái</kbd></td>
<td><strong>Bắn đạn</strong></td>
<td>Bắn theo hướng con trỏ chuột</td>
</tr>
<tr>
<td><kbd>ESC</kbd></td>
<td><strong>Tạm dừng/Thoát</strong></td>
<td>Mở menu tạm dừng hoặc thoát game</td>
</tr>
</table>

### Mục tiêu game

#### 🎯 Mục tiêu chính
1. **Thu thập 3 chìa khóa vàng** 🔑🔑🔑
   - Chìa khóa ẩn ở các vị trí khác nhau trên map
   - Cần đủ 3 chìa để mở cửa thoát

2. **Tìm và mở cửa thoát** 🚪
   - Cửa thường ở góc phải dưới của map
   - Chỉ mở được khi có đủ 3 chìa khóa

3. **Sống sót** ❤️
   - Tránh va chạm với quái vật
   - Giữ HP > 0

#### 🏆 Mục tiêu phụ
- Tiêu diệt quái vật để kiếm điểm (+100 điểm/con)
- Đạt điểm số cao nhất
- Hoàn thành màn với HP tối đa

### Điều kiện thắng/thua

#### ✅ Thắng
- Thu thập đủ 3 chìa khóa
- Đến cửa thoát và mở cửa thành công
- → Hiển thị màn hình **"YOU WIN!"** với điểm số

#### ❌ Thua
- HP giảm xuống 0 (bị quái vật tấn công quá nhiều)
- → Hiển thị màn hình **"GAME OVER!"** với điểm số

---

## 🎲 HỆ THỐNG GAME

### 1. Nhân vật (Player)

<table>
<tr>
<th>Thuộc tính</th>
<th>Giá trị</th>
</tr>
<tr>
<td>Màu sắc</td>
<td>🔵 Xanh dương</td>
</tr>
<tr>
<td>Kích thước</td>
<td>30×40 pixels</td>
</tr>
<tr>
<td>HP ban đầu</td>
<td>❤️ 100</td>
</tr>
<tr>
<td>Tốc độ di chuyển</td>
<td>5 pixels/frame</td>
</tr>
<tr>
<td>Lực nhảy</td>
<td>12 (độ cao ~150 pixels)</td>
</tr>
<tr>
<td>Khả năng đặc biệt</td>
<td>Bắn đạn theo hướng chuột</td>
</tr>
</table>

**Cơ chế vật lý:**
- **Trọng lực**: 0.8 (kéo xuống liên tục)
- **Tốc độ rơi tối đa**: 15 (giới hạn vận tốc)
- **Ma sát**: 0.85 (làm chậm dần khi không di chuyển)
- **Nhảy**: Chỉ khi đứng trên mặt đất

### 2. Quái vật (Enemies)

<table>
<tr>
<th>Thuộc tính</th>
<th>Giá trị</th>
</tr>
<tr>
<td>Màu sắc</td>
<td>🔴 Đỏ</td>
</tr>
<tr>
<td>Kích thước</td>
<td>35×35 pixels</td>
</tr>
<tr>
<td>HP</td>
<td>3 (cần 3 viên đạn để tiêu diệt)</td>
</tr>
<tr>
<td>Tốc độ</td>
<td>2 pixels/frame</td>
</tr>
<tr>
<td>Sát thương</td>
<td>-10 HP/lần chạm</td>
</tr>
<tr>
<td>Điểm thưởng</td>
<td>+100 điểm khi tiêu diệt</td>
</tr>
</table>

**AI quái vật:**
- ✅ Tuần tra tự động qua lại trên platform
- ✅ Phát hiện tường và đổi hướng
- ✅ Phát hiện bờ vực và tránh rơi
- ✅ Hiển thị thanh máu phía trên đầu

### 3. Vật phẩm

#### 🔑 Chìa khóa (Keys)
- **Màu sắc**: Vàng
- **Số lượng**: 3 chìa/màn
- **Điểm thưởng**: +50 điểm/chìa
- **Chức năng**: Cần đủ 3 chìa để mở cửa

#### 🚪 Cửa thoát (Door)
- **Màu sắc**: Xám (đóng) → Xanh lá (mở)
- **Điều kiện**: Cần 3 chìa khóa
- **Điểm thưởng**: +200 điểm khi mở

#### 💥 Đạn (Bullets)
- **Tốc độ**: 10 pixels/frame
- **Sát thương**: 1 HP/viên
- **Giới hạn**: 20 viên cùng lúc
- **Tốc độ bắn**: 5 viên/giây (200ms cooldown)

### 4. Hệ thống điểm

<table>
<tr>
<th>Hành động</th>
<th>Điểm thưởng</th>
</tr>
<tr>
<td>Tiêu diệt quái vật</td>
<td>+100 điểm</td>
</tr>
<tr>
<td>Thu thập chìa khóa</td>
<td>+50 điểm</td>
</tr>
<tr>
<td>Mở cửa thoát</td>
<td>+200 điểm</td>
</tr>
</table>

**Điểm tối đa mỗi màn:**
- Tiêu diệt 6 quái: 6 × 100 = **600 điểm**
- Thu thập 3 chìa: 3 × 50 = **150 điểm**
- Mở cửa: 1 × 200 = **200 điểm**
- **TỔNG**: **950 điểm/màn**

---

## 🗺️ CÁC MÀN CHƠI

### Level 1: Khởi đầu
- **Độ khó**: ⭐ Dễ
- **Kích thước map**: 44×32 tiles
- **Số quái vật**: 6 con
- **Đặc điểm**: Map rộng, nhiều platform, dễ di chuyển
- **Mục tiêu**: Làm quen với điều khiển và cơ chế game

### Level 2: Thử thách
- **Độ khó**: ⭐⭐ Trung bình
- **Kích thước map**: 44×32 tiles
- **Số quái vật**: 8 con
- **Đặc điểm**: Platform hẹp hơn, quái vật nhiều hơn
- **Mục tiêu**: Cải thiện kỹ năng nhảy và bắn

### Level 3: Nguy hiểm
- **Độ khó**: ⭐⭐⭐ Khó
- **Kích thước map**: 44×32 tiles
- **Số quái vật**: 10 con
- **Đặc điểm**: Nhiều bẫy, platform xa nhau
- **Mục tiêu**: Tìm đường đi tối ưu, tránh quái vật

### Level 4: Địa ngục
- **Độ khó**: ⭐⭐⭐⭐ Rất khó
- **Kích thước map**: 44×32 tiles
- **Số quái vật**: 12 con
- **Đặc điểm**: Mê cung phức tạp, quái vật dày đặc
- **Mục tiêu**: Sống sót và hoàn thành màn

### Level 5: Boss Final
- **Độ khó**: ⭐⭐⭐⭐⭐ Cực khó
- **Kích thước map**: 44×32 tiles
- **Số quái vật**: 15 con
- **Đặc điểm**: Màn cuối cùng, thử thách tổng hợp
- **Mục tiêu**: Chinh phục mê cung và thoát ra

---

## 💡 MẸO & CHIẾN THUẬT

### Mẹo chơi game

#### 🎯 Di chuyển
- **Nhảy liên tục**: Giữ nhịp nhảy để di chuyển nhanh hơn
- **Tránh rơi**: Luôn kiểm tra platform phía dưới trước khi nhảy
- **Sử dụng ma sát**: Thả phím để dừng lại chính xác

#### ⚔️ Chiến đấu
- **Bắn từ xa**: Tiêu diệt quái vật từ xa để tránh mất HP
- **Nhắm chính xác**: Di chuyển chuột để bắn chính xác
- **Quản lý đạn**: Tránh bắn liên tục, chờ đạn cũ biến mất
- **Tránh va chạm**: Mỗi lần chạm quái mất 10 HP!

#### 🔑 Thu thập vật phẩm
- **Ưu tiên chìa khóa**: Thu thập chìa khóa trước khi tiêu diệt quái
- **Ghi nhớ vị trí**: Nhớ vị trí cửa thoát để quay lại
- **Khám phá toàn bộ**: Tìm kiếm khắp map để không bỏ sót chìa

#### 🏆 Đạt điểm cao
- **Tiêu diệt tất cả quái**: +100 điểm/con
- **Thu thập đủ 3 chìa**: +150 điểm
- **Hoàn thành nhanh**: Càng nhanh càng tốt
- **Giữ HP cao**: Bonus điểm nếu HP > 80

### Chiến thuật nâng cao

#### 🎮 Kỹ thuật Rocket Jump
- Bắn đạn xuống dưới khi nhảy để nhảy cao hơn
- Hữu ích để lên platform cao

#### 🏃 Speedrun
- Bỏ qua quái vật không cần thiết
- Tìm đường đi ngắn nhất
- Nhảy liên tục để tăng tốc

#### 🛡️ Defensive Play
- Tiêu diệt quái vật trước khi thu thập chìa
- Giữ khoảng cách an toàn
- Luôn có lối thoát

---

## 🔧 CÔNG NGHỆ

### Ngôn ngữ & Thư viện

<table>
<tr>
<th>Công nghệ</th>
<th>Mô tả</th>
</tr>
<tr>
<td><strong>Ngôn ngữ</strong></td>
<td>C/C++ (C++98/C++03 compatible)</td>
</tr>
<tr>
<td><strong>Thư viện đồ họa</strong></td>
<td>WinBGIM (graphics.h)</td>
</tr>
<tr>
<td><strong>Compiler</strong></td>
<td>MinGW GCC (TDM-GCC-32)</td>
</tr>
<tr>
<td><strong>IDE</strong></td>
<td>Dev-C++, Code::Blocks, VS Code</td>
</tr>
<tr>
<td><strong>Platform</strong></td>
<td>Windows 7+</td>
</tr>
</table>

### Thuật toán đã implement

#### 📐 Thuật toán vẽ đường (TP2 - 60%)
- **Bresenham Line Algorithm**: Vẽ đường thẳng
- **Midpoint Circle Algorithm**: Vẽ đường tròn
- **Midpoint Ellipse Algorithm**: Vẽ ellipse
- **Flood Fill Algorithm**: Tô màu đa giác đệ quy

#### 🌿 Thuật toán Fractal (TP3 - 20%)
- **Koch Curve**: Đường cong Koch (tuyết)
- **Dragon Curve**: Đường cong rồng
- **Sierpinski Triangle**: Tam giác Sierpinski

#### 🔄 Phép biến đổi 2D (TP4 - 20%)
- **Translation**: Tịnh tiến
- **Rotation**: Xoay
- **Scaling**: Co giãn
- **Reflection**: Đối xứng

### Cấu trúc code

```
src/
├── main.cpp              # Entry point, game loop
├── config.h              # Cấu hình game
│
├── core/                 # Core systems
│   ├── algorithms.h      # Bresenham, Midpoint, Flood Fill
│   ├── blocks.h          # Tile rendering
│   ├── decorations.h     # Fractal decorations
│   ├── doublebuffer.h    # Double buffering
│   └── primitives.h      # Basic shapes
│
├── entities/             # Game entities
│   ├── Player.h          # Player logic
│   ├── Enemy.h           # Enemy AI
│   └── Items.h           # Keys, doors
│
├── graphics/             # Graphics & UI
│   ├── Menu.h/.cpp       # Menu system
│   └── CustomDrawing.h   # Custom drawing functions
│
├── levels/               # Level logic
│   ├── Level1.h          # Level 1 gameplay
│   ├── Level2.h          # Level 2 gameplay
│   ├── Level3.h          # Level 3 gameplay
│   ├── Level4.h          # Level 4 gameplay
│   ├── Level5.h          # Level 5 gameplay
│   └── LevelCommon.h     # Shared utilities
│
├── map/                  # Map data
│   ├── Level1.h          # Level 1 map
│   ├── Level2.h          # Level 2 map
│   ├── Level3.h          # Level 3 map
│   ├── Level4.h          # Level 4 map
│   └── Level5.h          # Level 5 map
│
└── utils/                # Utilities
    └── ShootingSystem.h  # Bullet system
```

### Tính năng kỹ thuật

#### ✨ Vật lý thực tế
- Mô phỏng trọng lực chính xác
- Giới hạn tốc độ rơi tự nhiên
- Ma sát làm chậm dần chuyển động
- Nhảy có độ cao và thời gian thực tế

#### 🎯 Va chạm chính xác
- Kiểm tra 4 góc của hitbox
- Phân biệt va chạm ngang và dọc
- Xử lý va chạm đa đối tượng
- Không có bug xuyên tường

#### 🤖 AI quái vật thông minh
- Tuần tra tự động không cần input
- Tránh rơi xuống bờ vực
- Đổi hướng khi gặp chướng ngại
- Hiển thị thanh máu trực quan

#### 🎨 Đồ họa tự vẽ
- Tất cả hình vẽ sử dụng thuật toán tự implement
- Không dùng hàm vẽ có sẵn của BGI
- Áp dụng Bresenham, Midpoint, Flood Fill
- Hiệu ứng fractal trang trí

---

## 👥 CREDITS

### Đội ngũ phát triển
**Escape The Labyrinth Team**

### Công nghệ
- **WinBGIM**: Thư viện đồ họa
- **MinGW GCC**: Compiler
- **C/C++**: Ngôn ngữ lập trình

### Tài liệu tham khảo
- Bresenham, J. E. (1965). "Algorithm for computer control of a digital plotter"
- Midpoint Circle Algorithm
- Flood Fill Algorithm
- Koch Curve, Dragon Curve
- 2D Transformations

### Học phần
- **Môn học**: Tin Học Đồ Họa Máy Tính
- **Năm học**: 2026
- **Mục đích**: Đồ án cuối kỳ

---

## 📞 HỖ TRỢ

### Báo lỗi
Nếu gặp lỗi, vui lòng tạo issue trên GitHub với thông tin:
- Mô tả lỗi
- Các bước tái hiện
- Screenshot (nếu có)
- Thông tin hệ thống

### Đóng góp
Mọi đóng góp đều được hoan nghênh! Vui lòng:
1. Fork repository
2. Tạo branch mới
3. Commit changes
4. Push và tạo Pull Request

---

## 📜 LICENSE

© 2026 - Escape The Labyrinth. All rights reserved.

Dự án được phát triển cho mục đích học tập.

---

<div align="center">

**🎮 CHÚC BẠN CHƠI GAME VUI VẺ! 🎮**

*Nếu thích game, đừng quên cho ⭐ trên GitHub!*

</div>
