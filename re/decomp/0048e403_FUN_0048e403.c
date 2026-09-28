// FUN_0048e403 @ 0048e403 size=172 sig=undefined FUN_0048e403() cc=unknown
// callers: 
// callees: GetCursorPos,FUN_0048ba5c,FUN_0048ba66,SetCursorPos

void FUN_0048e403(int param_1,int param_2)

{
  int iVar1;
  tagPOINT local_c;
  
  GetCursorPos(&local_c);
  iVar1 = FUN_0048ba66();
  if (local_c.y + param_2 < iVar1 + -1) {
    iVar1 = local_c.y + param_2;
  }
  else {
    iVar1 = FUN_0048ba66();
    iVar1 = iVar1 + -1;
  }
  if (iVar1 < 1) {
    local_c.y = 0;
  }
  else {
    iVar1 = FUN_0048ba66();
    if (local_c.y + param_2 < iVar1 + -1) {
      local_c.y = param_2 + local_c.y;
    }
    else {
      local_c.y = FUN_0048ba66();
      local_c.y = local_c.y + -1;
    }
  }
  iVar1 = FUN_0048ba5c();
  if (local_c.x + param_1 < iVar1 + -1) {
    iVar1 = local_c.x + param_1;
  }
  else {
    iVar1 = FUN_0048ba5c();
    iVar1 = iVar1 + -1;
  }
  if (iVar1 < 1) {
    local_c.x = 0;
  }
  else {
    iVar1 = FUN_0048ba5c();
    if (local_c.x + param_1 < iVar1 + -1) {
      local_c.x = param_1 + local_c.x;
    }
    else {
      local_c.x = FUN_0048ba5c();
      local_c.x = local_c.x + -1;
    }
  }
  SetCursorPos(local_c.x,local_c.y);
  return;
}

