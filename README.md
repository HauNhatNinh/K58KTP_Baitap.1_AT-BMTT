# K58KTP_Baitap.1_AT-BMTT
## CÁC PHƯƠNG PHÁP MÃ HÓA CỔ ĐIỂN
_____
### 1.Caesar (Caesar cipher)
#### Tên gọi
Caesar cipher — đặt theo tên Julius Caesar, phương pháp dịch chữ theo một số vị trí cố định.

#### Thuật toán

Mã hoá: với mỗi ký tự chữ cái c (A–Z hoặc a–z), đưa về 0..25 rồi tính:
E(c) = (c_index + k) mod 26
(với k là khoá số, dịch bao nhiêu vị trí).

Giải mã:
D(C) = (C_index - k + 26) mod 26
(hoặc E(..., 26 - k)).

#### Không gian khoá

k ∈ {0,1,...,25}. Kích thước khoá: 26 khả năng (thực tế chỉ 25 khác nhau nếu coi k=0 là vô hiệu).

#### Cách phá (không cần khoá)

Brute force: thử 25 hoán vị — cực nhanh.

Phân tích tần suất: kiểm tra xem dịch nào làm cho phân bố chữ cái giống tiếng nguồn (ví dụ chữ 'E' phổ biến trong tiếng Anh).

### Kết luận: rất yếu, dễ phá bằng tay hoặc script.
_____
### 2.Affine cipher
#### Tên gọi
Affine cipher — là một dạng biến đổi affine tuyến tính trên trường modulo 26.

#### Thuật toán

- Với mỗi ký tự x (0..25), khoá gồm hai số a và b (a phải nghịch đảo modulo 26):

 Mã hoá: E(x) = (a * x + b) mod 26

 Giải mã: cần a_inv = a^(-1) mod 26, rồi D(y) = a_inv * (y - b) mod 26.

- Ràng buộc

 a phải thỏa gcd(a,26) = 1 để tồn tại nghịch đảo. Các giá trị a hợp lệ: {1,3,5,7,9,11,15,17,19,21,23,25} (12 giá trị). b ∈ {0..25}.

#### Không gian khoá

Tổng số khoá hợp lệ = 12 × 26 = 312.

#### Cách phá (không cần khoá)

Brute force: thử tất cả 312 cặp (a,b) — khả thi bằng script.

Phân tích tần suất: chuyển đổi affine là ánh xạ một-chữ sang một-chữ; tần suất chữ cái còn nguyên, nên có thể dùng tần suất để khớp.

Known-plaintext hay cribs (đoán một từ) sẽ nhanh tìm (a,b).

### Kết luận: yếu trước brute-force và phân tích tần suất.
_____
