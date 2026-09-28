// FUN_0043b2c4 @ 0043b2c4 size=584 sig=undefined FUN_0043b2c4() cc=unknown
// callers: 
// callees: FUN_00493108,FUN_0048c434,FUN_0044980c,FUN_00496e80,FUN_00491efa,FUN_00498aab,sprintf,FUN_0049f22b,FUN_0049eb9f,FUN_004a43da,FUN_0046c3fc,FUN_0049a8ed,FUN_00490796,FUN_0049aa64,FUN_00491e02,FUN_00490ab3,FUN_0049a93f

undefined4 FUN_0043b2c4(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24 [16];
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c [4];
  undefined4 local_8;
  
  if ((param_2 == 3) && (((&DAT_005a43f0)[DAT_004c5b50 * 0xadc] != -1 || (DAT_004c48a4 != 0)))) {
    local_10 = DAT_0051bddc;
    FUN_0048c434(*(undefined4 *)(DAT_004c48a0 + 0x3c));
    if (DAT_004c48a4 == 0) {
      FUN_0046c3fc(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,&local_8,local_c);
    }
    else {
      FUN_0044980c((int)(char)*PTR_DAT_004d5988,&local_8,local_c);
    }
    FUN_0049a8ed();
    FUN_0049f22b(DAT_004c48a0,&local_34);
    FUN_0049aa64(&local_34);
    local_14 = 0x166;
    iVar1 = FUN_00490ab3(0,0x47414d49,0x3030494d,0,0);
    if (iVar1 != 0) {
      uVar2 = FUN_00498aab(iVar1,1);
      if (DAT_004c48a4 == 0) {
        FUN_00496e80(uVar2,3000,
                     (int)(char)(&DAT_0059f162)[(char)(&DAT_005a43f0)[DAT_004c5b50 * 0xadc] * 0x2d8]
                     ,0,0x183,local_14,0xffffffff);
      }
      else {
        FUN_00496e80(uVar2,3000,(int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],0,0x183,local_14,
                     0xffffffff);
      }
      FUN_00498aab(iVar1,0);
      FUN_00490796(iVar1,0);
    }
    if (((char)(&DAT_005a43f0)[DAT_004c5b50 * 0xadc] == DAT_0058f1f4) || (DAT_004c48a4 != 0)) {
      iVar1 = FUN_0049eb9f(param_1,0);
      if (iVar1 != 0) {
        FUN_00491e02(0x30);
        FUN_00491efa(0xff);
        sprintf(local_24,&DAT_004c48c3,local_8);
        local_30 = 0x17b;
        local_28 = 0x18c;
        local_34 = 0x183;
        local_2c = 0x1a6;
        FUN_00493108(local_24,&local_34,1,0);
      }
    }
    FUN_0049a93f();
    FUN_0048c434(local_10);
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar2;
}

