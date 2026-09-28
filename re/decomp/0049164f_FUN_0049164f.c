// FUN_0049164f @ 0049164f size=115 sig=undefined FUN_0049164f() cc=unknown
// callers: FUN_0049185e
// callees: FUN_00498b98,FUN_0048f774,FUN_0048f992,FUN_0048fbbf,FUN_0048f8e8,FUN_00498aab

int FUN_0049164f(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar1 = FUN_0048f8e8(param_1,param_2);
  if (iVar1 != 0) {
    iVar3 = FUN_00498b98(0x88);
    if (iVar3 == 0) {
      FUN_0048fbbf(iVar1,0);
    }
    else {
      piVar2 = (int *)FUN_00498aab(iVar3,1);
      FUN_0048f774(piVar2,0x88,0);
      FUN_0048f992(iVar1,piVar2 + 2,0x80);
      *piVar2 = iVar1;
      piVar2[1] = -1;
      FUN_00498aab(iVar3,0);
    }
  }
  return iVar3;
}

