// FUN_00427100 @ 00427100 size=152 sig=undefined FUN_00427100() cc=unknown
// callers: FUN_00427440
// callees: FUN_00427278

void FUN_00427100(int param_1,int param_2)

{
  int iVar1;
  
  if (((DAT_004b7d34 != 0) && (DAT_00557788 == DAT_0058f1f4)) &&
     (iVar1 = (int)(short)(&DAT_005a0552)[param_2 * 200 + param_1 * 5],
     (*(byte *)(&DAT_005a43ec + iVar1 * 0x2b7) & 4) == 0)) {
    if (DAT_00557790 != 0) {
      (&DAT_005a43ec)[DAT_00557790 * 0x2b7] = (&DAT_005a43ec)[DAT_00557790 * 0x2b7] & 0xfffffffd;
    }
    (&DAT_005a43ec)[iVar1 * 0x2b7] = (&DAT_005a43ec)[iVar1 * 0x2b7] | 2;
    DAT_00557790 = iVar1;
    FUN_00427278();
  }
  return;
}

