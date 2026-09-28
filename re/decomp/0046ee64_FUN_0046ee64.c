// FUN_0046ee64 @ 0046ee64 size=34 sig=undefined FUN_0046ee64() cc=unknown
// callers: FUN_0046ce10
// callees: DestroyWindow,FUN_004a4113

void FUN_0046ee64(void)

{
  if (DAT_004d5974 != (HWND)0x0) {
    FUN_004a4113();
    DestroyWindow(DAT_004d5974);
    DAT_004d5974 = (HWND)0x0;
  }
  return;
}

