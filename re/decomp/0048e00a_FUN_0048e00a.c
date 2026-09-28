// FUN_0048e00a @ 0048e00a size=173 sig=undefined FUN_0048e00a() cc=unknown
// callers: 
// callees: GetAsyncKeyState

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048e00a(void)

{
  SHORT SVar1;
  int iVar2;
  
  _DAT_0065e7a8 = 0;
  SVar1 = GetAsyncKeyState(0x11);
  if (((int)SVar1 & 0x80000000U) != 0) {
    _DAT_0065e7a8 = _DAT_0065e7a8 | 3;
  }
  SVar1 = GetAsyncKeyState(0x10);
  if (((int)SVar1 & 0x80000000U) != 0) {
    _DAT_0065e7a8 = _DAT_0065e7a8 | 0xc;
  }
  SVar1 = GetAsyncKeyState(0x12);
  if (((int)SVar1 & 0x80000000U) != 0) {
    _DAT_0065e7a8 = _DAT_0065e7a8 | 0x30;
  }
  SVar1 = GetAsyncKeyState(0xd);
  if (((int)SVar1 & 0x80000000U) != 0) {
    _DAT_0065e7a8 = _DAT_0065e7a8 | 0x40;
  }
  if (DAT_0051c308 != (short *)0x0) {
    for (iVar2 = 0; iVar2 < *DAT_0051c308; iVar2 = iVar2 + 1) {
      SVar1 = GetAsyncKeyState(*(int *)(DAT_0051c308 + iVar2 * 4 + 1));
      if (((int)SVar1 & 0x80000000U) != 0) {
        _DAT_0065e7a8 = _DAT_0065e7a8 | *(uint *)(DAT_0051c308 + iVar2 * 4 + 3);
      }
    }
  }
  return;
}

