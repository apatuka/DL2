// FUN_0048e138 @ 0048e138 size=49 sig=undefined FUN_0048e138() cc=unknown
// callers: FUN_0048e241,FUN_0048e169,FUN_0048e319,FUN_0048e1d5,FUN_0048e2ad,FUN_0048e3f1,FUN_0048e385
// callees: GetCursorPos

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048e138(int *param_1,int *param_2)

{
  tagPOINT local_c;
  
  GetCursorPos(&local_c);
  *param_2 = local_c.y - _DAT_0065e65c;
  *param_1 = local_c.x - _DAT_0065e658;
  return;
}

