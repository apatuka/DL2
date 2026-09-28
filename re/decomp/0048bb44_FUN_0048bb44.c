// FUN_0048bb44 @ 0048bb44 size=40 sig=undefined FUN_0048bb44() cc=unknown
// callers: FUN_00489c98
// callees: CoInitialize

undefined4 FUN_0048bb44(void)

{
  HRESULT HVar1;
  
  if (DAT_0051bdd4 == 0) {
    HVar1 = CoInitialize((LPVOID)0x0);
    if (HVar1 < 0) {
      return 0;
    }
  }
  DAT_0051bdd4 = DAT_0051bdd4 + 1;
  return 1;
}

