// FUN_0048bbbb @ 0048bbbb size=39 sig=undefined FUN_0048bbbb() cc=unknown
// callers: FUN_0049ae0c
// callees: 

void FUN_0048bbbb(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((param_1 != 0) && (param_2 != (undefined4 *)0x0)) {
    puVar2 = (undefined4 *)(param_1 + 0x2c);
    for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
      *param_2 = *puVar2;
      puVar2 = puVar2 + 1;
      param_2 = param_2 + 1;
    }
  }
  return;
}

