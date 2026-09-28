// FUN_004a3e49 @ 004a3e49 size=87 sig=undefined FUN_004a3e49() cc=unknown
// callers: FUN_004a43da,FUN_004a196e,FUN_004a3ea0
// callees: FUN_00490796

undefined4 FUN_004a3e49(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 0x24) & 0x1f;
  if (uVar1 == 2) {
    if (*(int *)(param_2 + 0x38) != 0) {
      FUN_00490796(*(undefined4 *)(param_2 + 0x38),1);
      *(undefined4 *)(param_2 + 0x38) = 0;
    }
  }
  else if ((uVar1 == 4) && (*(int *)(param_2 + 0x38) != 0)) {
    FUN_00490796(*(undefined4 *)(param_2 + 0x38),1);
    *(undefined4 *)(param_2 + 0x38) = 0;
  }
  *(undefined4 *)(param_2 + 0x11c) = 0;
  return 1;
}

