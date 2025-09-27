# K58KTP_Baitap.1_AT-BMTT
## CÁC PHƯƠNG PHÁP MÃ HÓA CỔ ĐIỂN
_____
### 1.Caesar (Caesar cipher)
#### Tên gọi
Caesar cipher — đặt theo tên Julius Caesar, phương pháp dịch chữ theo một số vị trí cố định.

#### Thuật toán

- Mã hoá: với mỗi ký tự chữ cái c (A–Z hoặc a–z), đưa về 0..25 rồi tính:
E(c) = (c_index + k) mod 26
(với k là khoá số, dịch bao nhiêu vị trí).

- Giải mã:
D(C) = (C_index - k + 26) mod 26
(hoặc E(..., 26 - k)).

#### Không gian khoá

- k ∈ {0,1,...,25}. Kích thước khoá: 26 khả năng (thực tế chỉ 25 khác nhau nếu coi k=0 là vô hiệu).

#### Cách phá (không cần khoá)

Brute force: thử 25 hoán vị — cực nhanh.

Phân tích tần suất: kiểm tra xem dịch nào làm cho phân bố chữ cái giống tiếng nguồn (ví dụ chữ 'E' phổ biến trong tiếng Anh).

### Kết luận: rất yếu, dễ phá bằng tay hoặc script.
##### Mã hóa và giải mã Caesar bằng html+css+javascript
<img width="1042" height="730" alt="image" src="https://github.com/user-attachments/assets/580231f0-650c-4778-b4b7-f145595fd0e9" />

##### Mã hóa và giải mã Caesar bằng C++
<img width="271" height="606" alt="image" src="https://github.com/user-attachments/assets/455999df-966f-44bd-b98f-6d01d4b5d861" />

_____
### 2.Affine cipher
#### Tên gọi
Affine cipher — là một dạng biến đổi affine tuyến tính trên trường modulo 26.

#### Thuật toán

- Với mỗi ký tự x (0..25), khoá gồm hai số a và b (a phải nghịch đảo modulo 26):

   - Mã hoá: E(x) = (a * x + b) mod 26

   - Giải mã: cần a_inv = a^(-1) mod 26, rồi D(y) = a_inv * (y - b) mod 26.

- Ràng buộc

 a phải thỏa gcd(a,26) = 1 để tồn tại nghịch đảo. Các giá trị a hợp lệ: {1,3,5,7,9,11,15,17,19,21,23,25} (12 giá trị). b ∈ {0..25}.

#### Không gian khoá

Tổng số khoá hợp lệ = 12 × 26 = 312.

#### Cách phá (không cần khoá)

Brute force: thử tất cả 312 cặp (a,b) — khả thi bằng script.

Phân tích tần suất: chuyển đổi affine là ánh xạ một-chữ sang một-chữ; tần suất chữ cái còn nguyên, nên có thể dùng tần suất để khớp.

Known-plaintext hay cribs (đoán một từ) sẽ nhanh tìm (a,b).

### Kết luận: yếu trước brute-force và phân tích tần suất.
##### Mã hóa và giải mã Affine cipher bằng html+css+javascript
<img width="1104" height="812" alt="image" src="https://github.com/user-attachments/assets/6a187565-3921-4ca5-a6d0-bf5e8ca51b1c" />

##### Mã hóa và giải mã Affine cipher bằng C++
<img width="367" height="611" alt="image" src="https://github.com/user-attachments/assets/13b94da7-f68f-4e32-94b3-3d81804306dd" />

_____
### 3.Hoán vị (Transposition / Permutation cipher)
#### Tên gọi
Hoán vị (Columnar transposition, block permutation…) — giữ nguyên ký tự nhưng thay đổi vị trí theo một hoán vị cố định.

#### Thuật toán (một dạng đơn giản: block permutation)

Chia plaintext thành khối độ dài n (padding nếu cần). Khoá là một hoán vị P của n chỉ số (ví dụ [2,0,1] nghĩa vị trí 0 → 2, 1 → 0, 2 → 1).

- Mã hoá: với mỗi khối B[0..n-1], tạo C[j] = B[P[j]].

- Giải mã: dùng hoán vị nghịch P_inv để đảo lại: B[P[j]] = C[j] hoặc B[j] = C[P_inv[j]].

#### Không gian khoá

- Độ dài khoá n → số hoán vị = n!. (Ví dụ n=8 thì 8! = 40320; n=10 thì 10! ≈ 3.6M)

#### Cách phá (không cần khoá)

Phân tích cấu trúc: vì transposition giữ tần suất chữ cái, ta không thể dùng phân tích tần suất một-chữ để giải. Tuy nhiên:

Kỹ thuật xâu đoán (cribs): nếu đoán được một từ/cụm từ xuất hiện, có thể tìm hoán vị khớp.

Chuẩn hoá dòng/cột (columnar): với columnar transposition, người ta thử độ dài cột, ghép các cột và kiểm tra xem xuất hiện từ hợp lý.

Heuristics và search (hill-climbing / simulated annealing): dùng hàm mục tiêu dựa trên xác suất n-gram (bi-gram, tri-gram) để tối ưu hoán vị. Đây là cách thường dùng cho hoán vị dài.

### Kết luận: khó hơn substitution, nhưng với tính toán hiện đại và heuristics có thể phá được nếu văn bản dài.
##### Mã hóa và giải mã Hoán vị (Transposition / Permutation cipher) bằng html+css+javascript
<img width="1095" height="802" alt="image" src="https://github.com/user-attachments/assets/d2c82716-918c-46f1-8709-a65306ca5329" />

##### Mã hóa và giải mã Hoán vị (Transposition / Permutation cipher) bằng C++
- Đang lỗi, cần sửa.
_____
### 4.Vigenère cipher
#### Tên gọi
Vigenère cipher — mã hoá bằng bảng Vigenère; gọi là polyalphabetic substitution cipher.

#### Thuật toán

- Khoá là chuỗi ký tự K (ký tự chữ, độ dài L). Lặp khoá dọc theo plaintext.

- Mỗi ký tự plaintext P_i (0..25) được mã hoá:
E(P_i) = (P_i + K_{i mod L}) mod 26 (với K_j là giá trị 0..25 tương ứng ký tự khoá).

- Giải mã: D(C_i) = (C_i - K_{i mod L} + 26) mod 26.

#### Không gian khoá

- Với khoá chiều dài L, số khoá = 26^L. Nếu L không giới hạn, khoá không gian lớn; thực tế người dùng thường chọn L nhỏ → dễ tấn công.

#### Cách phá (không cần khoá)

Kasiski examination: tìm khoảng cách giữa các chuỗi trùng lặp trong ciphertext — khoảng cách thường chia hết cho chiều dài khoá; giúp suy đoán L.

Friedman test (Index of Coincidence): ước lượng chiều dài khoá bằng IC.

Sau khi biết L: ta tách ciphertext thành L dãy (mỗi dãy là Caesar cipher) → áp dụng phân tích tần suất cho từng dãy để tìm dịch (shift) tương ứng.

Brute force: nếu L nhỏ, thử tất cả 26^L.

Kasiski + frequency analysis là phương pháp cổ điển và hiệu quả.

### Kết luận: dễ bị phá nếu khoá ngắn hoặc có ciphertext dài; nếu khoá dài và ngẫu nhiên (one-time pad) thì an toàn.
##### Mã hóa và giải mã Vigenère cipher bằng html+css+javascript
<img width="1112" height="804" alt="image" src="https://github.com/user-attachments/assets/8426aa58-f76f-4094-a32f-95128c3e2465" />

##### Mã hóa và giải mã Vigenère cipher bằng C++
<img width="283" height="598" alt="image" src="https://github.com/user-attachments/assets/9c8158ac-db61-416d-b0d9-3f1d86464822" />
_____
### 5.Playfair cipher
#### Tên gọi
Playfair cipher — mã hoá theo cặp ký tự (digraph), dùng bảng 5×5 sinh từ khoá.

#### Thuật toán (phổ biến nhất, J ≡ I)

- Tạo ma trận 5×5 từ khóa (loại bỏ chữ trùng, nối phần còn lại của bảng chữ cái, thường gộp J với I).

- Chuẩn hoá plaintext:

  - Loại bỏ ký tự không phải chữ (tuỳ biến),

  - Viết chữ thường, thay j bằng i,

  - Chia thành digraphs (cặp). Nếu trong một cặp hai chữ giống nhau, chèn x giữa (hoặc chữ khác) rồi tiếp tục. Nếu cuối cùng còn 1 ký tự, padding x.

- Mã hoá một cặp (A,B): tìm vị trí (r1,c1) và (r2,c2) trong ma trận:

  - Nếu cùng hàng: thay bằng ký tự bên phải (vòng lại).

  - Nếu cùng cột: thay bằng ký tự bên dưới (vòng lại).

  - Nếu khác hàng và cột: thay bằng hai ký tự ở các góc của chữ nhật (r1,c2) và (r2,c1).

- Giải mã: quy tắc ngược (trái / trên / hoán chéo).

#### Không gian khoá

- Ma trận là một sắp xếp của 25 chữ cái (J bị loại) → số ma trận = 25! ≈ 1.5511210043 × 10^25. (Rất lớn)

- Lưu ý: một số ma trận có thể tạo cùng ánh xạ do cách chuẩn hoá, nhưng độ lớn vẫn cực kỳ lớn.

#### Cách phá (không cần khoá)

Không phải substitution đơn ký tự, Playfair bảo vệ chống phân tích tần suất một-chữ. Tuy nhiên:

Phân tích digraph (cặp chữ): tần suất bigram không đồng đều; có thể dùng thống kê digram để tìm ma trận gần đúng.

Chiến lược heuristic / hill-climbing: dùng hàm mục tiêu dựa trên xác suất n-gram (bigram/trigram/quadgram) và tối ưu hoán vị ma trận (hoán đổi 2 chữ cái, đánh giá score); phương pháp này thường phá được Playfair với ciphertext đủ dài.

Known-plaintext / crib: nếu biết một đoạn plaintext tương ứng, dễ suy ma trận.

### Kết luận: mạnh hơn các substitution đơn, nhưng vẫn có thể phá bằng search heuristics khi ciphertext đủ dài.
##### Mã hóa và giải mã Playfair cipher bằng html+css+javascript
<img width="1108" height="792" alt="image" src="https://github.com/user-attachments/assets/990c94f3-e9c8-4459-9fe0-d9d10a71994c" />

##### Mã hóa và giải mã Playfair cipher bằng C++
<img width="289" height="608" alt="image" src="https://github.com/user-attachments/assets/0beec1ab-9d06-423e-811e-bd235b97a30c" />

