// FUN_0044a328 @ 0044a328 size=47 sig=undefined FUN_0044a328() cc=unknown
// callers: FUN_0044a3b0
// callees: GetCursorPos,FUN_0043cfb0

void FUN_0044a328(void)

{
  tagPOINT local_8;
  
  GetCursorPos(&local_8);
  if (local_8.x < 1) {
    FUN_0043cfb0(0,1);
  }
  if (DAT_0058f1c0 + -1 <= local_8.x) {
    FUN_0043cfb0(1,1);
  }
  return;
}

