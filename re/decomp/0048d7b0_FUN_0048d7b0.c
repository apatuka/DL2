// FUN_0048d7b0 @ 0048d7b0 size=42 sig=undefined FUN_0048d7b0() cc=unknown
// callers: FUN_0048d205
// callees: FUN_00498a30,FUN_00498bba

int FUN_0048d7b0(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_1 != 0) {
    iVar1 = FUN_00498bba(param_1);
    if (iVar1 != 0) {
      FUN_00498a30(iVar1,0);
    }
  }
  return iVar1;
}

