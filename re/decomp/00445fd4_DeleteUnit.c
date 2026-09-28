// DeleteUnit @ 00445fd4 size=176 sig=undefined DeleteUnit() cc=unknown
// callers: FUN_004471c0,FUN_004474b0,FUN_004526b0,FUN_00445f08,FUN_0046e39c,DeleteUnit,FUN_00485668,FUN_00445ae4,SpyCaught,FUN_00486b74,FUN_0046f26c
// callees: FUN_00445a74,FUN_00445ee0,DeleteUnit,DeleteArmy,DebugMessage
// strings: \"Deleted unit not in specified territory in DeleteUnit\"

/* auto-named from string evidence: DeleteUnit */

void DeleteUnit(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 6) != '\0') {
    iVar3 = *(int *)(param_1 + 0x3c);
    if ((*(char *)(param_1 + 7) == '\x13') || (*(char *)(param_1 + 7) == '\x04')) {
      iVar4 = 0;
      piVar1 = (int *)(param_1 + 0x48);
      do {
        if (*piVar1 != 0) {
          DeleteUnit(*piVar1);
        }
        iVar4 = iVar4 + 1;
        piVar1 = piVar1 + 1;
      } while (iVar4 < 3);
    }
    else if (*(int *)(param_1 + 0x48) != 0) {
      FUN_00445a74(param_1);
    }
    if ((*(char *)(param_1 + 6) == '$') && (*(int *)(param_1 + 0x48) != 0)) {
      *(undefined4 *)(*(int *)(param_1 + 0x48) + 0x48) = 0;
    }
    iVar2 = iVar3 + 0x76;
    iVar4 = FUN_00445ee0(param_1,iVar2);
    if (iVar4 == 0) {
      iVar3 = iVar3 + 0x7a;
      iVar4 = FUN_00445ee0(param_1,iVar3);
      if (iVar4 == 0) {
        DebugMessage(s_Deleted_unit_not_in_specified_te_004c5349);
      }
      else {
        DeleteArmy(param_1,iVar3);
      }
    }
    else {
      DeleteArmy(param_1,iVar2);
    }
  }
  return;
}

