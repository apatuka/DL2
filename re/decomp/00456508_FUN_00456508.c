// FUN_00456508 @ 00456508 size=269 sig=undefined FUN_00456508() cc=unknown
// callers: 
// callees: FUN_0045640c,FUN_00450fa8,FUN_00450dd0,FUN_00450da4,FUN_00446bf0

void FUN_00456508(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int local_5c [7];
  int aiStack_40 [7];
  int local_24 [7];
  int *local_8;
  
  piVar4 = &DAT_004d01f0;
  piVar5 = local_24;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar5 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  }
  iVar3 = 0;
  for (iVar2 = *(int *)(param_1 + 0x7a); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
    if (((local_24[*(char *)(iVar2 + 8)] == 0) && (iVar1 = FUN_00446bf0(iVar2), iVar1 == 0)) &&
       (iVar1 = FUN_00450fa8(iVar2), iVar1 == 0)) {
      iVar3 = iVar3 + 1;
      local_24[*(char *)(iVar2 + 8)] = 1;
    }
  }
  if (1 < iVar3) {
    piVar4 = &DAT_004d020c;
    piVar5 = local_5c;
    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar5 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar5 = piVar5 + 1;
    }
    iVar2 = 0;
    FUN_00450dd0(DAT_005649d0);
    local_8 = aiStack_40;
    for (iVar3 = 0; iVar3 < DAT_004d5aec; iVar3 = iVar3 + 1) {
      for (iVar1 = FUN_00450da4(DAT_004d5aec); local_5c[iVar1] != 0;
          iVar1 = (iVar1 + 1) % DAT_004d5aec) {
      }
      local_5c[iVar1] = 1;
      if (local_24[iVar1] != 0) {
        *local_8 = iVar1;
        iVar2 = iVar2 + 1;
        local_8 = local_8 + 1;
      }
    }
    piVar4 = aiStack_40 + iVar2;
    iVar3 = 0;
    if (iVar2 != 0) {
      do {
        iVar1 = iVar3 + 2;
        iVar3 = FUN_0045640c(param_1,aiStack_40[iVar3 + 1],aiStack_40[iVar3]);
        if (iVar2 != iVar1) {
          *piVar4 = iVar3;
          iVar2 = iVar2 + 1;
          piVar4 = piVar4 + 1;
        }
        iVar3 = iVar1;
      } while (iVar2 != iVar1);
    }
  }
  return;
}

