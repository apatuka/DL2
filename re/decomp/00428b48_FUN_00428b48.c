// FUN_00428b48 @ 00428b48 size=44 sig=undefined FUN_00428b48() cc=unknown
// callers: FUN_00468214
// callees: FUN_00428860,FUN_00428a24,FUN_004288c0,FUN_00428a50

int FUN_00428b48(void)

{
  int iVar1;
  
  iVar1 = FUN_004288c0();
  if (iVar1 == 0) {
    return 4;
  }
  FUN_00428860();
  do {
    iVar1 = FUN_00428a50();
  } while (iVar1 == 0);
  FUN_00428a24();
  return iVar1;
}

