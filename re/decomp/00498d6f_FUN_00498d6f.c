// FUN_00498d6f @ 00498d6f size=49 sig=undefined FUN_00498d6f() cc=unknown
// callers: FUN_0046ff98,FUN_004935d2
// callees: FUN_00498d18,GlobalFree,FUN_00498ccb

void FUN_00498d6f(HGLOBAL param_1)

{
  HGLOBAL pvVar1;
  
  if (param_1 == (HGLOBAL)0x0) {
    param_1 = (HGLOBAL)FUN_00498d18();
  }
  if (param_1 != (HGLOBAL)0x0) {
    GlobalFree(param_1);
    pvVar1 = (HGLOBAL)FUN_00498d18();
    if (param_1 == pvVar1) {
      FUN_00498ccb(0);
    }
  }
  return;
}

