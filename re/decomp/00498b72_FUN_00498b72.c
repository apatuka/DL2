// FUN_00498b72 @ 00498b72 size=38 sig=undefined FUN_00498b72() cc=unknown
// callers: 
// callees: GetLastError,GlobalReAlloc

bool FUN_00498b72(HGLOBAL param_1,SIZE_T param_2)

{
  HGLOBAL pvVar1;
  
  pvVar1 = GlobalReAlloc(param_1,param_2,0);
  if (pvVar1 == (HGLOBAL)0x0) {
    GetLastError();
  }
  return pvVar1 == (HGLOBAL)0x0;
}

