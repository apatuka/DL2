// FUN_00472578 @ 00472578 size=339 sig=undefined FUN_00472578() cc=unknown
// callers: FUN_00472578,FUN_004726cc,FUN_00472844
// callees: FUN_00472578,FUN_0044d1a4,FUN_004412d4

void FUN_00472578(undefined *param_1,undefined *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  ushort *local_14;
  int local_10;
  ushort local_a;
  int local_8;
  
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x2000 << ((byte)param_4 & 0x1f);
  *(undefined2 *)(param_1 + param_4 * 2 + 0xa70) = (undefined2)param_3;
  if ((param_1 == param_2) || (DAT_00653430 != 0)) {
    DAT_00653430 = 1;
  }
  else {
    local_8 = 0;
    local_14 = (ushort *)(param_1 + 0x890);
    do {
      local_a = *local_14;
      for (local_10 = 0; (local_a != 0 && (local_10 < 0x10)); local_10 = local_10 + 1) {
        if ((local_a & 1) != 0) {
          iVar2 = (local_8 * 0x10 + local_10) * 0xadc;
          puVar3 = &DAT_005a43d0 + iVar2;
          if (((*(short *)(&DAT_005a4e40 + param_4 * 2 + iVar2) == 0) &&
              ((*(byte *)((int)&DAT_005a43ec + iVar2 + 1) & 1) == 0)) &&
             ((param_1[0x22] == (&DAT_005a43f2)[iVar2] || (1 < param_5)))) {
            if (param_4 == (char)(&DAT_005a43f0)[iVar2]) {
LAB_00472685:
              FUN_00472578(puVar3,param_2,param_3 + 1,param_4,param_5);
            }
            else if ((((&DAT_005a43f0)[iVar2] == -1) || (puVar3 == param_2)) ||
                    (((iVar1 = FUN_004412d4(param_4,(int)(char)(&DAT_005a43f0)[iVar2],2), iVar1 != 0
                      && (iVar1 = FUN_0044d1a4(puVar3,9,0), iVar1 == -1)) ||
                     (iVar2 = FUN_004412d4(param_4,(int)(char)(&DAT_005a43f0)[iVar2],0x10),
                     iVar2 != 0)))) {
              if (0 < param_5) goto LAB_00472685;
            }
            else if (2 < param_5) goto LAB_00472685;
          }
        }
        local_a = (short)local_a >> 1;
      }
      local_8 = local_8 + 1;
      local_14 = local_14 + 1;
    } while (local_8 < 7);
  }
  return;
}

