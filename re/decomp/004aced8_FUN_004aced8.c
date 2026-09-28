// FUN_004aced8 @ 004aced8 size=45 sig=undefined FUN_004aced8() cc=unknown
// callers: FUN_004acb90
// callees: GetFileType

bool FUN_004aced8(uint param_1)

{
  DWORD DVar1;
  
  if (DAT_00520194 <= param_1) {
    return false;
  }
  DVar1 = GetFileType(*(HANDLE *)(&DAT_0069f484 + param_1 * 4));
  return DVar1 == 2;
}

