// FUN_00495f8f @ 00495f8f size=54 sig=undefined FUN_00495f8f() cc=unknown
// callers: FUN_00495fc5
// callees: FUN_0048a316,FUN_00495fc5,FUN_004954a9,FUN_004989cf

void FUN_00495f8f(int param_1)

{
  int iVar1;
  
  if ((*(byte *)(param_1 + 0xc) & 2) != 0) {
    iVar1 = FUN_0048a316(param_1);
    if (iVar1 == 0) {
      FUN_004954a9(DAT_0051e08c,param_1);
      FUN_004989cf(param_1);
    }
    else {
      FUN_00495fc5(param_1);
    }
  }
  return;
}

