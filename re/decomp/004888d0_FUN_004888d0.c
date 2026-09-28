// FUN_004888d0 @ 004888d0 size=28 sig=undefined FUN_004888d0() cc=unknown
// callers: FUN_00488ce9,FUN_00488dd3,FUN_00488b0f,FUN_00488b59,FUN_00488a67,FUN_00488d30,FUN_00488998,FUN_00488c1c,FUN_00488a09,FUN_00488e9d,FUN_00488aae,FUN_00488e1b,FUN_004888ec,FUN_00488c95,FUN_00488ba3,FUN_00488d7e
// callees: FUN_004950bc,GetLastError

DWORD FUN_004888d0(void)

{
  DWORD DVar1;
  
  DVar1 = GetLastError();
  FUN_004950bc(DVar1);
  if (0 < (int)DVar1) {
    DVar1 = -DVar1;
  }
  return DVar1;
}

