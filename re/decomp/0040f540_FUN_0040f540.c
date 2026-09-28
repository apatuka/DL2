// FUN_0040f540 @ 0040f540 size=66 sig=undefined FUN_0040f540() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_0040f2e0,FUN_0040beb4,FUN_0040c68c

void FUN_0040f540(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0040c68c((int)*(short *)(param_1 + 10),3,*(undefined4 *)(param_1 + 0x10));
  if ((iVar1 == 0) &&
     (iVar1 = FUN_0040c68c((int)*(short *)(param_1 + 10),0xb,*(undefined4 *)(param_1 + 0x10)),
     iVar1 == 0)) {
    FUN_0040f2e0(param_1);
    return;
  }
  FUN_0040beb4(param_1);
  return;
}

