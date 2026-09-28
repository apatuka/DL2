// FUN_00416d08 @ 00416d08 size=233 sig=undefined FUN_00416d08() cc=unknown
// callers: FUN_0040ef18,FUN_00416e70,FUN_00410870
// callees: FUN_00416cc0

undefined4 FUN_00416d08(int param_1)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  ushort *local_c;
  int local_8;
  
  if (((*(char *)(param_1 + 7) != '\t') && (*(char *)(param_1 + 7) != '\n')) &&
     (*(short *)(param_1 + 0x28) < 100)) {
    iVar1 = *(int *)(param_1 + 0x3c);
    if ((*(char *)(iVar1 + 0x21) == '\0') || (*(char *)(iVar1 + 0x20) != *(char *)(param_1 + 8))) {
      if ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] == '\x02') {
        local_c = (ushort *)(iVar1 + 0x890);
        local_8 = 0;
        do {
          uVar3 = *local_c;
          for (iVar1 = 0; (uVar3 != 0 && (iVar1 < 0x10)); iVar1 = iVar1 + 1) {
            if ((uVar3 & 1) != 0) {
              iVar2 = (local_8 * 0x10 + iVar1) * 0xadc;
              if ((((&DAT_005a43f1)[iVar2] != '\0') &&
                  ((&DAT_005a43f0)[iVar2] == *(char *)(param_1 + 8))) &&
                 (iVar2 = FUN_00416cc0(&DAT_005a43d0 + iVar2), iVar2 != 0)) {
                return 1;
              }
            }
            uVar3 = (short)uVar3 >> 1;
          }
          local_8 = local_8 + 1;
          local_c = local_c + 1;
        } while (local_8 < 7);
      }
    }
    else {
      iVar1 = FUN_00416cc0(iVar1);
      if (iVar1 != 0) {
        return 1;
      }
    }
  }
  return 0;
}

