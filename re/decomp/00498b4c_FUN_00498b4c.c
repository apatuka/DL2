// FUN_00498b4c @ 00498b4c size=38 sig=undefined FUN_00498b4c() cc=unknown
// callers: FUN_00498c3e,FUN_00496358,FUN_0049028e
// callees: GetLastError,GlobalReAlloc

bool FUN_00498b4c(HGLOBAL param_1,SIZE_T param_2)

{
  HGLOBAL pvVar1;
  
  pvVar1 = GlobalReAlloc(param_1,param_2,2);
  if (pvVar1 == (HGLOBAL)0x0) {
    GetLastError();
  }
  return pvVar1 == (HGLOBAL)0x0;
}

