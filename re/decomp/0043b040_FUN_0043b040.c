// FUN_0043b040 @ 0043b040 size=329 sig=undefined FUN_0043b040() cc=unknown
// callers: 
// callees: FUN_00493108,FUN_0049a8ed,FUN_0049f09b,FUN_004a0e79,FUN_00491e02,FUN_0049aa64,FUN_00491efa,FUN_0049a93f,sprintf,FUN_0049ea99,FUN_0049eb9f,FUN_004a43da

undefined4 FUN_0043b040(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_38 [20];
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  if (param_2 == 3) {
    uVar3 = param_1;
    uVar1 = FUN_0049ea99(param_1);
    FUN_004a0e79(uVar1,uVar3);
    FUN_0049f09b(param_1,&local_14);
    iVar2 = FUN_0049eb9f(param_1,0);
    if (iVar2 != 0) {
      FUN_00491e02(0x30);
      FUN_00491efa(0xff);
      sprintf(local_38,&DAT_004c48c0,DAT_0059f154);
      iVar2 = (int)(0x1cU - DAT_0065ec0c) >> 1;
      if (iVar2 < 0) {
        iVar2 = iVar2 + (uint)((0x1cU - DAT_0065ec0c & 1) != 0);
      }
      local_20 = iVar2 + local_10 + 5;
      local_18 = local_20 + DAT_0065ec0c;
      local_24 = local_14 + 5;
      local_1c = local_14 + 0x2d;
      FUN_0049a8ed();
      FUN_0049aa64(&local_24);
      FUN_00493108(local_38,&local_24,1,0);
      FUN_0049a93f();
      sprintf(local_38,&DAT_004c48c0,DAT_004dcf4c);
      iVar2 = (int)(0x10U - DAT_0065ec0c) >> 1;
      if (iVar2 < 0) {
        iVar2 = iVar2 + (uint)((0x10U - DAT_0065ec0c & 1) != 0);
      }
      local_20 = iVar2 + local_10 + 0xe;
      local_18 = local_20 + DAT_0065ec0c;
      local_24 = local_14 + 0x38;
      local_1c = local_14 + 0x60;
      FUN_0049a8ed();
      FUN_0049aa64(&local_24);
      FUN_00493108(local_38,&local_24,1,0);
      FUN_0049a93f();
    }
    uVar3 = 1;
  }
  else {
    uVar3 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar3;
}

