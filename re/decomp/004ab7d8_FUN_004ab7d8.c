// FUN_004ab7d8 @ 004ab7d8 size=38 sig=undefined FUN_004ab7d8() cc=unknown
// callers: FUN_004ab834
// callees: FUN_004ab7a8

void FUN_004ab7d8(undefined1 param_1,int param_2)

{
  if (0x4f < *(int *)(param_2 + 0x50)) {
    FUN_004ab7a8(param_2);
  }
  *(undefined1 *)(param_2 + *(int *)(param_2 + 0x50)) = param_1;
  *(int *)(param_2 + 0x50) = *(int *)(param_2 + 0x50) + 1;
  *(int *)(param_2 + 0x5c) = *(int *)(param_2 + 0x5c) + 1;
  return;
}

