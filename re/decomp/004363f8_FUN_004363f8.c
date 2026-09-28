// FUN_004363f8 @ 004363f8 size=32 sig=undefined FUN_004363f8() cc=unknown
// callers: FUN_00467c8c
// callees: FUN_004361b8,FUN_0043632c,FUN_00436184

int FUN_004363f8(void)

{
  int iVar1;
  
  iVar1 = FUN_004361b8();
  if (iVar1 == 0) {
    return 0xd;
  }
  FUN_00436184();
  do {
    iVar1 = FUN_0043632c();
  } while (iVar1 == 0);
  return iVar1;
}

