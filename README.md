# Khai Motor

Project dieu khien robot 2 banh dung ESP32-C3, Arduino framework va PlatformIO. He thong nhan lenh tu cum nut analog, luu chuoi lenh, toi uu chuoi lenh, tao quy dao chuyen dong cho tung banh, sau do dung PID de tinh PWM dieu khien dong co.

## 1. Muc tieu project

Project nay duoc tach thanh cac khoi chinh:

- Doc nut nhan va ghi lai lenh di chuyen cua robot.
- Toi uu chuoi lenh lien tiep giong nhau thanh mot lenh co `count`.
- Lap quy dao cho banh trai va banh phai dua tren lenh `TOP`, `BACK`, `LEFT`, `RIGHT`.
- Tao setpoint vi tri theo tung chu ky de PID bam theo.
- Doc encoder de lay vi tri hien tai cua dong co.
- Tinh PID va xuat PWM ra driver dong co.

## 2. Cau truc thu muc

```text
Khai_motor/
├── include/
│   ├── PinConfig.h       # Khai bao chan ESP32-C3
│   ├── RobotConfig.h     # Thong so robot va enum control
│   ├── Kinematics.h      # Cong thuc quy doi quang duong/xung
│   └── read_command.h    # Khai bao ham doc lenh
├── lib/
│   ├── control/
│   │   ├── pid.cpp/.h          # PID dieu khien dong co
│   │   └── trajectory.cpp/.h   # Lap quy dao va setpoint
│   ├── matrix/
│   │   └── matrix.cpp/.h       # Doc phim analog
│   └── motor/
│       └── motor.cpp/.h        # Encoder va PWM dong co
├── src/
│   ├── main.cpp          # Khoi tao he thong, timer, loop chinh
│   └── read_command.cpp  # FSM ghi lenh va chay lenh
└── platformio.ini        # Cau hinh PlatformIO
```

## 3. Workflow tong the

```text
Nguoi dung bam nut
        |
        v
matrix::read_analog_matrix()
        |
        v
read_command()
        |
        v
Luu lenh vao route[]
        |
        v
optimal()
        |
        v
press_cmd[] = lenh + so lan lap
        |
        v
traject::caculate_traject()
        |
        v
leftTire.pos_tar / rightTire.pos_tar
        |
        v
traject::update()
        |
        v
leftTire.pos_setpoint / rightTire.pos_setpoint
        |
        v
pid::resolve_pid()
        |
        v
go(speedA, speedB)
        |
        v
PWM ra dong co
```

## 4. Luong khoi dong trong `main.cpp`

File `src/main.cpp` lam cac viec sau:

1. Khoi dong Serial de debug.
2. Tao timer interrupt moi 10 ms.
3. Trong timer interrupt, goi:

```cpp
myPidController.resolve_pid();
```

4. Cau hinh chan dieu khien driver dong co.
5. Cau hinh PWM bang `ledcSetup()` va `ledcAttachPin()`.
6. Trong `loop()`, lien tuc goi:

```cpp
read_command();
```

Nhu vay, project co 2 luong chay song song:

- `loop()` xu ly nut nhan va chuoi lenh.
- Timer interrupt goi PID theo chu ky 10 ms.

## 5. Workflow doc va ghi lenh

File `src/read_command.cpp` quan ly trang thai bang FSM:

```cpp
IDLE -> RECORD -> HANDLE -> PLAYING
```

Y nghia cac state:

- `IDLE`: Cho nguoi dung bat dau ghi lenh.
- `RECORD`: Doc nut va luu lenh vao mang `route[]`.
- `HANDLE`: Goi `optimal()` de toi uu chuoi lenh.
- `PLAYING`: Nap lenh da toi uu vao bo lap quy dao.
- `ERR`: Bao loi khi vuot qua so lenh toi da.

Mang lenh ban dau:

```cpp
control route[M];
```

Sau khi toi uu, lenh duoc luu vao:

```cpp
cmd press_cmd[M];
```

Moi phan tu gom:

```cpp
control cmd_press;
int count;
```

Vi du: neu nguoi dung bam `TOP`, `TOP`, `TOP`, `LEFT`, ham `optimal()` se bien thanh:

```text
TOP  x 3
LEFT x 1
```

## 6. Workflow lap quy dao

File `lib/control/trajectory.cpp` quan ly du lieu cua 2 banh:

```cpp
volatile MotorState leftTire;
volatile MotorState rightTire;
```

Moi banh co cac gia tri quan trong:

- `pos_curr`: Vi tri hien tai doc tu encoder.
- `pos_tar`: Vi tri dich cuoi cung.
- `pos_setpoint`: Vi tri ao thay doi theo tung chu ky, dua cho PID bam theo.
- `vel_setpoint`: Van toc ao cua quy dao.
- `pwm_output`: Xung PWM tinh duoc.

Khi nhan lenh, ham nay cap nhat dich den:

```cpp
traject::caculate_traject(control command, int count)
```

Y nghia:

- `TOP`: ca 2 banh tien.
- `BACK`: ca 2 banh lui.
- `LEFT`: banh trai lui, banh phai tien.
- `RIGHT`: banh trai tien, banh phai lui.

Sau do ham:

```cpp
traject::update()
```

goi:

```cpp
update_single_motor(leftTire);
update_single_motor(rightTire);
```

`update_single_motor()` tinh quy dao dang hinh thang/giam toc dua tren:

- Khoang cach con lai: `pos_tar - pos_setpoint`
- Van toc gioi han: `_v_max`
- Gia toc gioi han: `_a_max`
- Thoi gian mau: `_dt`

Ket qua quan trong nhat cua khoi trajectory la:

```cpp
leftTire.pos_setpoint
rightTire.pos_setpoint
```

Day la du lieu dua sang PID.

## 7. Workflow PID

File `lib/control/pid.cpp` tinh sai so giua setpoint va encoder:

```cpp
float error_a = leftTire.pos_setpoint - curr_encoder_A;
float error_b = rightTire.pos_setpoint - curr_encoder_B;
```

Sau do tinh 3 thanh phan:

```cpp
P = Kp * error
I = Ki * tong_error
D = Kd * dao_ham_error
```

Ket qua PID duoc gioi han trong khoang PWM:

```cpp
long speedA = constrain((long)Oa, -1023, 1023);
long speedB = constrain((long)Ob, -1023, 1023);
```

Cuoi cung goi:

```cpp
go(speedA, speedB);
```

## 8. Workflow encoder va motor

File `lib/motor/motor.cpp` co 2 nhiem vu:

1. Doc encoder:

```cpp
read_encoder_A();
read_encoder_B();
```

Encoder cap nhat:

```cpp
encoder_1_val
encoder_2_val
```

2. Xuat PWM:

```cpp
go(int speedA, int speedB);
```

Ham `go()` hien tai ghi PWM ra 2 kenh:

```cpp
ledcWrite(MOTOR::channela, ...);
ledcWrite(MOTOR::channelb, ...);
```

## 9. Cac file cau hinh

### `PinConfig.h`

Khai bao chan:

- Encoder A/B cho 2 banh.
- Chan analog doc nut.
- Chan PWM va chan dieu khien driver dong co.

### `RobotConfig.h`

Khai bao:

- Enum `control`: `TOP`, `BACK`, `LEFT`, `RIGHT`, `OK`, ...
- Thong so robot: dien ap, RPM, encoder, duong kinh banh xe, quang duong moi lenh, khoang xoay.

### `Kinematics.h`

Chua cong thuc quy doi:

- Quang duong tien sang so xung encoder.
- Cung quay 90 do sang so xung encoder.

## 10. Workflow de xuat: tach `MotionManager`

Workflow nen huong toi la tach them mot lop trung gian `MotionManager`. Lop nay nam giua `read_command` va `trajectory`, co nhiem vu quan ly viec chay tung lenh trong danh sach da toi uu.

Muc tieu cua workflow nay:

- `read_command` chi phu trach doc nut, ghi lenh va tao danh sach lenh da toi uu.
- `MotionManager` phu trach chay tung lenh mot, kiem tra khi nao xong lenh hien tai, sau do chuyen sang lenh tiep theo.
- `trajectory` chi phu trach tao `pos_setpoint` cho banh trai va banh phai.
- `pid` chi phu trach bam theo `pos_setpoint` va tinh PWM.
- `motor` chi phu trach encoder va xuat PWM.

### 10.1. So do workflow moi

```text
Nguoi dung bam nut
        |
        v
matrix::read_analog_matrix()
        |
        v
read_command()
        |
        v
route[] = chuoi lenh goc
        |
        v
optimal()
        |
        v
press_cmd[] = chuoi lenh da toi uu
        |
        v
MotionManager::loadCommands()
        |
        v
MotionManager::update()
        |
        +-- Neu chua co lenh dang chay:
        |       lay press_cmd[current_index]
        |       goi trajectory.caculate_traject()
        |       danh dau dang chay
        |
        +-- Neu dang chay:
        |       goi trajectory.update()
        |       kiem tra da toi dich chua
        |
        +-- Neu da xong lenh:
                current_index++
                chuyen sang lenh tiep theo
        |
        v
leftTire.pos_setpoint / rightTire.pos_setpoint
        |
        v
pid::resolve_pid()
        |
        v
go(speedA, speedB)
```

### 10.2. Trach nhiem tung khoi

#### `read_command`

Khoi nay nen chi lam cac viec:

- Doc nut tu `matrix`.
- Quan ly state `IDLE`, `RECORD`, `HANDLE`, `PLAYING`, `ERR`.
- Luu lenh vao `route[]`.
- Goi `optimal()` de tao `press_cmd[]`.
- Khi bat dau `PLAYING`, dua danh sach `press_cmd[]` cho `MotionManager`.

`read_command` khong nen truc tiep lap vong `for` de nap tat ca lenh vao `trajectory`, vi nhu vay robot se bi cong don tat ca muc tieu cung luc.

#### `MotionManager`

Day la khoi nen them moi. Khoi nay quan ly tien trinh chay lenh.

Bien trang thai nen co:

```cpp
int current_index;
int total_commands;
bool is_running_command;
bool is_finished;
```

Nhung ham nen co:

```cpp
void loadCommands(cmd* commands, int total);
void start();
void stop();
void update();
bool done();
```

Y tuong cua `update()`:

```text
Neu da chay het lenh:
    dung robot
    bao done

Neu chua co lenh nao dang chay:
    lay lenh hien tai
    nap vao trajectory.caculate_traject()
    danh dau is_running_command = true

Neu dang co lenh chay:
    goi trajectory.update()
    kiem tra leftTire/rightTire da gan pos_tar chua

Neu lenh hien tai da xong:
    is_running_command = false
    current_index++
```

#### `trajectory`

Khoi nay nen chi giu nhiem vu lap quy dao:

- Nhan lenh dich qua `caculate_traject()`.
- Cap nhat `leftTire.pos_tar` va `rightTire.pos_tar`.
- Moi lan goi `update()`, cap nhat:

```cpp
leftTire.pos_setpoint
rightTire.pos_setpoint
```

`trajectory` khong can biet danh sach lenh dai bao nhieu. No chi can biet dich hien tai cua tung banh.

#### `pid`

Khoi PID nen chi doc:

```cpp
leftTire.pos_setpoint
rightTire.pos_setpoint
encoder_1_val
encoder_2_val
```

Sau do tinh:

```cpp
error_a = leftTire.pos_setpoint - encoder_1_val;
error_b = rightTire.pos_setpoint - encoder_2_val;
```

PID khong nen doc nut, khong nen quan ly state, khong nen biet robot dang o lenh thu may. PID chi can bam setpoint.

#### `motor`

Khoi motor chi nen phu trach:

- Khoi tao encoder.
- Doc encoder bang interrupt.
- Xuat PWM va chieu quay cho dong co.

### 10.3. Workflow trong `loop()`

Sau khi tach `MotionManager`, `loop()` nen co dang:

```cpp
void loop()
{
    read_command();
    motionManager.update();
}
```

`read_command()` xu ly nguoi dung va state. `motionManager.update()` xu ly tien trinh chay lenh. Hai khoi nay khong nen lam thay viec cua nhau.

### 10.4. Workflow trong timer interrupt

Timer interrupt nen giu gon:

```cpp
void IRAM_ATTR on_timer()
{
    myPidController.resolve_pid();
}
```

Ly do:

- PID can chay deu theo chu ky 10 ms.
- Khong nen dua qua nhieu logic FSM vao interrupt.
- Khong nen in `Serial` trong interrupt.
- Khong nen xu ly danh sach lenh trong interrupt.

Neu sau nay can dieu khien chinh xac hon, co the can nhac goi `trajectory.update()` theo chu ky co dinh. Tuy nhien trong giai do hien tai, nen de `MotionManager` goi `trajectory.update()` trong `loop()` de de debug hon.

### 10.5. Cach kiem tra mot lenh da xong

Mot lenh co the xem la xong khi ca 2 banh da gan toi dich:

```text
abs(leftTire.pos_tar - leftTire.pos_setpoint) < nguong
abs(rightTire.pos_tar - rightTire.pos_setpoint) < nguong
```

Dong thoi van toc setpoint gan bang 0:

```text
abs(leftTire.vel_setpoint) < nguong_van_toc
abs(rightTire.vel_setpoint) < nguong_van_toc
```

Neu muon chac hon, co the kiem tra encoder thuc te:

```text
abs(leftTire.pos_tar - encoder_1_val) < nguong_encoder
abs(rightTire.pos_tar - encoder_2_val) < nguong_encoder
```

Nen phan biet 2 loai "xong":

- `trajectory done`: setpoint da toi dich.
- `motor done`: encoder thuc te da toi dich.

Voi robot that, nen uu tien `motor done`, vi setpoint toi dich chua chac banh xe da toi dich.

### 10.6. Danh gia workflow nay

Uu diem:

- Tach trach nhiem ro rang hon.
- De debug tung khoi rieng.
- De them tinh nang `pause`, `resume`, `stop`, `emergency stop`.
- Tranh viec `read_command` nap tat ca lenh vao trajectory cung luc.
- PID sach hon vi chi lam dung nhiem vu dieu khien.

Nhuoc diem:

- Can them file/class moi.
- Can quan ly them bien `current_index`, `is_running_command`, `is_finished`.
- Can dinh nghia ro dieu kien ket thuc tung lenh.

Day la workflow phu hop neu project se tiep tuc phat trien dai hon, vi no giup code bot roi va moi module co mot nhiem vu ro rang.

## 11. Cac diem can hoan thien

Project hien tai da co khung workflow chinh, nhung van con mot so diem nen hoan thien:

- Can dam bao `traject::update()` duoc goi dinh ky truoc khi PID doc `pos_setpoint`.
- Nen dung mot object `traject` chung cho ca `read_command.cpp` va `pid.cpp`, tranh tao nhieu object khac nhau.
- Can goi `init_encoder()` trong `setup()` neu muon encoder interrupt hoat dong.
- Ham `go()` hien tai moi ghi PWM, can kiem tra them chan chieu quay `ina_1`, `ina_2`, `inb_1`, `inb_2`.
- Nen bao ve du lieu `leftTire/rightTire` khi vua doc/ghi trong interrupt vua doc/ghi trong loop.
- Can bo sung `MotionManager` de quan ly tung lenh trong state `PLAYING`.
- Can bo sung dieu kien ket thuc lenh de robot biet khi nao chay xong lenh hien tai va chuyen sang lenh tiep theo.

## 12. Lenh build

Build project:

```bash
pio run
```

Upload vao board:

```bash
pio run -t upload
```

Mo Serial Monitor:

```bash
pio device monitor
```
