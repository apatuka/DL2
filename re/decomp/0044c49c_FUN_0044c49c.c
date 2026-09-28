// FUN_0044c49c @ 0044c49c size=437 sig=undefined FUN_0044c49c() cc=unknown
// callers: GetBuildingTasks,FUN_0044f3f0
// callees: MoveLaborToHousingNoNet,FUN_00484e88,FUN_0044b620

void FUN_0044c49c(int param_1,int param_2)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  char *pcVar7;
  int *local_28;
  int *local_24;
  int local_20;
  short local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  if (param_1 != 0) {
    bVar2 = true;
    iVar3 = FUN_0044b620(param_1);
    if (*(short *)(param_1 + 0x14) == 0) {
      local_10 = 0;
      local_24 = (int *)(param_1 + 0x18);
      local_14 = -1;
      local_18 = 0;
      iVar6 = 0;
      pcVar7 = (char *)(param_1 + 0x2c);
      do {
        if (*pcVar7 != '\0') {
          if ((((0x100 << ((byte)iVar6 & 0x1f) & (int)*(short *)(param_1 + 2)) == 0) &&
              (*pcVar7 != '\x15')) &&
             ((iVar6 < 4 || ((iVar3 != 0 && (iVar4 = FUN_00484e88(iVar3), iVar4 != 0)))))) {
            bVar2 = false;
            if (local_14 == -1) {
              local_14 = iVar6;
            }
            local_10 = local_10 + 1;
          }
          else {
            local_18 = local_18 + *local_24;
          }
        }
        local_24 = local_24 + 1;
        iVar6 = iVar6 + 1;
        pcVar7 = pcVar7 + 1;
      } while (iVar6 < 5);
      param_2 = param_2 - local_18;
      if (local_10 == 0) {
        if (0 < param_2) {
          do {
            if (param_2 == 0) {
              return;
            }
            param_2 = param_2 + -1;
            *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
            iVar3 = MoveLaborToHousingNoNet
                              (&DAT_005a43d0 + *(short *)(param_1 + 8) * 0xadc,param_1,0);
          } while (iVar3 != 0);
        }
      }
      else {
        if (bVar2) {
          local_10 = local_10 + 1;
        }
        local_28 = (int *)(param_1 + 0x18);
        local_20 = 0;
        iVar6 = 0;
        pcVar7 = (char *)(param_1 + 0x2c);
        do {
          if ((((*pcVar7 != '\0') &&
               ((0x100 << ((byte)iVar6 & 0x1f) & (int)*(short *)(param_1 + 2)) == 0)) &&
              ((*pcVar7 != '\x15' || (bVar2)))) &&
             ((iVar6 < 4 || ((iVar3 != 0 && (iVar4 = FUN_00484e88(iVar3), iVar4 != 0)))))) {
            local_1c = (short)(param_2 / local_10);
            *local_28 = (int)local_1c;
            local_20 = local_20 + param_2 / local_10;
          }
          local_28 = local_28 + 1;
          iVar6 = iVar6 + 1;
          pcVar7 = pcVar7 + 1;
        } while (iVar6 < 5);
        piVar1 = (int *)(param_1 + 0x18 + local_14 * 4);
        *piVar1 = *piVar1 + (int)(char)((char)param_2 - (char)local_20);
      }
    }
    else {
      iVar3 = 0;
      puVar5 = (undefined4 *)(param_1 + 0x18);
      do {
        *puVar5 = 0;
        *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) & ~(0x100 << ((byte)iVar3 & 0x1f));
        iVar3 = iVar3 + 1;
        puVar5 = puVar5 + 1;
      } while (iVar3 < 5);
      *(int *)(param_1 + 0x18) = param_2;
    }
  }
  return;
}

