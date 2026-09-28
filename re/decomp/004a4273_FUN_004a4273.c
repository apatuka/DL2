// FUN_004a4273 @ 004a4273 size=93 sig=undefined FUN_004a4273() cc=unknown
// callers: InitCYGame
// callees: FUN_004a14c9,FUN_0048f774,FUN_004955b2

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004a4273(undefined4 param_1)

{
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  
  if ((DAT_0051e384 == 0) && (DAT_0051e384 = FUN_004955b2(0,0), DAT_0051e384 == 0)) {
    return 0;
  }
  _DAT_0051e38c = param_1;
  FUN_0048f774(local_1c,0x18,0);
  local_18 = 1;
  local_14 = 7;
  FUN_004a14c9(local_1c);
  return 1;
}

