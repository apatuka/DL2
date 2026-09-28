// FUN_00417dc8 @ 00417dc8 size=125 sig=undefined FUN_00417dc8() cc=unknown
// callers: FUN_004197dc,FUN_00419684
// callees: 

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00417dc8(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  DAT_004c55f0 = 0;
  _DAT_004c5610 = 0;
  _DAT_004c5630 = 0;
  iVar2 = 0;
  puVar1 = &DAT_004c55f8;
  do {
    if ((DAT_005332bc + iVar2 < 100) && ((&DAT_00533405)[(DAT_005332bc + iVar2) * 0x146] == '\0')) {
      *puVar1 = 0x6b;
      puVar1[1] = iVar2 * 0x25 + 0x16f;
      puVar1[2] = 0x168;
      puVar1[3] = 0x25;
      puVar1[-2] = 1;
    }
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 8;
  } while (iVar2 < 3);
  return;
}

