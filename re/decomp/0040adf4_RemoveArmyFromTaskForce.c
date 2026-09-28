// RemoveArmyFromTaskForce @ 0040adf4 size=198 sig=undefined RemoveArmyFromTaskForce() cc=unknown
// callers: RemoveArmyFromTaskForce,FUN_0040ef18,FUN_004526b0,FUN_00445ae4,FUN_0040f248,FUN_0040b074,FUN_0040cd0c,FUN_0040beb4,FUN_0040b968
// callees: RemoveArmyFromTaskForce,DebugMessage
// strings: \"Couldn't remove army from task force in RemoveArmyFromTaskForce\"

/* auto-named from string evidence: RemoveArmyFromTaskForce */

void RemoveArmyFromTaskForce(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  if (((DAT_0058f1fc == 0) || (DAT_0058f1f4 == DAT_004d5a58)) && (*(short *)(param_1 + 0x36) != 0))
  {
    iVar2 = *(char *)(param_1 + 8) * 0x2648 + *(short *)(param_1 + 0x36) * 0xc4;
    piVar3 = (int *)(&DAT_00522504 + iVar2);
    for (iVar1 = 0; (param_1 != *piVar3 && (iVar1 < 0x10)); iVar1 = iVar1 + 1) {
      piVar3 = piVar3 + 1;
    }
    if (iVar1 < 0x10) {
      *(undefined4 *)(&DAT_00522504 + iVar1 * 4 + iVar2) = 0;
      *(undefined2 *)(iVar2 + 0x5224e4 + iVar1 * 2) = 0;
      *(undefined2 *)(param_1 + 0x36) = 0;
      if (*(char *)(param_1 + 6) == '\f') {
        iVar1 = 0;
        piVar3 = (int *)(param_1 + 0x48);
        do {
          if (*piVar3 == 0) {
            if (*(int *)(param_1 + 0x48) != 0) {
              RemoveArmyFromTaskForce(*(int *)(param_1 + 0x48));
            }
          }
          else {
            RemoveArmyFromTaskForce(*piVar3);
          }
          iVar1 = iVar1 + 1;
          piVar3 = piVar3 + 1;
        } while (iVar1 < 3);
      }
    }
    else {
      DebugMessage(s_Couldn_t_remove_army_from_task_f_004b6c94);
    }
  }
  return;
}

