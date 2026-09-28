// FUN_0043b8b0 @ 0043b8b0 size=429 sig=undefined FUN_0043b8b0() cc=unknown
// callers: 
// callees: FUN_00493108,FUN_0049f09b,FUN_00491efa,sprintf,FUN_0049eb9f,FUN_004a43da,FUN_0049fe03,FUN_00495c51,FUN_0049a8ed,FUN_0049aa64,FUN_00491e02,FUN_0049a93f,FUN_00414b64,FUN_0046d250

undefined4 FUN_0043b8b0(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_2c [4];
  int local_28;
  int local_20;
  undefined1 local_1c [8];
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  if ((param_2 == 3) &&
     (((char)(&DAT_005a43f0)[DAT_004c5b50 * 0xadc] == DAT_0058f1f4 || (DAT_004c48a4 != 0)))) {
    FUN_0049f09b(param_1,local_2c);
    FUN_0049a8ed();
    iVar1 = FUN_0049aa64(local_2c);
    if (iVar1 != 0) {
      FUN_0049fe03(param_1,local_2c);
      FUN_00414b64();
      iVar1 = FUN_0049eb9f(param_1,0);
      if (iVar1 != 0) {
        FUN_00491e02(0x30);
        FUN_00491efa(0);
        FUN_0046d250(*(undefined4 *)
                      (&DAT_00533234 +
                      *(int *)(s_RRGCONE_004c1c33 + *(int *)(param_1 + 0x30) * 0x10 + 5) * 4),
                     local_c);
        sprintf(local_1c,&DAT_004c48c8,local_c);
        local_28 = local_20 + DAT_0065ec0c * -2 + -5;
        local_20 = local_20 - (DAT_0065ec0c + -5);
        FUN_00493108(local_1c,local_2c,1,0);
        FUN_0046d250(*(undefined4 *)
                      (&DAT_00533260 +
                      *(int *)(s_RRGCONE_004c1c33 + *(int *)(param_1 + 0x30) * 0x10 + 5) * 4),
                     local_14);
        if (*(int *)(&DAT_00533260 +
                    *(int *)(s_RRGCONE_004c1c33 + *(int *)(param_1 + 0x30) * 0x10 + 5) * 4) < 0) {
          sprintf(local_1c,&DAT_004c48c8,local_14);
          uVar2 = 0x60;
        }
        else {
          sprintf(local_1c,&DAT_004c48cb,local_14);
          uVar2 = 0x50;
        }
        FUN_00491e02(uVar2);
        FUN_00495c51(local_2c,0,DAT_0065ec0c);
        FUN_00493108(local_1c,local_2c,1,0);
      }
    }
    FUN_0049a93f();
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar2;
}

