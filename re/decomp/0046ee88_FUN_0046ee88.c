// FUN_0046ee88 @ 0046ee88 size=24 sig=undefined FUN_0046ee88() cc=unknown
// callers: FUN_004618e8,WinMain
// callees: DestroyWindow

void FUN_0046ee88(void)

{
  if (DAT_0058f1dc != (HWND)0x0) {
    DestroyWindow(DAT_0058f1dc);
    DAT_0058f1dc = (HWND)0x0;
  }
  return;
}

