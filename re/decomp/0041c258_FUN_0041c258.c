// FUN_0041c258 @ 0041c258 size=275 sig=undefined FUN_0041c258() cc=unknown
// callers: 
// callees: FUN_0041bfc0,FUN_0041ba74,FUN_0049ea99,FUN_0049aa64,FUN_0044ba40,FUN_0044b7d8,FUN_0049a93f,FUN_0049a8ed,FUN_0049f22b,FUN_004a43da,FUN_0044c754,FUN_0041beac

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041c258(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 local_14 [16];
  
  if (param_2 == 3) {
    FUN_0049a8ed();
    puVar5 = local_14;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049f22b(uVar1,puVar5);
    FUN_0049aa64(local_14);
    FUN_004a43da(param_1,3,param_3,param_4);
    FUN_0041beac(local_14);
    FUN_0041bfc0(param_1);
    if (_DAT_0053b340 < 6) {
      iVar3 = *(int *)(DAT_0053b850 + 0x14 + _DAT_0053b340 * 4);
      iVar2 = FUN_0044ba40(DAT_0053b850);
      iVar2 = iVar2 - *(int *)(DAT_0053b850 + 0x14 + _DAT_0053b340 * 4);
    }
    else {
      iVar3 = FUN_0044c754(DAT_0053b84c);
      iVar2 = FUN_0044b7d8(DAT_0053b84c);
      iVar4 = FUN_0044c754(DAT_0053b84c);
      iVar2 = iVar2 - iVar4;
    }
    FUN_0041ba74((int)(char)(&DAT_0059f162)
                            [(char)(&DAT_005a43f0)[*(short *)(DAT_0053b850 + 8) * 0xadc] * 0x2d8],
                 iVar2 + iVar3,iVar3);
    FUN_0049a93f();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

