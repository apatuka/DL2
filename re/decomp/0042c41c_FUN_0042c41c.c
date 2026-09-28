// FUN_0042c41c @ 0042c41c size=44 sig=undefined FUN_0042c41c() cc=unknown
// callers: FUN_004684d0
// callees: FUN_0042c2fc,FUN_0042c204,FUN_0042c1a4,FUN_0042c328

int FUN_0042c41c(void)

{
  int iVar1;
  
  iVar1 = FUN_0042c204();
  if (iVar1 == 0) {
    return 0xd;
  }
  FUN_0042c1a4();
  do {
    iVar1 = FUN_0042c328();
  } while (iVar1 == 0);
  FUN_0042c2fc();
  return iVar1;
}

