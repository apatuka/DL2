// FUN_0044da3c @ 0044da3c size=276 sig=undefined FUN_0044da3c() cc=unknown
// callers: FUN_0044db50,FUN_00460a74
// callees: FUN_00445b94

int FUN_0044da3c(int param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  ushort uVar6;
  int iVar7;
  byte bVar8;
  ushort *local_18;
  int local_10;
  undefined *local_8;
  
  local_8 = (undefined *)0x0;
  bVar1 = 0;
  local_10 = 0;
  local_18 = (ushort *)(param_1 + 0x890);
  do {
    uVar6 = *local_18;
    for (iVar7 = 0; (uVar6 != 0 && (iVar7 < 0x10)); iVar7 = iVar7 + 1) {
      if ((uVar6 & 1) != 0) {
        iVar2 = local_10 * 0x10 + iVar7;
        iVar4 = iVar2 * 0xadc;
        puVar5 = &DAT_005a43d0 + iVar4;
        if ((((&DAT_005a43f1)[iVar4] == '\0') &&
            ((*(byte *)((int)&DAT_005a43ec + iVar4 + 1) & 1) == 0)) &&
           ((&DAT_005a444e)[iVar4] != '\0')) {
          if ((*(char *)(param_1 + 0x20) == (&DAT_005a43f0)[iVar4]) &&
             (iVar3 = FUN_00445b94(puVar5,0xc), iVar3 != 0)) {
            return (int)(short)(&DAT_005a43ea)[iVar2 * 0x56e];
          }
          bVar8 = local_8 == (undefined *)0x0;
          if ((&DAT_005a43f0)[iVar4] == -1) {
            bVar8 = bVar8 | 2;
          }
          if ((&DAT_005a43f0)[iVar4] == *(char *)(param_1 + 0x20)) {
            bVar8 = bVar8 | 4;
          }
          iVar2 = FUN_00445b94(puVar5,0xc);
          if (iVar2 != 0) {
            bVar8 = bVar8 | 8;
          }
          if (bVar1 < bVar8) {
            local_8 = puVar5;
            bVar1 = bVar8;
          }
        }
      }
      uVar6 = (short)uVar6 >> 1;
    }
    local_10 = local_10 + 1;
    local_18 = local_18 + 1;
    if (6 < local_10) {
      if (local_8 == (undefined *)0x0) {
        iVar7 = 0;
      }
      else {
        iVar7 = (int)*(short *)(local_8 + 0x1a);
      }
      return iVar7;
    }
  } while( true );
}

