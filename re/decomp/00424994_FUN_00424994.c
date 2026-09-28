// FUN_00424994 @ 00424994 size=44 sig=undefined FUN_00424994() cc=unknown
// callers: FUN_0045e7a4
// callees: FUN_00424564,FUN_004244d4,FUN_00424474,FUN_00424590

int FUN_00424994(void)

{
  int iVar1;
  
  iVar1 = FUN_004244d4();
  if (iVar1 == 0) {
    return 0x19;
  }
  FUN_00424474();
  do {
    iVar1 = FUN_00424590();
  } while (iVar1 == 0);
  FUN_00424564();
  return iVar1;
}

