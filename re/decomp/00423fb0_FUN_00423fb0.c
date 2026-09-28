// FUN_00423fb0 @ 00423fb0 size=44 sig=undefined FUN_00423fb0() cc=unknown
// callers: FUN_0045e7a4
// callees: FUN_00423dd8,FUN_00423f44,FUN_00423e38,FUN_00423f18

int FUN_00423fb0(void)

{
  int iVar1;
  
  iVar1 = FUN_00423e38();
  if (iVar1 == 0) {
    return 7;
  }
  FUN_00423dd8();
  do {
    iVar1 = FUN_00423f44();
  } while (iVar1 == 0);
  FUN_00423f18();
  return iVar1;
}

