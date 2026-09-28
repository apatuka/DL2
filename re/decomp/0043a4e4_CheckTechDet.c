// CheckTechDet @ 0043a4e4 size=129 sig=undefined CheckTechDet() cc=unknown
// callers: FUN_0043a568
// callees: FUN_0043a33c,DebugMessage,FUN_0048db5d,FUN_004a2cb5,FUN_0043a4dc
// strings: \"gpTechDet NULL in CheckTechDet()\"

/* auto-named from string evidence: CheckTechDet */

longlong CheckTechDet(void)

{
  int iVar1;
  uint local_4;
  
  if (DAT_004c4858 == 0) {
    DebugMessage(s_gpTechDet_NULL_in_CheckTechDet___004c486a);
    return (ulonglong)local_4 << 0x20;
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_0043a33c();
  iVar1 = FUN_004a2cb5(DAT_004c4858,&local_4);
  if ((((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004c4858 + 100) == 0)) && (local_4 == 5)) {
    FUN_0043a4dc();
    DAT_004d59a4 = 0;
    return CONCAT44(local_4,local_4);
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

