# DE CUONG DE TAI NGHIEN CUU KHOA HOC SINH VIEN

## 1. Thong tin chung

**Ten de tai:** Nghien cuu, thiet ke va che tao mo hinh robot hai banh tu hanh dieu khien theo chuoi lenh voi thuat toan lap quy dao va PID tren nen tang ESP32-C3.

**Linh vuc KHCN:** Ky thuat dieu khien, tu dong hoa, robot di dong, he thong nhung.

**Cap quan ly:** De tai nghien cuu khoa hoc sinh vien.

**Muc kinh phi du kien:** 7.000.000 VND.

**Thoi gian thuc hien du kien:** 04/2026 - 11/2026.

**Sinh vien thuc hien:** [Dien ho ten sinh vien]

**Lop/Khoa:** [Dien lop, khoa]

**Giang vien huong dan:** [Dien ho ten giang vien huong dan]

## 2. Tom tat de tai

De tai tap trung nghien cuu va xay dung mo hinh robot hai banh su dung vi dieu khien ESP32-C3, driver dong co, encoder va cum nut nhan analog de dieu khien robot theo chuoi lenh. Nguoi dung co the nhap cac lenh di chuyen nhu tien, lui, quay trai, quay phai. He thong ghi lai chuoi lenh, toi uu cac lenh lap lien tiep, chuyen doi lenh thanh quy dao chuyen dong cho tung banh, sau do dieu khien dong co bang bo dieu khien PID dua tren phan hoi encoder.

San pham cua de tai la mot mo hinh robot hai banh co kha nang thuc hien chuoi lenh da nhap, co cau truc phan mem ro rang gom cac khoi: doc lenh, toi uu lenh, lap quy dao, doc encoder, tinh PID va xuat PWM dieu khien dong co. De tai co tinh ung dung trong giang day, thuc hanh dieu khien tu dong, robot co ban va he thong nhung.

## 3. Tinh cap thiet

Robot di dong la mot huong nghien cuu quan trong trong linh vuc tu dong hoa va he thong nhung. Cac bai toan nhu dieu khien toc do, dieu khien vi tri, lap quy dao, doc cam bien phan hoi va xu ly lenh nguoi dung la nhung noi dung cot loi trong dao tao ky thuat dieu khien.

Trong thuc te hoc tap, sinh vien thuong tiep can tung phan rieng le nhu lap trinh vi dieu khien, doc encoder, PWM hoac PID, nhung chua co nhieu mo hinh tich hop day du quy trinh tu nhap lenh den dieu khien chuyen dong. Vi vay, viec xay dung mot robot hai banh co kha nang ghi chuoi lenh, toi uu lenh va dieu khien bam quy dao bang PID giup tao ra mot nen tang thuc hanh truc quan, de mo rong va phu hop voi dieu kien nghien cuu sinh vien.

## 4. Muc tieu nghien cuu

### 4.1. Muc tieu tong quat

Thiet ke va che tao mo hinh robot hai banh dieu khien bang ESP32-C3, co kha nang nhan chuoi lenh tu nguoi dung, lap quy dao chuyen dong va dieu khien dong co bang PID dua tren phan hoi encoder.

### 4.2. Muc tieu cu the

- Nghien cuu nguyen ly dieu khien robot hai banh vi sai.
- Xay dung mach dieu khien su dung ESP32-C3, driver dong co DC va encoder.
- Thiet ke khoi nhap lenh bang cum nut analog.
- Xay dung thuat toan ghi, luu va toi uu chuoi lenh di chuyen.
- Xay dung thuat toan lap quy dao cho hai banh theo cac lenh tien, lui, quay trai, quay phai.
- Xay dung bo dieu khien PID dieu khien vi tri/toc do dong co dua tren encoder.
- Thu nghiem, danh gia kha nang robot thuc hien chuoi lenh va do on dinh cua he thong.

## 5. Doi tuong va pham vi nghien cuu

**Doi tuong nghien cuu:**

- Mo hinh robot hai banh vi sai.
- He thong dieu khien dong co DC co encoder.
- Thuat toan lap quy dao va dieu khien PID tren vi dieu khien ESP32-C3.

**Pham vi nghien cuu:**

- Robot hoat dong trong moi truong phong thi nghiem, mat san phang.
- Cac lenh chuyen dong co ban gom tien, lui, quay trai, quay phai va dung.
- Tap trung vao dieu khien theo chuoi lenh nhap truoc, chua mo rong sang tu hanh tranh vat can hoac dinh vi ban do.

## 6. Noi dung nghien cuu

### Noi dung 1: Nghien cuu tong quan

- Tim hieu robot hai banh vi sai va cac bai toan dieu khien chuyen dong.
- Tim hieu nguyen ly hoat dong cua encoder, driver dong co va PWM.
- Tim hieu bo dieu khien PID va phuong phap lap quy dao don gian cho robot di dong.

### Noi dung 2: Thiet ke phan cung

- Lua chon vi dieu khien ESP32-C3 lam bo xu ly trung tam.
- Ket noi driver dong co, dong co DC, encoder va cum nut analog.
- Xac dinh cac chan tin hieu trong file `include/PinConfig.h`.
- Xac dinh cac thong so robot nhu duong kinh banh xe, so xung encoder, khoang cach di chuyen moi lenh va khoang xoay trong `include/RobotConfig.h`.

### Noi dung 3: Xay dung phan mem dieu khien

- Xay dung module doc phim analog trong `lib/matrix`.
- Xay dung FSM ghi va xu ly lenh trong `src/read_command.cpp` voi cac trang thai `IDLE`, `RECORD`, `HANDLE`, `PLAYING`, `ERR`.
- Toi uu chuoi lenh lien tiep thanh dang lenh kem so lan lap.
- Xay dung module quy doi dong hoc trong `include/Kinematics.h`.
- Xay dung module lap quy dao trong `lib/control/trajectory.cpp`.
- Xay dung module PID trong `lib/control/pid.cpp`.
- Xay dung module encoder va xuat PWM trong `lib/motor/motor.cpp`.

### Noi dung 4: Thu nghiem va danh gia

- Thu nghiem nhap chuoi lenh tien, lui, quay trai, quay phai.
- Danh gia kha nang toi uu chuoi lenh lap.
- Danh gia sai so vi tri dua tren gia tri encoder.
- Dieu chinh cac tham so PID de robot chuyen dong on dinh hon.
- Ghi nhan cac loi thuc te va de xuat huong cai tien.

## 7. Phuong phap nghien cuu

- **Phuong phap nghien cuu ly thuyet:** Tong hop tai lieu ve robot hai banh, encoder, PWM, PID va lap quy dao.
- **Phuong phap thiet ke he thong:** Phan tach he thong thanh cac khoi chuc nang doc lenh, xu ly lenh, dieu khien dong co va phan hoi encoder.
- **Phuong phap thuc nghiem:** Lap trinh, nap code len board ESP32-C3, thu nghiem tren mo hinh that va dieu chinh tham so.
- **Phuong phap danh gia:** So sanh lenh dat voi phan hoi encoder, quan sat kha nang bam quy dao va do on dinh khi robot thuc hien chuoi lenh.

## 8. Ket qua va san pham du kien

### 8.1. San pham dang I

- 01 bao cao tong ket de tai nghien cuu khoa hoc sinh vien.
- 01 file thuyet minh/bai bao cao tom tat ket qua nghien cuu.

### 8.2. San pham dang II

- 01 mo hinh robot hai banh su dung ESP32-C3, driver dong co, encoder va cum nut dieu khien.
- Ma nguon phan mem dieu khien robot duoc to chuc theo cac module trong project PlatformIO.
- Tai lieu huong dan cau truc phan mem va cach build/upload chuong trinh.

### 8.3. San pham dang III

- Quy trinh thiet ke va lap trinh robot hai banh dieu khien theo chuoi lenh.
- Giai phap co ban ve lap quy dao va PID cho mo hinh robot hai banh sinh vien.

## 9. Y nghia khoa hoc va thuc tien

**Y nghia khoa hoc:**

De tai giup sinh vien nam vung moi quan he giua mo hinh dong hoc robot hai banh, tin hieu encoder, lap quy dao va thuat toan PID. He thong duoc xay dung theo dang module, tao co so de tiep tuc nghien cuu cac bai toan nang cao nhu dieu khien toc do, dieu khien vi tri chinh xac, dieu khien quy dao phuc tap hoac robot tu hanh.

**Y nghia thuc tien:**

Mo hinh co the su dung trong hoc tap, thuc hanh vi dieu khien, robot co ban va dieu khien tu dong. Project cung co the lam nen tang de phat trien cac ung dung nhu xe robot giao duc, robot di chuyen theo kich ban, robot tu hanh don gian trong phong thi nghiem.

## 10. Tien do thuc hien du kien

| Thoi gian | Noi dung thuc hien | Ket qua du kien |
| --- | --- | --- |
| 04/2026 | Nghien cuu tong quan, xac dinh muc tieu va giai phap ky thuat | De cuong va kien truc tong the |
| 05/2026 | Thiet ke phan cung, lua chon linh kien, xac dinh so do ket noi | Danh sach linh kien va so do ket noi |
| 06/2026 | Xay dung module doc phim analog, encoder va PWM | Cac module phan cung hoat dong rieng le |
| 07/2026 | Xay dung thuat toan ghi lenh, toi uu lenh va FSM dieu khien | Robot nhan va xu ly chuoi lenh |
| 08/2026 | Xay dung lap quy dao va PID cho hai dong co | Robot bam setpoint co phan hoi encoder |
| 09/2026 | Tich hop toan bo he thong va thu nghiem cac kich ban chuyen dong | Mo hinh robot hoat dong theo chuoi lenh |
| 10/2026 | Hieu chinh tham so, danh gia sai so, hoan thien bao cao | Ket qua thu nghiem va ban thao bao cao |
| 11/2026 | Hoan thien san pham, bao cao tong ket va nghiem thu | San pham va ho so nghiem thu |

## 11. Du toan kinh phi

| Noi dung chi | Thanh tien du kien |
| --- | ---: |
| Nghien cuu ly thuyet, thiet ke giai phap, tai lieu | 3.000.000 VND |
| Che tao, lap rap, thu nghiem va hieu chinh mo hinh | 2.000.000 VND |
| Hoi thao khoa hoc, in an va trinh bay ket qua | 900.000 VND |
| Nghiem thu, danh gia va hoan thien ho so | 1.100.000 VND |
| **Tong cong** | **7.000.000 VND** |

## 12. Huong phat trien

- Bo sung dieu khien chieu quay day du cho driver dong co.
- Cai thien bo dieu khien PID va bo loc tin hieu encoder.
- Bo sung dieu kien ket thuc tung lenh va chuyen lenh tu dong trong trang thai `PLAYING`.
- Mo rong giao tiep Bluetooth/Wi-Fi de nhap lenh tu dien thoai hoac may tinh.
- Bo sung cam bien tranh vat can de robot co kha nang tu hanh co ban.
- Luu chuoi lenh vao bo nho flash de robot co the chay lai sau khi khoi dong.

## 13. Tai lieu tham khao du kien

1. Arduino Documentation, ESP32 Arduino Core va PlatformIO Documentation.
2. Tai lieu ky thuat ESP32-C3 cua Espressif Systems.
3. Tai lieu ve driver dong co DC va dieu khien PWM.
4. Tai lieu co so ve robot hai banh vi sai va dieu khien PID.
5. Cac bai bao, giao trinh va tai lieu hoc tap ve he thong nhung, dieu khien tu dong va robot di dong.

