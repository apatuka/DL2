// FUN_00475048 @ 00475048 size=123 sig=undefined FUN_00475048() cc=unknown
// callers: FUN_0047636c,FUN_004765e8,NetMakePact,FUN_00476e80,NetBuildingTasks,NetMoveUnit,NetBuildingFlags,NetReassignLabor,FUN_004766e8,NetBreakPact_6a70,NetBreakPact,NetReassignLaborByTask,NetDisbandUnit
// callees: DebugMessage,sprintf
// strings: \"%s\\nPlayer: %d Item: %d Data1: %d Data2: %d\"

void FUN_00475048(char *param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  char local_1f8 [500];
  
  if (param_2 == 0) {
    uVar2 = 0xffffffff;
    do {
      pcVar4 = param_1;
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      pcVar4 = param_1 + 1;
      cVar1 = *param_1;
      param_1 = pcVar4;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    pcVar4 = pcVar4 + -uVar2;
    pcVar5 = local_1f8;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *pcVar5 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    }
  }
  else {
    sprintf(local_1f8,s__s_Player___d_Item___d_Data1___d_004dbe17,param_1,
            (int)*(short *)(param_2 + 0x16),*(undefined2 *)(param_2 + 0x18),
            *(undefined2 *)(param_2 + 0x1a),*(undefined2 *)(param_2 + 0x1c));
  }
  DebugMessage(local_1f8);
  return;
}

