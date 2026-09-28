// FUN_00410cdc @ 00410cdc size=70 sig=undefined FUN_00410cdc() cc=unknown
// callers: FUN_00410d24
// callees: 

byte FUN_00410cdc(void)

{
  byte bVar1;
  
  if (DAT_00533198 == 0) {
    DAT_00533198 = 8;
    DAT_0053319c = *(byte *)(DAT_005331c4 + DAT_005331cc);
    DAT_005331cc = DAT_005331cc + 1;
  }
  bVar1 = DAT_0053319c;
  DAT_0053319c = DAT_0053319c >> 1;
  DAT_00533198 = DAT_00533198 + -1;
  return bVar1 & 1;
}

