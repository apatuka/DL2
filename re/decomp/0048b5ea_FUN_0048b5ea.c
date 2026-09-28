// FUN_0048b5ea @ 0048b5ea size=57 sig=undefined FUN_0048b5ea() cc=unknown
// callers: FUN_0048b1c0,CYGame_InitDirectDraw
// callees: FUN_0048b48b,FUN_0048b3e3

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048b5ea(void)

{
  if ((DAT_0051b810 == 0) || (DAT_0051b814 == 0)) {
    FUN_0048b48b();
  }
  else {
    FUN_0048b3e3();
  }
  DAT_0065e5a8 = DAT_0065e590;
  DAT_0065e5ac = _DAT_0065e5a4;
  return;
}

