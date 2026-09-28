// FUN_00484e24 @ 00484e24 size=97 sig=undefined FUN_00484e24() cc=unknown
// callers: ProduceUnits
// callees: free

undefined4 FUN_00484e24(int *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if ((undefined1 *)*param_1 == (undefined1 *)0x0) {
    uVar2 = 0;
  }
  else {
    *(undefined1 *)param_2 = *(undefined1 *)*param_1;
    *(undefined2 *)((int)param_2 + 2) = *(undefined2 *)(*param_1 + 2);
    iVar3 = 0;
    do {
      param_2 = param_2 + 1;
      iVar1 = iVar3 * 4;
      iVar3 = iVar3 + 1;
      *param_2 = *(undefined4 *)(*param_1 + 4 + iVar1);
    } while (iVar3 < 0xb);
    iVar3 = *param_1;
    if (iVar3 == param_1[1]) {
      param_1[1] = *(int *)(iVar3 + 0x30);
    }
    *param_1 = *(int *)(*param_1 + 0x30);
    free(iVar3);
    uVar2 = 1;
  }
  return uVar2;
}

