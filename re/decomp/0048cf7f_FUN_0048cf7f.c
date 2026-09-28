// FUN_0048cf7f @ 0048cf7f size=191 sig=undefined FUN_0048cf7f() cc=unknown
// callers: 
// callees: FUN_0048c3f4,memset

void FUN_0048cf7f(int param_1,int param_2,int param_3)

{
  undefined4 local_88 [23];
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_20 = DAT_0065ee24;
  local_24 = DAT_0065ee20;
  local_18 = DAT_0065ee24 + param_2;
  local_1c = DAT_0065ee20 + param_3;
  local_10 = DAT_0065ee2c;
  local_14 = DAT_0065ee28;
  local_8 = param_2 + DAT_0065ee2c;
  local_c = param_3 + DAT_0065ee28;
  memset(local_88,0,100);
  local_88[0] = 100;
  local_2c = 0xff;
  local_28 = 0xff;
  FUN_0048c3f4(DAT_0051bddc);
  (**(code **)(**(int **)(DAT_0051bddc + 0x40) + 0x14))
            (*(int **)(DAT_0051bddc + 0x40),&local_24,*(undefined4 *)(param_1 + 0x40),&local_14,
             0x1010000,local_88);
  return;
}

