// FUN_00410d24 @ 00410d24 size=74 sig=undefined FUN_00410d24() cc=unknown
// callers: FUN_00410e74
// callees: FUN_00410cdc,FUN_00410c18

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00410d24(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  _DAT_005331dc = _DAT_005331dc + param_1;
  while (param_1 != 0) {
    if (DAT_005331bc == 0) {
      iVar1 = FUN_00410cdc();
      iVar2 = iVar1 + iVar2 * 2;
      param_1 = param_1 + -1;
    }
    else {
      iVar1 = FUN_00410c18(DAT_005331bc);
      iVar2 = iVar1 + iVar2 * 2;
      param_1 = param_1 + -1;
    }
  }
  return iVar2;
}

