// FUN_0041e4d0 @ 0041e4d0 size=401 sig=undefined FUN_0041e4d0() cc=unknown
// callers: 
// callees: sprintf,FUN_0049ea99,FUN_0049aa64,FUN_0049a8ed,FUN_0049f22b,FUN_004935fc,FUN_00491efa,FUN_004ae068,FUN_0049a93f,FUN_004a43da,FUN_0049eb9f,FUN_00493108,FUN_00491e02

undefined4 FUN_0041e4d0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined1 local_10 [12];
  
  if (param_2 == 3) {
    FUN_0049a8ed();
    piVar3 = &local_20;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049f22b(uVar1,piVar3);
    FUN_0049aa64(&local_20);
    FUN_004a43da(param_1,3,param_3,param_4);
    if (DAT_0053b880 != 0) {
      local_20 = 0x156;
      local_1c = 0x146;
      local_14 = 0x157;
      if (DAT_0053b880 == 100) {
        local_18 = 0x24f;
      }
      else {
        local_18 = FUN_004ae068();
        local_18 = local_18 + local_20;
      }
      FUN_004935fc(local_20,local_1c,local_18,local_14,0x37);
    }
    iVar2 = FUN_0049eb9f(param_1,0);
    if (iVar2 != 0) {
      FUN_00491e02(0x30);
      FUN_00491efa(0xff);
      local_30 = 0x156;
      local_2c = 0x146;
      local_28 = 0x24f;
      local_24 = 0x156;
      FUN_0049a8ed();
      FUN_0049aa64(&local_30);
      sprintf(local_10,&DAT_004b7944,DAT_0053b880);
      FUN_00493108(local_10,&local_30,9,0);
      FUN_0049a93f();
      if (DAT_004b7940 != 0) {
        local_30 = 0x149;
        local_2c = 0x115;
        local_28 = 0x25a;
        local_24 = 0x143;
        FUN_0049a8ed();
        FUN_0049aa64(&local_30);
        FUN_00493108(DAT_004b7940,&local_30,9,0);
        FUN_0049a93f();
      }
    }
    FUN_0049a93f();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

