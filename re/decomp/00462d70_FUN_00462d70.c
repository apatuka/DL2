// FUN_00462d70 @ 00462d70 size=383 sig=undefined FUN_00462d70() cc=unknown
// callers: FUN_00466218,FUN_00466128,FUN_00463014
// callees: memset

void FUN_00462d70(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 *local_10;
  int local_8;
  
  memset(&DAT_005a4c60 + param_1 * 0x56e,0,0xe);
  local_10 = &DAT_005a4450 + param_1 * 0x2b7;
  for (local_8 = 0; local_8 < (char)(&DAT_005a444e)[param_1 * 0xadc]; local_8 = local_8 + 1) {
    iVar2 = (int)*(char *)*local_10;
    iVar3 = (int)((char *)*local_10)[1];
    if (iVar2 != 0) {
      sVar1 = *(short *)(&DAT_005a0548 + iVar2 * 10 + iVar3 * 400);
      if (sVar1 != param_1) {
        (&DAT_005a4c60)[param_1 * 0x56e + ((int)sVar1 >> 4)] =
             (&DAT_005a4c60)[param_1 * 0x56e + ((int)sVar1 >> 4)] | 1 << ((byte)sVar1 & 0xf);
      }
    }
    if (iVar3 != 0) {
      sVar1 = *(short *)(&DAT_005a03c2 + iVar2 * 10 + iVar3 * 400);
      if (sVar1 != param_1) {
        (&DAT_005a4c60)[param_1 * 0x56e + ((int)sVar1 >> 4)] =
             (&DAT_005a4c60)[param_1 * 0x56e + ((int)sVar1 >> 4)] | 1 << ((byte)sVar1 & 0xf);
      }
    }
    if (iVar3 < DAT_004d5b1b + -1) {
      sVar1 = (&DAT_005a06e2)[iVar3 * 200 + iVar2 * 5];
      if (sVar1 != param_1) {
        (&DAT_005a4c60)[param_1 * 0x56e + ((int)sVar1 >> 4)] =
             (&DAT_005a4c60)[param_1 * 0x56e + ((int)sVar1 >> 4)] | 1 << ((byte)sVar1 & 0xf);
      }
    }
    if (iVar2 < DAT_004d5b1a + -1) {
      sVar1 = (&DAT_005a055c)[iVar3 * 200 + iVar2 * 5];
      if (sVar1 != param_1) {
        (&DAT_005a4c60)[param_1 * 0x56e + ((int)sVar1 >> 4)] =
             (&DAT_005a4c60)[param_1 * 0x56e + ((int)sVar1 >> 4)] | 1 << ((byte)sVar1 & 0xf);
      }
    }
    local_10 = local_10 + 1;
  }
  return;
}

