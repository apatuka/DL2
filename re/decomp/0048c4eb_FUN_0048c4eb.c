// FUN_0048c4eb @ 0048c4eb size=112 sig=undefined FUN_0048c4eb() cc=unknown
// callers: FUN_004a52db
// callees: FUN_0048f7f1,FUN_0048c2c5,FUN_0048c3f4

void FUN_0048c4eb(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_0048c2c5(param_1);
  if (iVar2 != 0) {
    if ((param_2 < param_1[4]) && (1 < param_1[2])) {
      iVar3 = (param_1[2] + -1) * param_2 + *param_1;
      iVar2 = (param_1[2] + -1) * param_1[4] + *param_1;
      iVar1 = param_1[2];
      while (iVar1 = iVar1 + -1, iVar1 != 0) {
        FUN_0048f7f1(iVar3,iVar2,param_2);
        iVar3 = iVar3 - param_2;
        iVar2 = iVar2 - param_1[4];
      }
    }
    FUN_0048c3f4(param_1);
  }
  return;
}

