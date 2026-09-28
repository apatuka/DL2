// FUN_0049415f @ 0049415f size=150 sig=undefined FUN_0049415f() cc=unknown
// callers: FUN_00415274,FUN_004152c0
// callees: FUN_00494b06,EnterCriticalSection,LeaveCriticalSection,FUN_004940f0,FUN_00498aab

int FUN_0049415f(int param_1)

{
  int iVar1;
  
  if (DAT_0051b83c != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  iVar1 = DAT_0065ec80;
  if (param_1 != DAT_0065ec80) {
    if (DAT_0065ec80 != 0) {
      FUN_00498aab(DAT_0065ec80,0);
    }
    FUN_00494b06();
    DAT_0065ec80 = param_1;
    if (param_1 == 0) {
      DAT_0065ecb0 = 0;
    }
    else {
      DAT_0065ecb0 = FUN_00498aab(param_1,1);
    }
    FUN_004940f0(1000);
    DAT_0051dc70 = 0;
  }
  if (DAT_0051b83c != 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  return iVar1;
}

