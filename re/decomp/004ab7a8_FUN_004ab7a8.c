// FUN_004ab7a8 @ 004ab7a8 size=45 sig=undefined FUN_004ab7a8() cc=unknown
// callers: FUN_004ab834,FUN_004ab7d8
// callees: 

void FUN_004ab7a8(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x50) != 0) {
    iVar1 = (**(code **)(param_1 + 0x54))
                      (param_1,*(int *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x58));
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0x60) = 1;
    }
    *(undefined4 *)(param_1 + 0x50) = 0;
  }
  return;
}

