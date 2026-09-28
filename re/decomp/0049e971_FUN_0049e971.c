// FUN_0049e971 @ 0049e971 size=119 sig=undefined FUN_0049e971() cc=unknown
// callers: FUN_004a43da
// callees: 

undefined4 FUN_0049e971(int param_1,int param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  
  if ((param_1 == 0) || (param_3 == (int *)0x0)) {
    uVar2 = 0;
  }
  else {
    if (param_2 == 0) {
      piVar3 = (int *)(param_1 + 0xcc);
    }
    else if (param_2 == 1) {
      piVar3 = (int *)(param_1 + 0xd8);
    }
    else if (param_2 == 2) {
      piVar3 = (int *)(param_1 + 0x9c);
    }
    else {
      if (param_2 != 3) {
        return 0;
      }
      piVar3 = (int *)(param_1 + 0xa8);
    }
    for (iVar1 = 0; iVar1 < *param_3; iVar1 = iVar1 + 1) {
      if (iVar1 < 3) {
        param_3[iVar1 + 1] = *piVar3;
        piVar3 = piVar3 + 1;
      }
      else {
        param_3[iVar1 + 1] = 0x20000000;
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}

