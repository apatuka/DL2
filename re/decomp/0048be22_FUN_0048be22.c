// FUN_0048be22 @ 0048be22 size=121 sig=undefined FUN_0048be22() cc=unknown
// callers: FUN_0048c85e
// callees: RealizePalette,ReleaseDC,SelectPalette,GetDC,FUN_0048bdb0

void FUN_0048be22(int param_1,undefined4 param_2,undefined4 param_3)

{
  HDC hdc;
  HPALETTE unaff_ESI;
  
  if (DAT_0051b834 != (HWND)0x0) {
    hdc = GetDC(DAT_0051b834);
    if (hdc != (HDC)0x0) {
      if (DAT_0051b838 != (HPALETTE)0x0) {
        unaff_ESI = SelectPalette(hdc,DAT_0051b838,0);
        RealizePalette(hdc);
      }
      FUN_0048bdb0(*(undefined4 *)(param_1 + 0x40),hdc,param_2,param_3,0xcc0020);
      if (DAT_0051b838 != (HPALETTE)0x0) {
        SelectPalette(hdc,unaff_ESI,0);
      }
      ReleaseDC(DAT_0051b834,hdc);
    }
  }
  return;
}

