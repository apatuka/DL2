// FUN_0048ddd1 @ 0048ddd1 size=25 sig=undefined FUN_0048ddd1() cc=unknown
// callers: FUN_004a2847,FUN_0048e51c
// callees: GetTickCount

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_0048ddd1(void)

{
  DWORD DVar1;
  
  DVar1 = GetTickCount();
  return (DVar1 - _DAT_0065e994) / 0xe;
}

