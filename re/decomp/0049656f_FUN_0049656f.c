// FUN_0049656f @ 0049656f size=48 sig=undefined FUN_0049656f() cc=unknown
// callers: FUN_00496748
// callees: 

void FUN_0049656f(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar1 = param_1 + 0x18;
    iVar2 = *(int *)(param_1 + 0x14);
    while (iVar2 != 0) {
      *(undefined4 *)(*(int *)(iVar1 + 4) + param_1 + 8) = 0;
      iVar1 = iVar1 + 8;
      iVar2 = iVar2 + -1;
    }
  }
  return;
}

