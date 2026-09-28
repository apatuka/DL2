// FUN_004acf08 @ 004acf08 size=23 sig=undefined FUN_004acf08() cc=unknown
// callers: FUN_004acfa4
// callees: GetFileType

bool FUN_004acf08(HANDLE param_1)

{
  DWORD DVar1;
  
  DVar1 = GetFileType(param_1);
  return DVar1 == 2;
}

