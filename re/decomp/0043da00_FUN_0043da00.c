// FUN_0043da00 @ 0043da00 size=66 sig=undefined FUN_0043da00() cc=unknown
// callers: FUN_00453c30
// callees: FUN_00482de8,FUN_0043d004,FUN_0046ca40

void FUN_0043da00(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 0x38) != 0)) && (*(char *)(param_1 + 0x1d) != '\0')) {
    uVar1 = FUN_0043d004((int)*(short *)(*(int *)(param_1 + 0x38) + 0xe));
    uVar2 = FUN_0046ca40(param_1,uVar1);
    FUN_00482de8(uVar2 % 3 + 0x6b,param_1,uVar1);
  }
  return;
}

