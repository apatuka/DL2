// FUN_0044bea8 @ 0044bea8 size=910 sig=undefined FUN_0044bea8() cc=unknown
// callers: FUN_00414004,FUN_0044bacc,FUN_0044c238,FUN_0044f3f0,FUN_0044c44c,FUN_00473e9c,FUN_0041d188,_DemolishBuilding,_MovePopulation,FUN_0046c780,FUN_0047d068,FUN_0047cb74,FUN_0044df94,FUN_0047cf9c,FUN_0047d49c,FUN_0044c9a0,FUN_004730a8,FUN_0044e0a8,FUN_0047d35c,FUN_0047c730,FUN_0047cdd8
// callees: FUN_004023dc,FUN_0044be88,FUN_0044c978,FUN_0044ba40,FUN_0046c3fc

void FUN_0044bea8(int param_1)

{
  char cVar1;
  int *piVar2;
  int *piVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int local_4c;
  int local_44;
  int *local_40;
  int *local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int *local_24;
  int *local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  if (*(short *)(param_1 + 0x30) == 0) {
    *(undefined1 *)(param_1 + 0x27) = 100;
  }
  FUN_0046c3fc(param_1,&local_c,local_10);
  local_8 = 0;
  piVar7 = (int *)(param_1 + 0x154);
  do {
    local_14 = *piVar7;
    if (local_14 != 0) {
      local_18 = FUN_0044be88(local_14);
      iVar6 = 0;
      piVar2 = (int *)(local_14 + 0x18);
      pcVar4 = (char *)(local_14 + 0x2c);
      do {
        cVar1 = *pcVar4;
        if (((cVar1 == '\x0f') || (cVar1 == '\a')) || (cVar1 == '\f')) {
          local_1c = *piVar2;
          piVar3 = (int *)(iVar6 * 4 + local_14 + 0x18);
          local_20 = piVar3;
          if (local_c < *piVar3) {
            piVar3 = &local_c;
          }
          *piVar2 = (int)(short)*piVar3;
          piVar3 = (int *)(iVar6 * 4 + local_14 + 0x18);
          local_24 = piVar3;
          if (local_18 < *piVar3) {
            piVar3 = &local_18;
          }
          *piVar2 = (int)(short)*piVar3;
          local_c = local_c - *piVar2;
          local_18 = local_18 - *piVar2;
          if (*piVar2 != local_1c) {
            *(ushort *)(local_14 + 2) = *(ushort *)(local_14 + 2) & ~(0x100 << ((byte)iVar6 & 0x1f))
            ;
          }
        }
        iVar6 = iVar6 + 1;
        piVar2 = piVar2 + 1;
        pcVar4 = pcVar4 + 1;
      } while (iVar6 < 5);
    }
    local_8 = local_8 + 1;
    piVar7 = piVar7 + 0xd;
  } while (local_8 < 0x24);
  local_8 = 0;
  piVar7 = (int *)(param_1 + 0x154);
  do {
    iVar6 = *piVar7;
    if ((iVar6 != 0) && (*(char *)(iVar6 + 5) != '\x11')) {
      local_28 = FUN_0044be88(iVar6);
      iVar8 = 0;
      do {
        iVar5 = (iVar8 + 1) % 5;
        cVar1 = *(char *)(iVar6 + 0x2c + iVar5);
        if (((cVar1 == '\x0f') || (cVar1 == '\a')) || (cVar1 == '\f')) {
          local_28 = local_28 - *(int *)(iVar6 + 0x18 + iVar5 * 4);
        }
        else {
          piVar2 = (int *)(iVar6 + 0x18 + iVar5 * 4);
          local_2c = *(int *)(iVar6 + 0x18 + iVar5 * 4);
          if (local_c < *piVar2) {
            piVar2 = &local_c;
          }
          *(int *)(iVar6 + 0x18 + iVar5 * 4) = (int)(short)*piVar2;
          piVar2 = (int *)(iVar6 + 0x18 + iVar5 * 4);
          if (local_28 < *piVar2) {
            piVar2 = &local_28;
          }
          *(int *)(iVar6 + 0x18 + iVar5 * 4) = (int)(short)*piVar2;
          local_c = local_c - *(int *)(iVar6 + 0x18 + iVar5 * 4);
          local_28 = local_28 - *(int *)(iVar6 + 0x18 + iVar5 * 4);
          if (*(int *)(iVar6 + 0x18 + iVar5 * 4) != local_2c) {
            *(ushort *)(iVar6 + 2) = *(ushort *)(iVar6 + 2) & ~(0x100 << ((byte)iVar5 & 0x1f));
          }
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < 5);
    }
    local_8 = local_8 + 1;
    piVar7 = piVar7 + 0xd;
  } while (local_8 < 0x24);
  local_8 = 0;
  piVar7 = (int *)(param_1 + 0x154);
  do {
    local_30 = *piVar7;
    if ((local_30 != 0) && (*(char *)(local_30 + 5) == '\x11')) {
      local_34 = FUN_0044ba40(local_30);
      iVar6 = 0;
      piVar2 = (int *)(local_30 + 0x18);
      pcVar4 = (char *)(local_30 + 0x2c);
      do {
        cVar1 = *pcVar4;
        if (((cVar1 == '\x0f') || (cVar1 == '\a')) || (cVar1 == '\f')) {
          local_34 = local_34 - *piVar2;
        }
        else {
          local_38 = *piVar2;
          piVar3 = (int *)(iVar6 * 4 + local_30 + 0x18);
          local_3c = piVar3;
          if (local_c < *piVar3) {
            piVar3 = &local_c;
          }
          *piVar2 = (int)(short)*piVar3;
          piVar3 = (int *)(iVar6 * 4 + local_30 + 0x18);
          local_40 = piVar3;
          if (local_34 < *piVar3) {
            piVar3 = &local_34;
          }
          *piVar2 = (int)(short)*piVar3;
          local_34 = local_34 - *piVar2;
          local_c = local_c - *piVar2;
          if (*piVar2 != local_38) {
            *(ushort *)(local_30 + 2) = *(ushort *)(local_30 + 2) & ~(0x100 << ((byte)iVar6 & 0x1f))
            ;
          }
        }
        iVar6 = iVar6 + 1;
        piVar2 = piVar2 + 1;
        pcVar4 = pcVar4 + 1;
      } while (iVar6 < 5);
    }
    local_8 = local_8 + 1;
    piVar7 = piVar7 + 0xd;
  } while (local_8 < 0x24);
  piVar7 = (int *)(param_1 + 0x154);
  for (local_8 = 0; (local_c != 0 && (local_8 < 0x24)); local_8 = local_8 + 1) {
    iVar6 = *piVar7;
    if ((iVar6 != 0) && (*(char *)(iVar6 + 5) == '\x11')) {
      local_44 = FUN_0044be88(iVar6);
      iVar8 = 0;
      piVar2 = (int *)(iVar6 + 0x18);
      do {
        iVar5 = *piVar2;
        piVar2 = piVar2 + 1;
        local_44 = local_44 - iVar5;
        iVar8 = iVar8 + 1;
      } while (iVar8 < 5);
      if (local_44 < local_c) {
        piVar2 = &local_44;
      }
      else {
        piVar2 = &local_c;
      }
      iVar8 = *piVar2;
      local_4c = FUN_004023dc(iVar6,0x14);
      if (local_4c == -1) {
        local_4c = FUN_0044c978(iVar6);
      }
      piVar2 = (int *)(iVar6 + 0x18 + local_4c * 4);
      *piVar2 = *piVar2 + iVar8;
      local_c = local_c - iVar8;
    }
    piVar7 = piVar7 + 0xd;
  }
  return;
}

