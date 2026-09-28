// FUN_00472d74 @ 00472d74 size=45 sig=undefined FUN_00472d74() cc=unknown
// callers: @MainWndProc$qqspvuiuil
// callees: KillTimer

void FUN_00472d74(HWND param_1)

{
  DAT_0058f1ec = 1;
  DAT_0058f1f0 = 1;
  DAT_0058f1a4 = 0;
  KillTimer(param_1,1);
  return;
}

