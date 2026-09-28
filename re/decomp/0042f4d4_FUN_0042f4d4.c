// FUN_0042f4d4 @ 0042f4d4 size=128 sig=undefined FUN_0042f4d4() cc=unknown
// callers: FUN_0042f680
// callees: 

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0042f4d4(void)

{
  int iVar1;
  undefined *puVar2;
  
  iVar1 = DAT_004c4224;
  if ((DAT_004c4224 != 0) && ((*(byte *)(&DAT_005a43ec + DAT_004c4224 * 0x2b7) & 4) == 0)) {
    (&DAT_005a43ec)[DAT_004c4224 * 0x2b7] = (&DAT_005a43ec)[DAT_004c4224 * 0x2b7] | 2;
    _DAT_00558c74 = iVar1;
    return iVar1;
  }
  iVar1 = 0;
  puVar2 = &DAT_005a43d0;
  while( true ) {
    if (DAT_004d5b18 < iVar1) {
      return -1;
    }
    if ((puVar2[0x1c] & 4) == 0) break;
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0xadc;
  }
  *(uint *)(puVar2 + 0x1c) = *(uint *)(puVar2 + 0x1c) | 2;
  return (int)*(short *)(puVar2 + 0x1a);
}

