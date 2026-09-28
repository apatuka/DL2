// FUN_00491200 @ 00491200 size=1103 sig=undefined FUN_00491200() cc=unknown
// callers: FUN_00491200,FUN_004917e6
// callees: FUN_0048fade,FUN_004911cc,GlobalUnlock,FUN_0048f992,FUN_0048d5c4,FUN_00491200,GlobalLock,FUN_004989cf,FUN_0048d03e,FUN_0048fa92

void FUN_00491200(undefined4 *param_1,int param_2,undefined4 *param_3)

{
  ushort uVar1;
  ushort *puVar2;
  LPVOID pvVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  byte bVar8;
  byte *pbVar9;
  byte *pbVar10;
  ushort *puVar11;
  int iVar12;
  int local_40 [4];
  ushort local_2e;
  short *local_2c;
  byte *local_28;
  byte local_21;
  short *local_20;
  short *local_1c;
  undefined4 local_18;
  uint local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  uVar1 = *(ushort *)(param_3 + 1);
  if (uVar1 < 0xe) {
    if (uVar1 == 0xd) {
      for (local_c = 0; local_c < *(short *)((int)param_1 + 0x12); local_c = local_c + 1) {
        puVar6 = (undefined1 *)FUN_0048d03e(param_2,0,local_c);
        for (iVar12 = 0; iVar12 < *(short *)(param_1 + 4); iVar12 = iVar12 + 1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
      }
    }
    else {
      if (uVar1 != 4) {
        if (uVar1 == 7) {
          local_2c = (short *)FUN_004911cc(*param_1,*param_3);
          puVar11 = (ushort *)(local_2c + 1);
          local_c = 0;
          for (local_10 = (int)*local_2c; local_10 != 0; local_10 = local_10 + -1) {
            local_14 = (uint)(short)*puVar11;
            if ((local_14 & 0x8000) != 0) {
              if ((*puVar11 & 0x4000) == 0) {
                puVar6 = (undefined1 *)FUN_0048d03e(param_2,0,local_c);
                *puVar6 = (undefined1)local_14;
              }
              else {
                local_c = local_c + ~local_14 + 1;
              }
              puVar11 = puVar11 + 1;
              local_14 = (uint)(short)*puVar11;
            }
            iVar12 = 0;
            puVar11 = puVar11 + 1;
            for (; local_14 != 0; local_14 = local_14 - 1) {
              iVar12 = iVar12 + (uint)(byte)*puVar11;
              iVar4 = FUN_0048d03e(param_2,0,local_c);
              if ((char)*(byte *)((int)puVar11 + 1) < '\0') {
                local_2e = puVar11[1];
                for (iVar5 = ~(int)(char)*(byte *)((int)puVar11 + 1) + 1; iVar5 != 0;
                    iVar5 = iVar5 + -1) {
                  *(undefined1 *)(iVar4 + iVar12) = (undefined1)local_2e;
                  *(char *)(iVar4 + iVar12 + 1) = (char)(local_2e >> 8);
                  iVar12 = iVar12 + 2;
                }
                puVar11 = puVar11 + 2;
              }
              else {
                puVar2 = puVar11;
                for (iVar5 = (int)(char)*(byte *)((int)puVar11 + 1); puVar11 = puVar2 + 1,
                    iVar5 != 0; iVar5 = iVar5 + -1) {
                  *(byte *)(iVar4 + iVar12) = (byte)*puVar11;
                  *(byte *)(iVar4 + iVar12 + 1) = *(byte *)((int)puVar2 + 3);
                  iVar12 = iVar12 + 2;
                  puVar2 = puVar11;
                }
              }
            }
            local_c = local_c + 1;
            local_14 = 0;
          }
          FUN_004989cf(local_2c);
          return;
        }
        if (uVar1 != 0xb) {
          if (uVar1 != 0xc) {
            return;
          }
          local_20 = (short *)FUN_004911cc(*param_1,*param_3);
          local_c = (int)*local_20;
          pbVar10 = (byte *)(local_20 + 2);
          pbVar9 = (byte *)((int)local_20 + 5);
          for (local_10 = (int)local_20[1]; local_10 != 0; local_10 = local_10 + -1) {
            iVar12 = 0;
            local_14 = (uint)*pbVar10;
            pbVar10 = pbVar9;
            for (; local_14 != 0; local_14 = local_14 - 1) {
              iVar12 = iVar12 + (uint)*pbVar10;
              iVar4 = FUN_0048d03e(param_2,0,local_c);
              if ((char)pbVar10[1] < '\0') {
                local_21 = pbVar10[2];
                for (iVar5 = ~(int)(char)pbVar10[1] + 1; iVar5 != 0; iVar5 = iVar5 + -1) {
                  *(byte *)(iVar4 + iVar12) = local_21;
                  iVar12 = iVar12 + 1;
                }
                pbVar10 = pbVar10 + 3;
              }
              else {
                pbVar9 = pbVar10 + 1;
                pbVar10 = pbVar10 + 2;
                for (iVar5 = (int)(char)*pbVar9; iVar5 != 0; iVar5 = iVar5 + -1) {
                  *(byte *)(iVar4 + iVar12) = *pbVar10;
                  pbVar10 = pbVar10 + 1;
                  iVar12 = iVar12 + 1;
                }
              }
            }
            local_c = local_c + 1;
            pbVar9 = pbVar10 + 1;
            local_14 = 0;
          }
          FUN_004989cf(local_20);
          return;
        }
      }
      local_1c = (short *)FUN_004911cc(*param_1,*param_3);
      iVar12 = 0;
      local_c = 0;
      pbVar9 = (byte *)(local_1c + 1);
      local_18 = 2;
      if (*(short *)(param_3 + 1) != 0xb) {
        local_18 = 0;
      }
      for (; local_c < *local_1c; local_c = local_c + 1) {
        iVar12 = iVar12 + (uint)*pbVar9;
        local_8 = (uint)pbVar9[1];
        if (local_8 == 0) {
          local_8 = 0x100;
        }
        pvVar3 = GlobalLock(*(HGLOBAL *)(param_2 + 0x3c));
        iVar4 = iVar12;
        pbVar9 = pbVar9 + 2;
        for (; local_8 != 0; local_8 = local_8 - 1) {
          bVar8 = (byte)local_18;
          *(byte *)((int)pvVar3 + iVar4 * 4 + 8) = *pbVar9 << (bVar8 & 0x1f);
          *(byte *)((int)pvVar3 + iVar4 * 4 + 9) = pbVar9[1] << (bVar8 & 0x1f);
          *(byte *)((int)pvVar3 + iVar4 * 4 + 10) = pbVar9[2] << (bVar8 & 0x1f);
          pbVar9 = pbVar9 + 3;
          iVar4 = iVar4 + 1;
        }
        GlobalUnlock(*(HGLOBAL *)(param_2 + 0x3c));
      }
      FUN_0048d5c4(param_2);
      FUN_004989cf(local_1c);
    }
  }
  else if (uVar1 == 0xf) {
    pbVar9 = (byte *)FUN_004911cc(*param_1,*param_3);
    local_28 = pbVar9;
    for (local_c = 0; local_c < *(short *)((int)param_1 + 0x12); local_c = local_c + 1) {
      local_8 = 0;
      pbVar10 = (byte *)FUN_0048d03e(param_2,0,local_c);
      pbVar9 = pbVar9 + 1;
      while ((int)local_8 < (int)*(short *)(param_1 + 4)) {
        if ((char)*pbVar9 < '\0') {
          for (iVar12 = ~(int)(char)*pbVar9 + 1; pbVar9 = pbVar9 + 1, iVar12 != 0;
              iVar12 = iVar12 + -1) {
            *pbVar10 = *pbVar9;
            pbVar10 = pbVar10 + 1;
            local_8 = local_8 + 1;
          }
        }
        else {
          local_21 = pbVar9[1];
          for (iVar12 = (int)(char)*pbVar9; iVar12 != 0; iVar12 = iVar12 + -1) {
            *pbVar10 = local_21;
            pbVar10 = pbVar10 + 1;
            local_8 = local_8 + 1;
          }
          pbVar9 = pbVar9 + 2;
        }
      }
    }
    FUN_004989cf(local_28);
  }
  else if (uVar1 == 0x10) {
    puVar6 = (undefined1 *)FUN_004911cc(*param_1,*param_3);
    local_28 = puVar6;
    for (local_c = 0; local_c < *(short *)((int)param_1 + 0x12); local_c = local_c + 1) {
      local_8 = 0;
      puVar7 = (undefined1 *)FUN_0048d03e(param_2,0,local_c);
      for (; (int)local_8 < (int)*(short *)(param_1 + 4); local_8 = local_8 + 1) {
        *puVar7 = *puVar6;
        puVar7 = puVar7 + 1;
        puVar6 = puVar6 + 1;
      }
    }
    FUN_004989cf(local_28);
  }
  else if ((uVar1 != 0xf100) && (uVar1 == 0xf1fa)) {
    for (iVar12 = (int)*(short *)((int)param_3 + 6); iVar12 != 0; iVar12 = iVar12 + -1) {
      FUN_0048f992(*param_1,local_40,6);
      iVar4 = FUN_0048fa92(*param_1);
      FUN_00491200(param_1,param_2,local_40);
      FUN_0048fade(*param_1,local_40[0] + -6 + iVar4,0);
    }
    param_1[1] = param_1[1] + 1;
  }
  return;
}

