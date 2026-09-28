// FUN_0047d068 @ 0047d068 size=375 sig=undefined FUN_0047d068() cc=unknown
// callers: SeaManipulationEffects,FUN_0047d288,FUN_0047d1e0
// callees: GetBuildingTasks,FUN_0044bea8,MoveLaborToHousingNoNet,FUN_0046c9d8,FUN_0044ba18,FUN_0044de9c
// strings: \"Earthquake2\"

int FUN_0047d068(int param_1,uint param_2)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  int local_50 [13];
  int *local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  local_10 = 0;
  local_1c = (int *)(param_1 + 0x154);
  local_14 = 0;
  do {
    iVar1 = *local_1c;
    if (iVar1 != 0) {
      FUN_0044de9c(&DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8,(int)*(char *)(iVar1 + 4),
                   (int)*(char *)(param_1 + 0x21),local_50);
      local_c = local_c + (local_50[0] - *(short *)(iVar1 + 0x14));
      while ((*(short *)(iVar1 + 0x14) < local_50[0] &&
             (uVar5 = FUN_0046c9d8(100,s_Earthquake2_004dcb14), uVar5 < param_2))) {
        local_18 = *(short *)(iVar1 + 0x14) + 0x32;
        if (local_50[0] < local_18) {
          piVar6 = local_50;
        }
        else {
          piVar6 = &local_18;
        }
        local_8 = local_8 + (*piVar6 - (int)*(short *)(iVar1 + 0x14));
        uVar2 = (undefined2)*piVar6;
        if (*(short *)(iVar1 + 0x14) == 0) {
          *(undefined2 *)(iVar1 + 0x14) = uVar2;
          iVar3 = FUN_0044ba18(iVar1);
joined_r0x0047d11d:
          if (4 < iVar3) {
            iVar4 = 4;
            piVar6 = (int *)(iVar1 + 0x28);
            do {
              if (*piVar6 != 0) {
                MoveLaborToHousingNoNet(param_1,iVar1,iVar4);
                iVar3 = iVar3 + -1;
                break;
              }
              iVar4 = iVar4 + -1;
              piVar6 = piVar6 + -1;
            } while (-1 < iVar4);
            goto joined_r0x0047d11d;
          }
          GetBuildingTasks(&DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8,iVar1);
        }
        else {
          *(undefined2 *)(iVar1 + 0x14) = uVar2;
        }
      }
    }
    local_14 = local_14 + 1;
    local_1c = local_1c + 0xd;
    if (0x23 < local_14) {
      if (local_c != 0) {
        local_10 = ((local_8 * 100) / local_c) / 0x14;
      }
      if (local_8 != 0) {
        local_10 = local_10 + 1;
      }
      FUN_0044bea8(param_1);
      return local_10;
    }
  } while( true );
}

