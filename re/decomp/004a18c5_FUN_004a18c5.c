// FUN_004a18c5 @ 004a18c5 size=86 sig=undefined FUN_004a18c5() cc=unknown
// callers: FUN_004a3533,FUN_004a19b4,FUN_004a43da,FUN_004a42f0
// callees: FUN_00498ba9,FUN_0048f774,strlen,FUN_004a6964

int FUN_004a18c5(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if ((param_1 != 0) || (param_2 != 0)) {
    if ((param_2 == 0) && (param_1 != 0)) {
      param_2 = strlen(param_1);
      param_2 = param_2 + 1;
    }
    iVar1 = FUN_00498ba9(param_2);
    if (iVar1 != 0) {
      if (param_1 == 0) {
        FUN_0048f774(iVar1,param_2,0);
      }
      else {
        FUN_004a6964(iVar1,param_1);
      }
    }
  }
  return iVar1;
}

