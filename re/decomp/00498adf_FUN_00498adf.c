// FUN_00498adf @ 00498adf size=20 sig=undefined FUN_00498adf() cc=unknown
// callers: FUN_004a5699
// callees: GlobalFlags

uint FUN_00498adf(HGLOBAL param_1)

{
  UINT UVar1;
  
  UVar1 = GlobalFlags(param_1);
  return UVar1 & 0x100;
}

