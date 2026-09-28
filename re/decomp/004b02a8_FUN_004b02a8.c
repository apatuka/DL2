// FUN_004b02a8 @ 004b02a8 size=52 sig=undefined FUN_004b02a8() cc=unknown
// callers: UnitList__Insert,FUN_00412654,malloc,FUN_00424a84,FUN_0041287c,RaceInit,FUN_0046e56c,FUN_004a6ec4,FUN_004609e8,FUN_00467e58,FUN_004a6e64,FUN_0042c50c,FUN_00427eb4,FUN_0042540c,FUN_00484da8,FUN_0041e9e8,FUN_00421b24,OpenDataFiles,FUN_00460a74,FUN_0047c128,FUN_004a6fc0,FUN_004b2e50,FUN_00427e80,FUN_00430cd8,FUN_00411990
// callees: FUN_004b0b44

int FUN_004b02a8(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    param_1 = 1;
  }
  while( true ) {
    iVar1 = FUN_004b0b44(param_1);
    if ((iVar1 != 0) || (DAT_0069f674 == (code *)0x0)) break;
    (*DAT_0069f674)();
  }
  return iVar1;
}

