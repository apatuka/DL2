// FUN_00402fe8 @ 00402fe8 size=371 sig=undefined FUN_00402fe8() cc=unknown
// callers: 
// callees: memset

void FUN_00402fe8(int param_1,int param_2,int param_3)

{
  int *piVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined2 *puVar7;
  ushort *local_14;
  ushort *local_c;
  int local_8;
  
  memset(param_3,0,0xad4);
  memset(&DAT_0052205c,0,0xe);
  for (puVar7 = &DAT_005f0410; puVar7 < &DAT_00645370; puVar7 = puVar7 + 0x91) {
    if (((puVar7 != (undefined2 *)0x0) && (*(char *)(puVar7 + 7) == param_2)) &&
       (sVar2 = puVar7[4], iVar4 = sVar2 * 0xadc, (char)(&DAT_005a43f0)[iVar4] == param_1)) {
      if (*(char *)((int)puVar7 + 5) == '\a') {
        iVar6 = 0;
        local_8 = param_3;
        do {
          uVar5 = 1 << ((byte)iVar6 & 0x1f);
          if (((uVar5 & *(uint *)(&DAT_005a4c74 + iVar4)) != 0) ||
             ((uVar5 & *(uint *)(&DAT_005a4c70 + iVar4)) != 0)) {
            piVar1 = (int *)(local_8 + *(char *)((int)puVar7 + 5) * 4);
            *piVar1 = *piVar1 + 1;
          }
          iVar6 = iVar6 + 1;
          local_8 = local_8 + 0x54;
        } while (iVar6 < 0x20);
        iVar4 = 0;
        local_c = &DAT_005a4c60 + sVar2 * 0x56e;
        local_14 = &DAT_0052205c;
        do {
          uVar3 = *local_c;
          for (iVar6 = 0; (uVar3 != 0 && (iVar6 < 0x10)); iVar6 = iVar6 + 1) {
            if (((uVar3 & 1) != 0) && ((&DAT_005a43f1)[(iVar4 * 0x10 + iVar6) * 0xadc] == '\0')) {
              *local_14 = *local_14 | 1 << ((byte)iVar6 & 0x1f);
            }
            uVar3 = (short)uVar3 >> 1;
          }
          iVar4 = iVar4 + 1;
          local_14 = local_14 + 1;
          local_c = local_c + 1;
        } while (iVar4 < 7);
        piVar1 = (int *)(param_3 + 0xa80 + *(char *)((int)puVar7 + 5) * 4);
        *piVar1 = *piVar1 + 1;
      }
      else {
        piVar1 = (int *)(param_3 + (char)(&DAT_005a43f2)[iVar4] * 0x54 +
                        *(char *)((int)puVar7 + 5) * 4);
        *piVar1 = *piVar1 + 1;
        piVar1 = (int *)(param_3 + 0xa80 + *(char *)((int)puVar7 + 5) * 4);
        *piVar1 = *piVar1 + 1;
      }
    }
  }
  return;
}

