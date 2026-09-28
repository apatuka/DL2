// FUN_00419924 @ 00419924 size=240 sig=undefined FUN_00419924() cc=unknown
// callers: CheckArmy
// callees: GetKeyState,FUN_0046e6b8,FUN_00418cf4,FUN_004196e4,FUN_00449dec,FUN_004173d4,FUN_00419678,FUN_00418d18,FUN_0042836c,FUN_00419684,FUN_00475854
// strings: \"Are you sure you want to disband your unit selection?\"|\"Disband Unit\"

void FUN_00419924(void)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int local_14;
  
  uVar2 = GetKeyState(0x12);
  if (((DAT_004d59b4 == 0x22) && (iVar3 = FUN_004173d4(), iVar3 != 0)) &&
     (iVar3 = FUN_0042836c(PTR_s_Disband_Unit_00509688,
                           PTR_s_Are_you_sure_you_want_to_disband_0050968c,6,0,0xd), iVar3 == 1)) {
    if (DAT_005332b0 != '\0') {
      FUN_004196e4();
    }
    piVar4 = &DAT_005332d8;
    local_14 = 0;
    do {
      iVar3 = 0;
      piVar5 = piVar4;
      do {
        if ((((uVar2 & 0x8000) != 0) || (*piVar5 == 1)) &&
           ((iVar1 = piVar5[1], iVar1 != 0 && (*(char *)(iVar1 + 8) == DAT_0058f1f4)))) {
          FUN_00475854(iVar1);
        }
        iVar3 = iVar3 + 1;
        piVar5 = piVar5 + 8;
      } while (iVar3 < 10);
      local_14 = local_14 + 1;
      piVar4 = (int *)((int)piVar4 + 0x146);
    } while (local_14 < 100);
    FUN_00419678();
    FUN_00419684();
    if (DAT_004d5aa0 != '\0') {
      FUN_0046e6b8(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
    }
    FUN_00449dec();
    FUN_00418d18();
    FUN_00418cf4();
  }
  return;
}

