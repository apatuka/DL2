// FUN_0042c054 @ 0042c054 size=44 sig=undefined FUN_0042c054() cc=unknown
// callers: FUN_0046878c
// callees: FUN_0042baf8,FUN_0042bc24,FUN_0042ba98,FUN_0042bc50

int FUN_0042c054(void)

{
  int iVar1;
  
  iVar1 = FUN_0042baf8();
  if (iVar1 == 0) {
    return 0x3c;
  }
  FUN_0042ba98();
  do {
    iVar1 = FUN_0042bc50();
  } while (iVar1 == 0);
  FUN_0042bc24();
  return iVar1;
}

