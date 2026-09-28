// FUN_00484f74 @ 00484f74 size=44 sig=undefined FUN_00484f74() cc=unknown
// callers: ProduceUnits
// callees: 

void FUN_00484f74(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  if (*(int *)(param_1 + 4) != 0) {
    iVar1 = 0;
    do {
      *(undefined4 *)(*(int *)(param_1 + 4) + 4 + iVar1 * 4) = *param_2;
      iVar1 = iVar1 + 1;
      param_2 = param_2 + 1;
    } while (iVar1 < 0xb);
  }
  return;
}

