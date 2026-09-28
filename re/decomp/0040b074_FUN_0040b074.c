// FUN_0040b074 @ 0040b074 size=73 sig=undefined FUN_0040b074() cc=unknown
// callers: FUN_0040b0c0
// callees: RemoveArmyFromTaskForce

void FUN_0040b074(int param_1,undefined2 *param_2,int param_3)

{
  RemoveArmyFromTaskForce(param_2);
  param_2[0x1b] =
       (short)((param_1 - (int)(&DAT_00522584 + *(short *)(param_1 + 10) * 0x2648)) / 0xc4) + 1;
  *(undefined2 *)(param_1 + 0x24 + param_3 * 2) = *param_2;
  *(undefined2 **)(param_1 + 0x44 + param_3 * 4) = param_2;
  return;
}

