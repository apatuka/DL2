// FUN_00426ba4 @ 00426ba4 size=44 sig=undefined FUN_00426ba4() cc=unknown
// callers: FUN_00468800
// callees: FUN_00426808,FUN_00426a84,FUN_00426868,FUN_00426ab0

int FUN_00426ba4(void)

{
  int iVar1;
  
  iVar1 = FUN_00426868();
  if (iVar1 == 0) {
    return 6;
  }
  FUN_00426808();
  do {
    iVar1 = FUN_00426ab0();
  } while (iVar1 == 0);
  FUN_00426a84();
  return iVar1;
}

