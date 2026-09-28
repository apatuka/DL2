// FUN_0045deb0 @ 0045deb0 size=139 sig=undefined FUN_0045deb0() cc=unknown
// callers: FUN_0045df3c
// callees: FUN_00459ee0,InvalidateRect,FUN_0043ee40

void FUN_0045deb0(undefined4 param_1,undefined4 param_2)

{
  RECT local_1c;
  int local_c;
  int local_8;
  
  if (DAT_004d5ad0 == 0) {
    FUN_00459ee0(param_1,param_2,&local_8,&local_c);
    local_1c.left = local_8;
    local_1c.top = local_c;
    local_1c.right = local_8 + 0x20;
    local_1c.bottom = local_c + 0x20;
  }
  else {
    FUN_0043ee40(param_1,param_2,&local_8,&local_c);
    local_1c.left = local_8 + -0x10;
    local_1c.top = local_c + -0x10;
    local_1c.right = local_8 + 0x10;
    local_1c.bottom = local_c;
  }
  InvalidateRect(DAT_004d5974,&local_1c,0);
  return;
}

