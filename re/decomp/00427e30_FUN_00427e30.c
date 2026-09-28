// FUN_00427e30 @ 00427e30 size=44 sig=undefined FUN_00427e30() cc=unknown
// callers: FUN_00468470
// callees: FUN_00427ca0,FUN_00427c40,FUN_00427d74,FUN_00427da0

int FUN_00427e30(void)

{
  int iVar1;
  
  iVar1 = FUN_00427ca0();
  if (iVar1 == 0) {
    return 6;
  }
  FUN_00427c40();
  do {
    iVar1 = FUN_00427da0();
  } while (iVar1 == 0);
  FUN_00427d74();
  return iVar1;
}

