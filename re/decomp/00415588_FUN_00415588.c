// FUN_00415588 @ 00415588 size=39 sig=undefined FUN_00415588() cc=unknown
// callers: FUN_0045b8a8
// callees: FUN_00415484,FUN_00415514,FUN_004154e8,FUN_004152f8

void FUN_00415588(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_00415484(param_1);
  if (iVar1 != 0) {
    FUN_004152f8();
    do {
      iVar1 = FUN_00415514();
    } while (iVar1 == 0);
    FUN_004154e8();
  }
  return;
}

