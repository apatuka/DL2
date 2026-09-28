// FUN_004467e8 @ 004467e8 size=798 sig=undefined FUN_004467e8() cc=unknown
// callers: FUN_00401a18,FUN_00401ac0,FUN_00401320
// callees: FUN_004412d4,FUN_00445b94,FUN_00416c28,FUN_0045dfb0

int FUN_004467e8(undefined *param_1,undefined *param_2,int param_3,int param_4,int param_5,
                int param_6,undefined4 *param_7)

{
  short sVar1;
  bool bVar2;
  bool bVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  ushort uVar8;
  int iVar9;
  undefined *puVar10;
  int iVar11;
  byte bVar12;
  undefined4 *local_38;
  ushort *local_2c;
  int local_24;
  undefined *local_18;
  int local_14;
  int local_c;
  
  local_14 = 0;
  bVar2 = false;
  bVar3 = false;
  bVar7 = (byte)param_3;
  FUN_0045dfb0(0x2000 << (bVar7 & 0x1f));
  puVar10 = param_1;
  if ((param_5 == 0) && (*(short *)(param_1 + param_3 * 2 + 0xa70) <= param_4)) {
    bVar2 = true;
  }
  do {
    *(uint *)(puVar10 + 0x1c) = *(uint *)(puVar10 + 0x1c) | 0x2000 << (bVar7 & 0x1f);
    sVar1 = *(short *)(puVar10 + param_3 * 2 + 0xa70);
    bVar4 = 0;
    local_18 = (undefined *)0x0;
    local_24 = 0;
    local_2c = (ushort *)(puVar10 + 0x890);
    local_c = (int)sVar1;
    do {
      uVar8 = *local_2c;
      local_38 = param_7 + local_14;
      for (iVar11 = 0; (uVar8 != 0 && (iVar11 < 0x10)); iVar11 = iVar11 + 1) {
        if (((uVar8 & 1) != 0) && (iVar5 = local_24 * 0x10 + iVar11, iVar5 <= DAT_004d5b18)) {
          iVar9 = iVar5 * 0xadc;
          puVar10 = &DAT_005a43d0 + iVar9;
          if ((puVar10 == param_2) && (bVar2)) {
            bVar3 = true;
          }
          if ((((puVar10 != param_2) && (puVar10 != param_1)) &&
              ((0x2000 << (bVar7 & 0x1f) & (&DAT_005a43ec)[iVar5 * 0x2b7]) == 0)) &&
             (((*(byte *)((int)&DAT_005a43ec + iVar9 + 1) & 1) == 0 &&
              ((int)*(short *)(&DAT_005a4e40 + param_3 * 2 + iVar9) < (int)sVar1)))) {
            bVar12 = *(short *)(&DAT_005a4e40 + param_3 * 2 + iVar9) == local_c;
            if (*(short *)(&DAT_005a4e40 + param_3 * 2 + iVar9) < local_c) {
              bVar12 = bVar12 | 2;
            }
            iVar6 = FUN_00445b94(puVar10,param_6);
            if (iVar6 != 0) {
              bVar12 = bVar12 | 4;
            }
            if (((&DAT_005a43f0)[iVar9] == -1) &&
               (((char)(&DAT_0059f161)[param_3 * 0x2d8] < '\x03' ||
                ((&DAT_005a4e28)[iVar5 * 0x2b7] == 0)))) {
              bVar12 = bVar12 | 8;
            }
            if (((char)(&DAT_005a43f0)[iVar9] == param_3) ||
               (iVar5 = FUN_004412d4(param_3,(int)(char)(&DAT_005a43f0)[iVar9],2), iVar5 != 0)) {
              bVar12 = bVar12 | 0x10;
            }
            if ((((&DAT_004faf8d)[param_6 * 0x24] != '\x03') &&
                (iVar5 = FUN_00416c28(param_3,param_6), iVar5 == 0)) && (bVar12 < 8)) {
              bVar12 = 0;
            }
            if ((bVar4 < bVar12) &&
               (local_c = (int)*(short *)(&DAT_005a4e40 + param_3 * 2 + iVar9), local_18 = puVar10,
               bVar4 = bVar12, param_7 != (undefined4 *)0x0)) {
              *local_38 = puVar10;
              local_14 = local_14 + 1;
              local_38 = local_38 + 1;
            }
          }
        }
        uVar8 = (short)uVar8 >> 1;
      }
      local_24 = local_24 + 1;
      local_2c = local_2c + 1;
    } while (local_24 < 7);
  } while ((((local_18 != param_2) && (local_18 != (undefined *)0x0)) &&
           ((param_4 < local_c || (iVar11 = FUN_00445b94(local_18,param_6), iVar11 == 0)))) &&
          (puVar10 = local_18, !bVar2));
  if (bVar2) {
    if (param_7 != (undefined4 *)0x0) {
      *param_7 = param_1;
      if (bVar3) {
        param_7[1] = param_2;
        param_7[2] = 0;
      }
      else {
        param_7[1] = local_18;
        param_7[2] = 0;
      }
    }
    iVar11 = (int)*(short *)(param_1 + 0x1a);
  }
  else if (local_18 == (undefined *)0x0) {
    if (param_7 != (undefined4 *)0x0) {
      *param_7 = 0;
    }
    iVar11 = -1;
  }
  else {
    if (param_7 != (undefined4 *)0x0) {
      param_7[local_14] = 0;
    }
    iVar11 = (int)*(short *)(local_18 + 0x1a);
  }
  return iVar11;
}

