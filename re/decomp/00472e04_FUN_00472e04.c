// FUN_00472e04 @ 00472e04 size=69 sig=undefined FUN_00472e04() cc=unknown
// callers: FUN_0046927c,@MainWndProc$qqspvuiuil,FUN_0044a3b0
// callees: FUN_00457b3c,FUN_00477f9c,GetActiveWindow,FUN_004a5b30,FUN_00494d38,FUN_004879b0

void FUN_00472e04(void)

{
  HWND pHVar1;
  int iVar2;
  
  FUN_004879b0();
  if (DAT_0065347c == 0) {
    DAT_0065347c = 1;
    pHVar1 = GetActiveWindow();
    if (pHVar1 == DAT_0058f1a4) {
      FUN_00494d38();
      FUN_004a5b30();
    }
    do {
      iVar2 = FUN_00477f9c();
    } while (iVar2 != 0);
    FUN_00457b3c();
    DAT_0065347c = 0;
  }
  return;
}

