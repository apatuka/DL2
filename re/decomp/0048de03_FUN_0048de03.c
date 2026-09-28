// FUN_0048de03 @ 0048de03 size=16 sig=undefined FUN_0048de03() cc=unknown
// callers: FUN_00494c15,FUN_004a0f18,FUN_00426ab0,FUN_00426868
// callees: GetTickCount

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0048de03(void)

{
  DWORD DVar1;
  
  DVar1 = GetTickCount();
  return DVar1 - _DAT_0065e994;
}

