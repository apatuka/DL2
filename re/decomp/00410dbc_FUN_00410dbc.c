// FUN_00410dbc @ 00410dbc size=86 sig=undefined FUN_00410dbc() cc=unknown
// callers: FUN_00410e38,FUN_00410e14
// callees: FUN_00410d70,FUN_00410c74

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00410dbc(uint param_1,int param_2)

{
  int iVar1;
  
  _DAT_005331dc = _DAT_005331dc + param_2;
  while (iVar1 = param_2 + -1, param_2 != 0) {
    param_2 = iVar1;
    if (DAT_005331c0 == 0) {
      FUN_00410d70(1 << ((byte)iVar1 & 0x1f) & param_1);
    }
    else {
      FUN_00410c74(DAT_005331c0,1 << ((byte)iVar1 & 0x1f) & param_1);
    }
  }
  return;
}

