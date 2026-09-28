// FUN_00431088 @ 00431088 size=157 sig=undefined FUN_00431088() cc=unknown
// callers: FUN_00435ed0,FUN_00431128
// callees: FUN_00432cf4,FUN_00430c38,FUN_0044a000,FUN_00430bd0,Timer_Init,FUN_00412584,FUN_00430ba8

undefined4 FUN_00431088(void)

{
  int iVar1;
  
  if (DAT_004c42ec != 0) {
    return 1;
  }
  if (DAT_00558d58 == 0) {
    FUN_00430ba8();
    FUN_00432cf4();
    FUN_0044a000();
  }
  iVar1 = Timer_Init(DAT_004c42e4);
  if (iVar1 != 0) {
    FUN_00412584(DAT_004c42e4,3);
    DAT_004c42e4 = 0;
    FUN_00430c38();
    if (DAT_00558d58 == 0) {
      FUN_00430bd0();
    }
    return 1;
  }
  DAT_004c5b74 = 7;
  DAT_004c5b70 = 10;
  DAT_004c5b7c = 0xcf;
  DAT_004c5b78 = 0xd2;
  DAT_004c42f0 = 0;
  return 1;
}

