// FUN_0044ffbc @ 0044ffbc size=65 sig=undefined FUN_0044ffbc() cc=unknown
// callers: FUN_00486e34
// callees: FUN_0044fdf0,FUN_0044fe1c

bool FUN_0044ffbc(void)

{
  int iVar1;
  
  iVar1 = FUN_0044fe1c(9);
  if (iVar1 != 0) {
    iVar1 = FUN_0044fdf0(9);
    return *(int *)(&DAT_004c61a4 + iVar1 * 0x44 + DAT_004d5a94 * 0xd8) <= DAT_0059f154;
  }
  return false;
}

