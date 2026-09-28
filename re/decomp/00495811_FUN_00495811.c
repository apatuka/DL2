// FUN_00495811 @ 00495811 size=73 sig=undefined FUN_00495811() cc=unknown
// callers: FUN_00489538,FUN_00495a4a
// callees: FUN_0049116d,FUN_00491bd5,FUN_004989cf

void FUN_00495811(int param_1)

{
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x34) != 0) {
      FUN_004989cf(*(undefined4 *)(param_1 + 0x34));
    }
    *(undefined4 *)(param_1 + 0x34) = 0;
    if (*(int *)(param_1 + 0x3c) != 0) {
      FUN_0049116d(*(undefined4 *)(param_1 + 0x3c));
    }
    if (*(int *)(param_1 + 0x20) != 0) {
      FUN_00491bd5(*(undefined4 *)(param_1 + 0x20));
    }
    *(undefined4 *)(param_1 + 0x20) = 0;
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  return;
}

