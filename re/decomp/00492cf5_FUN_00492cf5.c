// FUN_00492cf5 @ 00492cf5 size=114 sig=undefined FUN_00492cf5() cc=unknown
// callers: FUN_0049e007
// callees: FUN_0048f7f1,strlen

void FUN_00492cf5(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    iVar1 = strlen(*param_1);
    if (param_1[6] < param_1[7]) {
      iVar3 = param_1[6];
    }
    else {
      iVar3 = param_1[7];
    }
    if (param_1[6] < param_1[7]) {
      iVar2 = param_1[7];
    }
    else {
      iVar2 = param_1[6];
    }
    if (param_2 == 0) {
      if (iVar2 == iVar3) {
        if (iVar3 == 0) {
          return;
        }
        iVar3 = iVar3 + -1;
      }
    }
    else if (iVar2 == iVar3) {
      if (iVar1 <= iVar2) {
        return;
      }
      iVar2 = iVar2 + 1;
    }
    FUN_0048f7f1(iVar2 + *param_1,*param_1 + iVar3,(iVar1 + 1) - iVar2);
    param_1[7] = iVar3;
    param_1[6] = iVar3;
  }
  return;
}

