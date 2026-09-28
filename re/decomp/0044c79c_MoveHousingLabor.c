// MoveHousingLabor @ 0044c79c size=271 sig=undefined MoveHousingLabor() cc=unknown
// callers: FUN_0044c9a0
// callees: FUN_0044ba40,FUN_004484fc,FUN_004023dc,DebugMessage,FUN_0044ba18
// strings: \"Invalid arguments to MoveHousingLabor()\"

/* auto-named from string evidence: MoveHousingLabor */

undefined4 MoveHousingLabor(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int local_8;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    DebugMessage(s_Invalid_arguments_to_MoveHousing_004c608d);
    return 0;
  }
  if (*(char *)(param_2 + 5) == '\x11') {
    iVar2 = FUN_0044ba18(param_2);
    iVar3 = FUN_0044ba40(param_2);
    if (iVar2 == iVar3) {
      iVar2 = FUN_004023dc(param_2,0x14);
      if (((iVar2 != -1) && (param_3 != -1)) && (*(int *)(param_2 + 0x18 + iVar2 * 4) != 0)) {
        piVar4 = (int *)(param_2 + 0x18 + param_3 * 4);
        *piVar4 = *piVar4 + 1;
        piVar4 = (int *)(param_2 + 0x18 + iVar2 * 4);
        *piVar4 = *piVar4 + -1;
        return 1;
      }
      return 0;
    }
  }
  if ((param_1 != 0) && (param_2 != 0)) {
    iVar2 = FUN_0044ba18(param_2);
    iVar3 = FUN_0044ba40(param_2);
    if ((iVar2 < iVar3) &&
       (((iVar2 = (int)*(char *)(param_2 + 0x2c + param_3), iVar2 != 2 && (iVar2 != 0x15)) ||
        (iVar2 = FUN_004484fc(iVar2,param_1,param_2), 0 < iVar2)))) {
      piVar1 = (int *)(param_2 + 0x18 + param_3 * 4);
      local_8 = 0;
      piVar4 = (int *)(param_1 + 0x154);
      do {
        iVar2 = *piVar4;
        if ((((iVar2 != 0) && (iVar3 = FUN_004023dc(iVar2,0x14), iVar3 != -1)) && (param_3 != -1))
           && (*(int *)(iVar2 + 0x18 + iVar3 * 4) != 0)) {
          *piVar1 = *piVar1 + 1;
          piVar4 = (int *)(iVar2 + 0x18 + iVar3 * 4);
          *piVar4 = *piVar4 + -1;
          return 1;
        }
        local_8 = local_8 + 1;
        piVar4 = piVar4 + 0xd;
      } while (local_8 < 0x24);
    }
  }
  return 0;
}

