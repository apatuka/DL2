// FUN_004a2376 @ 004a2376 size=153 sig=undefined FUN_004a2376() cc=unknown
// callers: FUN_004a2cb5
// callees: FUN_0049eb44

undefined4 FUN_004a2376(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if ((*(byte *)(param_2 + 0x28) & 4) == 0) {
    uVar1 = *(int *)(param_2 + 0x1c) - 1;
    if (uVar1 < 2) {
      FUN_0049eb44(param_1,param_2,2,0xb,(*(uint *)(param_2 + 0x28) & 1) == 0,0);
      if ((*(byte *)(param_2 + 0x28) & 2) != 0) {
        return 1;
      }
    }
    else if (uVar1 == 3) {
      if (*(int *)(param_2 + 0x90) != 0) {
        *(int *)(param_2 + 0x20) = *(int *)(param_2 + 0x90) + -1;
      }
      if ((*(uint *)(param_2 + 0x24) & 0x1f) == 1) {
        if (*(int *)(param_2 + 0x90) != 0) {
          return 1;
        }
      }
      else if ((*(byte *)(param_2 + 0x28) & 2) != 0) {
        return 1;
      }
    }
    else if ((*(byte *)(param_2 + 0x28) & 2) != 0) {
      return 1;
    }
  }
  return 0;
}

