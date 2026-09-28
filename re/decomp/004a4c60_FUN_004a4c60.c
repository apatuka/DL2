// FUN_004a4c60 @ 004a4c60 size=50 sig=undefined FUN_004a4c60() cc=unknown
// callers: FUN_004a4c92,FUN_004a4ffe
// callees: FUN_004989cf

void FUN_004a4c60(int param_1)

{
  if (*(int *)(param_1 + 0x12) != 0) {
    FUN_004989cf(*(undefined4 *)(param_1 + 0x12));
    *(undefined4 *)(param_1 + 0x12) = 0;
  }
  if (*(int *)(param_1 + 0x16) != 0) {
    FUN_004989cf(*(undefined4 *)(param_1 + 0x16));
    *(undefined4 *)(param_1 + 0x16) = 0;
  }
  return;
}

