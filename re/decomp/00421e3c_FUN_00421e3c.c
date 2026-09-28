// FUN_00421e3c @ 00421e3c size=117 sig=undefined FUN_00421e3c() cc=unknown
// callers: FUN_00422f7c
// callees: FUN_00421a54,Timer_Init,FUN_00412584

undefined4 FUN_00421e3c(void)

{
  int iVar1;
  
  if (DAT_004b7b60 != 0) {
    return 1;
  }
  iVar1 = Timer_Init(DAT_004b7b58);
  if (iVar1 != 0) {
    FUN_00412584(DAT_004b7b58,3);
    DAT_004b7b58 = 0;
    FUN_00421a54();
    return 1;
  }
  DAT_004b7b64 = 0;
  DAT_004c5b74 = 0x53;
  DAT_004c5b70 = 0x10;
  DAT_004c5b7c = 0x11b;
  DAT_004c5b78 = 0xd8;
  return 1;
}

