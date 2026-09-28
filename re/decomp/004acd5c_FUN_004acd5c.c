// FUN_004acd5c @ 004acd5c size=18 sig=undefined FUN_004acd5c() cc=unknown
// callers: FUN_004acdd4,FUN_004ace78,FUN_004ace38,FUN_004ad1a4,FUN_004acd70,FUN_004ac688,FUN_004acf20
// callees: FUN_004accf0,GetLastError

void FUN_004acd5c(void)

{
  DWORD DVar1;
  
  DVar1 = GetLastError();
  FUN_004accf0(DVar1 & 0xffff);
  return;
}

