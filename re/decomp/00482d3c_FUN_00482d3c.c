// FUN_00482d3c @ 00482d3c size=172 sig=undefined FUN_00482d3c() cc=unknown
// callers: FUN_0041d188,FUN_00482a8c,FUN_00487a00
// callees: FUN_00495fc5,FUN_00482ba0,FUN_0048a333,FUN_0048a53c,FUN_00482b04

void FUN_00482d3c(void)

{
  int iVar1;
  
  if (DAT_00657e20 != 0) {
    FUN_00482b04();
    if (DAT_00657e38 != -1) {
      DAT_00657e34 = FUN_00482ba0(DAT_00657e38,1,0,1,0,1,1);
      if (DAT_00657e34 == 0) {
        DAT_00657e30 = 0xffffffff;
        return;
      }
      DAT_00657e30 = DAT_00657e38;
      FUN_0048a53c(DAT_00657e34,DAT_00657e3c);
      DAT_00657e38 = -1;
      iVar1 = FUN_0048a333(DAT_00657e34,1);
      if (iVar1 == 0) {
        FUN_00495fc5(DAT_00657e34);
        DAT_00657e30 = 0xffffffff;
        return;
      }
      *(uint *)(DAT_00657e34 + 0xc) = *(uint *)(DAT_00657e34 + 0xc) | 2;
    }
  }
  return;
}

