// FUN_004451d4 @ 004451d4 size=155 sig=undefined FUN_004451d4() cc=unknown
// callers: FUN_00445270
// callees: FUN_00445074

void FUN_004451d4(int param_1,int param_2)

{
  short *psVar1;
  
  FUN_00445074((int)*(short *)(param_1 + 0xe),(int)*(short *)(param_1 + 0x10),
               (int)*(short *)(param_1 + 0x12),(int)*(short *)(param_1 + 0x14));
  *(undefined2 *)(param_1 + 0x1e) = *(undefined2 *)(param_1 + 0x20);
  if ((*(int *)(*(int *)(param_1 + 0x1a) + 8 + param_2 * 0x10) == 0) ||
     ((*(short *)(*(int *)(param_1 + 0x1a) + 4 + param_2 * 0x10) == 0 &&
      (*(short *)(*(int *)(param_1 + 0x1a) + 6 + param_2 * 0x10) == 0)))) {
    *(undefined4 *)(param_1 + 0x16) = *(undefined4 *)(param_1 + 0x1a);
  }
  else {
    *(int *)(param_1 + 0x16) = param_2 * 0x10 + *(int *)(param_1 + 0x1a);
  }
  psVar1 = *(short **)(param_1 + 0x16);
  FUN_00445074((*(int *)(param_1 + 6) >> 8) + (int)*psVar1,
               (*(int *)(param_1 + 10) >> 8) + (int)psVar1[1],(int)psVar1[2],(int)psVar1[3]);
  return;
}

