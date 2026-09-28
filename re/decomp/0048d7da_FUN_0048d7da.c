// FUN_0048d7da @ 0048d7da size=80 sig=undefined FUN_0048d7da() cc=unknown
// callers: 
// callees: FUN_0048f7f1,FUN_0048d76a,FUN_00498aab

int FUN_0048d7da(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  
  iVar1 = FUN_0048d76a((int)*(short *)(param_1 + 2),(int)*(short *)(param_1 + 4));
  if (iVar1 != 0) {
    puVar2 = (undefined2 *)FUN_00498aab(iVar1,1);
    FUN_0048f7f1(param_1,puVar2,*(short *)(param_1 + 2) * 4 + 8);
    *puVar2 = 0;
    FUN_00498aab(iVar1,0);
  }
  return iVar1;
}

