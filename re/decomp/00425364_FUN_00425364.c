// FUN_00425364 @ 00425364 size=114 sig=undefined FUN_00425364() cc=unknown
// callers: FUN_004505d0,FUN_00450528,FUN_00473300,FUN_00429464,NetBreakPact
// callees: FUN_00424f14,FUN_00424a84,FUN_004152ec,FUN_00424eb4,FUN_004152e0,FUN_004251d8,FUN_0044a000,FUN_0048db5d,FUN_00424dc0,FUN_00425268

void FUN_00425364(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  FUN_004152e0();
  iVar1 = FUN_00424f14(param_1,param_2);
  if (iVar1 == 0) {
    FUN_004152ec();
  }
  else {
    iVar1 = FUN_00424a84();
    if (iVar1 == 0) {
      FUN_004251d8();
    }
    else {
      FUN_00424eb4();
      FUN_0044a000();
      DAT_004d59a4 = 1;
      FUN_0048db5d(0);
      DAT_004d59a4 = 0;
      iVar1 = FUN_00424dc0();
      if (iVar1 == 0) {
        FUN_004251d8();
      }
      else {
        do {
          iVar1 = FUN_00425268();
        } while (iVar1 == 0);
      }
    }
  }
  return;
}

