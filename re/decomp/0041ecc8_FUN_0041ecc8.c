// FUN_0041ecc8 @ 0041ecc8 size=124 sig=undefined FUN_0041ecc8() cc=unknown
// callers: FUN_0041edd8
// callees: Timer_Init,FUN_00412584,FUN_0041e914

undefined4 FUN_0041ecc8(void)

{
  int iVar1;
  
  if (DAT_004b7990 != 0) {
    return 1;
  }
  iVar1 = Timer_Init(DAT_004b7988);
  if (iVar1 != 0) {
    FUN_00412584(DAT_004b7988,3);
    DAT_004b7988 = 0;
    FUN_0041e914();
    return 1;
  }
  DAT_004c5b74 = DAT_004b7978 + 0x21;
  DAT_004c5b70 = DAT_004b797c + 0x14;
  DAT_004c5b7c = DAT_004b7978 + 0xe9;
  DAT_004c5b78 = DAT_004b797c + 0xdc;
  return 1;
}

