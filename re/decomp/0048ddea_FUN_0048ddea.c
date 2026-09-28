// FUN_0048ddea @ 0048ddea size=25 sig=undefined FUN_0048ddea() cc=unknown
// callers: 
// callees: GetTickCount

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_0048ddea(void)

{
  DWORD DVar1;
  
  DVar1 = GetTickCount();
  return (DVar1 - _DAT_0065e994) / 0xe;
}

