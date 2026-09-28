// FUN_00495fc5 @ 00495fc5 size=95 sig=undefined FUN_00495fc5() cc=unknown
// callers: FUN_004960fd,FUN_0049604c,FUN_00482ba0,FUN_00482d3c,FUN_00495f8f,FUN_00496093
// callees: FUN_0048a2a6,FUN_00490796,FUN_00495f8f,FUN_0048a3ef

void FUN_00495fc5(int param_1)

{
  int iVar1;
  
  if ((param_1 != 0) &&
     (((*(byte *)(param_1 + 0xc) & 4) == 0 || (param_1 != *(int *)(param_1 + 0x20))))) {
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 4;
    iVar1 = *(int *)(param_1 + 0x20);
    FUN_0048a3ef(param_1);
    if (iVar1 != param_1) {
      FUN_0048a2a6(param_1);
      *(undefined4 *)(param_1 + 0x20) = 0;
      FUN_00495f8f(param_1);
    }
    if (iVar1 != 0) {
      if ((*(byte *)(iVar1 + 0xc) & 1) == 0) {
        FUN_0048a2a6(iVar1);
        FUN_00495f8f(param_1);
      }
      else {
        FUN_00490796(iVar1,1);
      }
    }
  }
  return;
}

