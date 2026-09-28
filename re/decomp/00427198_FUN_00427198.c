// FUN_00427198 @ 00427198 size=211 sig=undefined FUN_00427198() cc=unknown
// callers: 
// callees: FUN_00493108,FUN_0049ea99,FUN_0049a93f,FUN_004a43da,FUN_0049f22b,FUN_0049eb9f,FUN_0049a8ed,FUN_0049aa64,FUN_00491e02,FUN_00491efa,FUN_00482320

undefined4 FUN_00427198(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14 [16];
  
  if (param_2 == 3) {
    FUN_0049a8ed();
    puVar3 = local_14;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049f22b(uVar1,puVar3);
    FUN_0049aa64(local_14);
    FUN_004a43da(param_1,3,param_3,param_4);
    FUN_00482320();
    if (DAT_004b7d58 != 0) {
      iVar2 = FUN_0049eb9f(param_1,0);
      if (iVar2 != 0) {
        FUN_00491e02(0x30);
        FUN_00491efa(0xff);
        local_24 = 0x143;
        local_20 = 0x13b;
        local_1c = 0x261;
        local_18 = 0x167;
        FUN_0049a8ed();
        FUN_0049aa64(&local_24);
        FUN_00493108(DAT_004b7d58,&local_24,9,0);
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

