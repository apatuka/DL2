// FUN_00458298 @ 00458298 size=69 sig=undefined FUN_00458298() cc=unknown
// callers: FUN_00426868,FUN_004780e4,FUN_00478090,FUN_00468214,FUN_00468a28,FUN_0046ce10
// callees: CGNet_Cleanup

undefined4 FUN_00458298(void)

{
  if ((DAT_004d1718 != 0) && (DAT_004d1704 != 0)) {
    CGNet_Cleanup(DAT_004d1704);
  }
  DAT_004d1718 = 0;
  DAT_004d1710 = 0;
  DAT_004d1708 = 0;
  DAT_004d170c = 0;
  DAT_004d1704 = 0;
  return 1;
}

