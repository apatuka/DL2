// FUN_0044a358 @ 0044a358 size=88 sig=undefined FUN_0044a358() cc=unknown
// callers: FUN_0044a3b0
// callees: FUN_0045e398,GetCursorPos

void FUN_0044a358(void)

{
  tagPOINT local_8;
  
  GetCursorPos(&local_8);
  if (local_8.x < 1) {
    FUN_0045e398(0,1);
  }
  if (DAT_0058f1c0 + -1 <= local_8.x) {
    FUN_0045e398(1,1);
  }
  if (local_8.y < 1) {
    FUN_0045e398(2,1);
  }
  if (DAT_0058f1c4 + -1 <= local_8.y) {
    FUN_0045e398(3,1);
  }
  return;
}

