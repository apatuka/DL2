// FUN_0049e9e8 @ 0049e9e8 size=130 sig=undefined FUN_0049e9e8() cc=unknown
// callers: FUN_004a3533,FUN_004a43da
// callees: 

undefined4 FUN_0049e9e8(int param_1,int param_2,int *param_3)

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
    iVar1 = 0;
    do {
      if (iVar1 < *param_3) {
        if ((*(byte *)((int)param_3 + iVar1 * 4 + 7) & 0x20) == 0) {
          *piVar3 = param_3[iVar1 + 1];
        }
      }
      else {
        *piVar3 = 0x40000000;
      }
      piVar3 = piVar3 + 1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 3);
    uVar2 = 1;
  }
  return uVar2;
}

