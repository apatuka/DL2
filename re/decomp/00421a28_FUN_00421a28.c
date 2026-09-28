// FUN_00421a28 @ 00421a28 size=44 sig=undefined FUN_00421a28() cc=unknown
// callers: FUN_0045e7a4
// callees: FUN_00421990,FUN_00421904,FUN_004219bc,FUN_004218a4

int FUN_00421a28(void)

{
  int iVar1;
  
  iVar1 = FUN_00421904();
  if (iVar1 == 0) {
    return 4;
  }
  FUN_004218a4();
  do {
    iVar1 = FUN_004219bc();
  } while (iVar1 == 0);
  FUN_00421990();
  return iVar1;
}

