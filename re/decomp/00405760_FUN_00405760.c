// FUN_00405760 @ 00405760 size=56 sig=undefined FUN_00405760() cc=unknown
// callers: FUN_00405948,FUN_004098c4,FUN_00405aac,FUN_004057c4
// callees: FUN_004b0a30

undefined4 FUN_00405760(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x18) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x18) + 0x14) = *(undefined4 *)(param_1 + 0x14);
    }
    if (*(int *)(param_1 + 0x14) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0x14) + 0x18) = *(undefined4 *)(param_1 + 0x18);
    }
    FUN_004b0a30(param_1);
    uVar1 = 1;
  }
  return uVar1;
}

