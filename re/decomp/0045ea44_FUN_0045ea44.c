// FUN_0045ea44 @ 0045ea44 size=39 sig=undefined FUN_0045ea44() cc=unknown
// callers: FUN_0043baf4,FUN_0047361c
// callees: ChCht,FUN_00423d84

void FUN_0045ea44(void)

{
  int iVar1;
  
  iVar1 = FUN_00423d84();
  if (iVar1 != 7) {
    if (iVar1 != 1) {
      return;
    }
    iVar1 = ChCht(0,1,0);
    if (iVar1 == 0) {
      return;
    }
  }
  DAT_0058f1ec = 1;
  return;
}

