// FUN_004a2c32 @ 004a2c32 size=131 sig=undefined FUN_004a2c32() cc=unknown
// callers: FUN_004a2cb5
// callees: FUN_0049eb44,FUN_0049eafa

void FUN_004a2c32(int param_1,int param_2)

{
  int iVar1;
  
  if (*(int *)(param_2 + 0x1c) != 9) {
    if (((*(int *)(param_1 + 0x68) == *(int *)(param_1 + 0x7c)) &&
        (*(int *)(param_1 + 0x88) == *(int *)(param_1 + 0x84))) &&
       (iVar1 = FUN_0049eafa(param_2), iVar1 != 1)) {
      FUN_0049eb44(param_1,*(undefined4 *)(param_1 + 0x68),2,0x3d,0,*(undefined4 *)(param_1 + 0x88))
      ;
      return;
    }
    if (((*(int *)(param_1 + 0x68) != *(int *)(param_1 + 0x7c)) ||
        (*(int *)(param_1 + 0x88) != *(int *)(param_1 + 0x84))) &&
       (iVar1 = FUN_0049eafa(param_2), iVar1 == 1)) {
      FUN_0049eb44(param_1,*(undefined4 *)(param_1 + 0x68),2,0x3d,1,*(undefined4 *)(param_1 + 0x88))
      ;
    }
  }
  return;
}

