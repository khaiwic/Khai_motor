luong thong tin se di tu press_cmd[] vao trong trajectory 
trajectory nhan duoc tin hieu tu press_cmd se khoi tao nhung gia tri can chuan bi de tinh toan 
trajecory se goi encoder de tra ve gia tri van toc va vi tri hien tai (velocity and position current) de tinh toan ra cac gia tri gia toc va toc do can thiet sau do truyen thang vao pid roi tu pid lai truyen xung ve dong co( vong lap trong mot chu ki lenh)
khi vua khoi tao 2  ngat ngoai cho encoder va 1 timer interrput cho PID thi lieu co su xung dot va lam sai lenh thoi gian khi tinh toan khong ( toi lay chu ki = 10ms cho timer)
khoi tao mot tydef motorstate {
    tao ra mot bien long de lay gia tri pid 
    tao ra mot bien long de lay gia tri encoder 1 va mot bien lay gia tri encoder 2
    
}