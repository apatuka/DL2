// FUN_0042b520 @ 0042b520 size=646 sig=undefined FUN_0042b520() cc=unknown
// callers: 
// callees: FUN_0042baa4,FUN_0042b498,FUN_0042b3d0,FUN_0042b428,FUN_0049eb44

void FUN_0042b520(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 local_3c;
  int local_38;
  int local_28 [6];
  uint local_10;
  uint local_c;
  int local_8;
  
  piVar3 = local_28;
  local_8 = 0;
  iVar4 = 0;
  do {
    iVar1 = FUN_0042b3d0(iVar4);
    if (iVar1 != param_1) {
      iVar2 = FUN_0042b498(iVar1);
      if (iVar2 == 0) {
        *piVar3 = iVar1;
        local_8 = local_8 + 1;
        piVar3 = piVar3 + 1;
      }
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 6);
  if (local_8 == 0) {
    iVar4 = FUN_0042b428(param_1);
    local_38 = (&DAT_00557bf8)[iVar4];
    local_3c = 1;
    FUN_0049eb44(DAT_004bda5c,param_1,1,0x29,0,&local_3c);
  }
  FUN_0049eb44(DAT_004bda5c,param_1,1,0x28,0,&local_3c);
  iVar4 = FUN_0042b428(param_1);
  local_c = local_38 - (&DAT_00557bf8)[iVar4];
  iVar4 = FUN_0042b428(param_1);
  (&DAT_00557bf8)[iVar4] = local_38;
  if (local_c != 0) {
    local_10 = local_c;
    iVar4 = 0;
    piVar3 = local_28;
    if (0 < local_8) {
      do {
        iVar1 = (int)((local_c ^ (int)local_c >> 0x1f) - ((int)local_c >> 0x1f)) / local_8;
        if ((int)local_c < 0) {
          iVar1 = -iVar1;
        }
        iVar2 = FUN_0042b428(*piVar3);
        iVar1 = (&DAT_00557bf8)[iVar2] - iVar1;
        if (iVar1 < 0) {
          iVar1 = 0;
        }
        if (100 < iVar1) {
          iVar1 = 100;
        }
        if ((0x4b < iVar1) && (*piVar3 == 0x29)) {
          iVar1 = 0x4b;
        }
        iVar2 = FUN_0042b428(*piVar3);
        local_10 = local_10 - ((&DAT_00557bf8)[iVar2] - iVar1);
        iVar2 = FUN_0042b428(*piVar3);
        (&DAT_00557bf8)[iVar2] = iVar1;
        iVar4 = iVar4 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar4 < local_8);
    }
    if (local_10 != 0) {
      iVar4 = 0;
      piVar3 = local_28;
      if (0 < local_8) {
        do {
          iVar1 = FUN_0042b428(*piVar3);
          if ((&DAT_00557bf8)[iVar1] != 0) {
            iVar1 = FUN_0042b428(*piVar3);
            iVar1 = (&DAT_00557bf8)[iVar1] - local_10;
            if (iVar1 < 0) {
              iVar1 = 0;
            }
            if (100 < iVar1) {
              iVar1 = 100;
            }
            if ((0x4b < iVar1) && (*piVar3 == 0x29)) {
              iVar1 = 0x4b;
            }
            iVar2 = FUN_0042b428(*piVar3);
            local_10 = local_10 - ((&DAT_00557bf8)[iVar2] - iVar1);
            iVar2 = FUN_0042b428(*piVar3);
            (&DAT_00557bf8)[iVar2] = iVar1;
          }
          iVar4 = iVar4 + 1;
          piVar3 = piVar3 + 1;
        } while (iVar4 < local_8);
      }
      if (local_10 != 0) {
        iVar4 = FUN_0042b428(param_1);
        (&DAT_00557bf8)[iVar4] = (&DAT_00557bf8)[iVar4] - local_10;
      }
    }
    iVar4 = 0;
    piVar3 = local_28;
    if (0 < local_8) {
      do {
        iVar1 = FUN_0042b428(*piVar3);
        local_38 = (&DAT_00557bf8)[iVar1];
        local_3c = 1;
        FUN_0049eb44(DAT_004bda5c,*piVar3,1,0x29,0,&local_3c);
        iVar4 = iVar4 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar4 < local_8);
    }
    iVar4 = FUN_0042b428(param_1);
    local_38 = (&DAT_00557bf8)[iVar4];
    local_3c = 1;
    FUN_0049eb44(DAT_004bda5c,param_1,1,0x29,0,&local_3c);
    FUN_0042baa4();
  }
  return;
}

