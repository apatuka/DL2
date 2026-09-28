// FUN_0042d3dc @ 0042d3dc size=157 sig=undefined FUN_0042d3dc() cc=unknown
// callers: FUN_00476b8c
// callees: FUN_0048db5d,FUN_0042c50c,FUN_0042c73c,FUN_0044a000,FUN_0042d304,FUN_0042d0ac,FUN_0042d27c,FUN_00477f9c,FUN_0042d04c

undefined4 FUN_0042d3dc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0042d0ac(param_1,param_2);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = FUN_0042c50c();
    if (iVar1 == 0) {
      FUN_0042d27c();
      uVar2 = 0;
    }
    else {
      FUN_0042d04c();
      FUN_0044a000();
      DAT_004d59a4 = 1;
      FUN_0048db5d(0);
      DAT_004d59a4 = 0;
      iVar1 = FUN_0042c73c();
      if (iVar1 == 0) {
        FUN_0042d27c();
        uVar2 = 0;
      }
      else {
        iVar1 = 0;
        while ((iVar1 == 0 && (*(int *)(&DAT_006534fc + DAT_0058f1f4 * 4) == 2))) {
          FUN_00477f9c();
          iVar1 = FUN_0042d304();
        }
        FUN_0042d27c();
        if (iVar1 == 0x25) {
          uVar2 = 1;
        }
        else {
          uVar2 = 0;
        }
      }
    }
  }
  return uVar2;
}

