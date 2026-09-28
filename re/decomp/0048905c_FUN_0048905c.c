// FUN_0048905c @ 0048905c size=40 sig=undefined FUN_0048905c() cc=unknown
// callers: FUN_00438b9c,FUN_004397a0
// callees: FindClose

void FUN_0048905c(int param_1)

{
  if (*(int *)(param_1 + 0x244) != 0) {
    FindClose(*(HANDLE *)(param_1 + 0x244));
  }
  *(undefined4 *)(param_1 + 0x244) = 0;
  return;
}

