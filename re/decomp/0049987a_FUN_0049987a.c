// FUN_0049987a @ 0049987a size=438 sig=undefined FUN_0049987a() cc=unknown
// callers: FUN_00499a30
// callees: 

void FUN_0049987a(int param_1,int param_2,byte param_3,uint *param_4,undefined1 *param_5)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint *puVar9;
  byte bVar10;
  int iVar11;
  int local_3c;
  int local_38;
  uint local_34;
  uint local_30;
  int local_2c;
  int local_28;
  int local_10;
  int local_c;
  undefined1 *local_8;
  
  bVar10 = 8 - param_3;
  iVar3 = 1 << (param_3 & 0x1f);
  iVar11 = 1 << (bVar10 * '\x02' & 0x1f);
  uVar4 = 1 << (bVar10 & 0x1f);
  local_10 = 0;
  if (0 < param_1) {
    do {
      iVar6 = (int)uVar4 >> 1;
      iVar7 = iVar6;
      if (iVar6 < 0) {
        iVar7 = iVar6 + (uint)((uVar4 & 1) != 0);
      }
      iVar7 = (uint)*(byte *)(param_2 + 8 + local_10 * 4) - iVar7;
      iVar8 = iVar6;
      if (iVar6 < 0) {
        iVar8 = iVar6 + (uint)((uVar4 & 1) != 0);
      }
      iVar8 = (uint)*(byte *)(param_2 + 9 + local_10 * 4) - iVar8;
      if (iVar6 < 0) {
        iVar6 = iVar6 + (uint)((uVar4 & 1) != 0);
      }
      iVar6 = (uint)*(byte *)(param_2 + 10 + local_10 * 4) - iVar6;
      local_30 = iVar7 * iVar7 + iVar8 * iVar8 + iVar6 * iVar6;
      local_38 = (iVar11 - ((uint)*(byte *)(param_2 + 8 + local_10 * 4) << (bVar10 & 0x1f))) * 2;
      bVar1 = *(byte *)(param_2 + 9 + local_10 * 4);
      bVar2 = *(byte *)(param_2 + 10 + local_10 * 4);
      local_8 = param_5;
      local_28 = 0;
      puVar9 = param_4;
      if (0 < iVar3) {
        do {
          local_2c = 0;
          local_34 = local_30;
          local_3c = (iVar11 - ((uint)bVar1 << (bVar10 & 0x1f))) * 2;
          if (0 < iVar3) {
            do {
              iVar7 = 0;
              uVar5 = local_34;
              local_c = (iVar11 - ((uint)bVar2 << (bVar10 & 0x1f))) * 2;
              if (0 < iVar3) {
                do {
                  if ((local_10 == 0) || (uVar5 < *puVar9)) {
                    *puVar9 = uVar5;
                    *local_8 = (undefined1)local_10;
                  }
                  uVar5 = uVar5 + local_c;
                  iVar7 = iVar7 + 1;
                  puVar9 = puVar9 + 1;
                  local_8 = local_8 + 1;
                  local_c = local_c + iVar11 * 2;
                } while (iVar7 < iVar3);
              }
              local_34 = local_34 + local_3c;
              local_2c = local_2c + 1;
              local_3c = local_3c + iVar11 * 2;
            } while (local_2c < iVar3);
          }
          local_30 = local_30 + local_38;
          local_28 = local_28 + 1;
          local_38 = local_38 + iVar11 * 2;
        } while (local_28 < iVar3);
      }
      local_10 = local_10 + 1;
    } while (local_10 < param_1);
  }
  return;
}

