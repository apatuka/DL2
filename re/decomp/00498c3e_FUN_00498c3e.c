// FUN_00498c3e @ 00498c3e size=82 sig=undefined FUN_00498c3e() cc=unknown
// callers: 
// callees: FUN_00498b4c,GlobalLock,FUN_004989b1,GlobalUnlock,FUN_0048f7f1

bool FUN_00498c3e(HGLOBAL param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  LPVOID pvVar3;
  
  iVar1 = FUN_004989b1(param_1);
  iVar2 = FUN_00498b4c(param_1,param_3 + iVar1);
  if (iVar2 == 0) {
    pvVar3 = GlobalLock(param_1);
    FUN_0048f7f1(param_2 + (int)pvVar3,(int)pvVar3 + param_3 + param_2,iVar1 - param_2);
    GlobalUnlock(param_1);
  }
  return iVar2 == 0;
}

