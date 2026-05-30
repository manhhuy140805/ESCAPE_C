# Đánh Giá Đồ Án (Dựa trên YEU_CAU.md)

Dưới đây là phần đánh giá các yêu cầu trong file `docs/YEU_CAU.md` kèm theo dẫn chứng cụ thể vị trí tương ứng trong mã nguồn dự án.

## ĐIỂM TP2: CÀI ĐẶT THUẬT TOÁN VẼ ĐOẠN THẲNG/ĐƯỜNG TRÒN (CHƯƠNG 2)

### 1. Tự cài đặt Thuật toán Vẽ đường thẳng, đường tròn (Bresenham/Midpoint)
- **Trạng thái đánh giá:** Đạt mức Tốt (8.5 - 10)
- **Vị trí code minh chứng:** 
  - File `src/core/algorithms.h`: 
    - Hàm `bresenhamLine()` tự cài đặt thuật toán Bresenham cho mọi trường hợp (có phân chia rõ ràng `trường hợp 1: dx >= dy` và `trường hợp 2`).
    - Hàm `midpointCircle()` và `midpointEllipse()` tự cài đặt thuật toán Midpoint hoàn chỉnh.
  - File `src/graphics/CustomDrawing.h`: 
    - Các thuật toán này được áp dụng mượt mà để vẽ nhân vật, quái vật, đạn, chìa khóa (ví dụ: `drawCustomPlayer`, `drawCustomEnemy`, `drawCustomKey`).
  - Code có chú thích giải thích rõ ràng cho từng phần.

### 2. Thuật toán Tô màu đa giác
- **Trạng thái đánh giá:** Đạt mức Tốt (8.5 - 10)
- **Vị trí code minh chứng:** 
  - File `src/core/algorithms.h`:
    - Cài đặt thành công thuật toán `floodFillRecursive()` và `floodFill8Recursive()` đệ quy theo 4 hướng và 8 hướng. Thuật toán tự động tìm biên (so sánh `oldColor` và `fillColor`) để lấp đầy chính xác.
    - Cài đặt thêm các hàm bọc như `filledPolygon()`, `filledTriangle()` để kết hợp vẽ viền đa giác và tô màu tùy ý dựa trên điểm gieo mầm `seed`.
  - File `src/graphics/CustomDrawing.h`: Áp dụng để tô màu nhân vật và môi trường game cực kỳ đa dạng (ví dụ: `drawFilledPlayer`, `drawFilledEnemy`, `drawFilledTree`, v.v.).

### 3. Tính thẩm mỹ & Giao diện Game
- **Trạng thái đánh giá:** Đạt mức Tốt (8.5 - 10)
- **Vị trí code minh chứng:** 
  - File `src/levels/LevelCommon.h`: Hệ thống hiển thị điểm số (HUD), số lượng chìa khóa, thông báo Pause và màn hình Win/Lose được căn chỉnh chữ cực kỳ chỉn chu bằng hàm `outtextxy()` kết hợp `textwidth()` để căn giữa.
  - Các hình ảnh nhân vật và vật thể vẽ tay phối màu RGB hài hòa. Kỹ thuật tô màu kết hợp vẽ viền không gây ra tình trạng màu loang lổ hay răng cưa quá mức.

---

## ĐIỂM TP3: HÌNH HỌC FRACTAL (CHƯƠNG 3)

### 1. Kỹ thuật cài đặt Đệ quy Fractal
- **Trạng thái đánh giá:** Đạt mức Tốt (8.5 - 10)
- **Vị trí code minh chứng:** 
  - File `src/core/fractals.h` chứa cài đặt chính xác các hàm đệ quy:
    - `drawKochCurve()` (đường cong Koch)
    - `drawKochSnowflake()` (bông tuyết Koch)
    - `drawDragonCurve()` (đường cong Rồng)
    - `drawFractalTree()` (cây Fractal)
  - Các hàm đều sử dụng thuật toán đệ quy rõ ràng, sử dụng tham số `depth` để giới hạn số lần gọi đệ quy, đảm bảo không bị tràn bộ nhớ hay treo máy.

### 2. Ứng dụng Fractal vào bối cảnh Game
- **Trạng thái đánh giá:** Đạt mức Tốt (8.5 - 10)
- **Vị trí code minh chứng:**
  - File `src/core/decorations.h` lồng ghép các hình Fractal vào làm chi tiết trang trí cảnh quan.
  - Ví dụ:
    - `drawKochSnowflake` dùng để trang trí các tinh thể tuyết bay lơ lửng.
    - `drawDragonCurve` và `drawKochCurve` tạo nên các đường nét hoa văn bám trên các bức tường, rạn đá.

### 3. Tính thẩm mỹ & Độ sắc nét
- **Trạng thái đánh giá:** Đạt mức Tốt (8.5 - 10)
- Hình ảnh hiển thị sắc nét nhờ thuật toán vẽ đường thẳng `bresenhamLine` tự cài đặt (không bị đứt khúc). Màu sắc hài hòa (sử dụng phối màu RGB mượt mà) tạo nền game ấn tượng, không gây rối mắt hay cản trở gameplay.

---

## ĐIỂM TP4: PHÉP BIẾN ĐỔI 2 CHIỀU

### 1. Vận dụng chuyển động Affine vào Game
- **Trạng thái đánh giá:** Đạt mức Tốt (8.5 - 10)
- **Vị trí code minh chứng:**
  - File `src/graphics/CustomDrawing.h`: 
    - Hàm `transformPoint2D()` cài đặt toán học ma trận của phép biến đổi Affine (Tịnh tiến, Quay, Co giãn) bằng các hàm lượng giác `cos/sin`.
    - Hàm `drawAffineKey()` áp dụng phép biến đổi này: sử dụng `cos(spin)` làm phép co giãn trục X (Scale X) và `sin` để dịch chuyển trục Y, tạo ra hiệu ứng hoạt hình quay 3D (fake 3D) và lơ lửng mượt mà cho vật thể chìa khóa.
  - File `src/entities/Items.h` (dòng 24): Sử dụng `drawAffineKey` liên tục với biến đếm frame để tạo hoạt ảnh.

### 2. Tương tác người dùng & Đa dạng tốc độ
- **Trạng thái đánh giá:** Đạt mức Tốt (8.5 - 10)
- **Vị trí code minh chứng:**
  - File `src/levels/LevelCommon.h`:
    - Hàm `handleSpeedControlKeys()` trực tiếp nhận phím bấm của người dùng (`0`, `1`, `2`, `3`) để thay đổi tốc độ toàn game tương ứng:
      - 0 - Dừng (`GAME_SPEED_MULTIPLIER = 0.0f`)
      - 1 - Chậm (`0.55f`)
      - 2 - Nhanh chuẩn (`1.0f`)
      - 3 - Rất Nhanh (`1.65f`)
  - Biến `GAME_SPEED_MULTIPLIER` được nhân thẳng vào vận tốc di chuyển, tốc độ đạn rơi và AI của quái vật.
  - Có hiển thị tốc độ trên màn hình HUD.

### 3. Hiệu ứng Hình ảnh & Âm thanh
- **Trạng thái đánh giá:** Đạt mức Tốt (8.5 - 10)
- **Vị trí code minh chứng:**
  - File `src/core/sound.h`: Khởi tạo và phát âm thanh bằng Windows Multimedia API (`mciSendString`).
  - Âm thanh được lồng ghép đa dạng, khớp với hành động:
    - Lấy chìa khóa (`playCollectSound`), mở cửa trong `LevelCommon.h`.
    - Bắn đạn, bắn rocket trong `ShootingSystem.h`.
    - Âm thanh Win/Lose khác biệt trong `showEndScreen()`.
  - Hình ảnh chuyển động vô cùng mượt mà do trò chơi đã triển khai cơ chế Double Buffering (file `src/core/doublebuffer.h`), giúp xóa bỏ hoàn toàn hiện tượng nhấp nháy, bóng ma (ghosting) thường gặp trên console.
