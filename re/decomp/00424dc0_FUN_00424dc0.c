// FUN_00424dc0 @ 00424dc0 size=103 sig=undefined FUN_00424dc0() cc=unknown
// callers: FUN_00425364
// callees: Timer_Init,FUN_004249c0

undefined4 FUN_00424dc0(void)

{
  int iVar1;
  
  if (DAT_00557548 != 0) {
    return 1;
  }
  iVar1 = Timer_Init(DAT_00557530);
  if (iVar1 != 0) {
    FUN_004249c0();
    return 1;
  }
  DAT_004c5b74 = DAT_004b7c84 + 10;
  DAT_004c5b70 = DAT_004b7c88 + 0xd;
  DAT_004c5b7c = DAT_004b7c84 + 0xd2;
  DAT_004c5b78 = DAT_004b7c88 + 0xd5;
  return 1;
}

