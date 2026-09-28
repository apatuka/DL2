// FUN_0049ddf8 @ 0049ddf8 size=128 sig=undefined FUN_0049ddf8() cc=unknown
// callers: FUN_0049e007,FUN_0049e3d7,FUN_0049e47a,FUN_0049df38
// callees: FUN_00498ba9,FUN_0048f774,FUN_0049f09b

undefined4 FUN_0049ddf8(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  if (param_1 == 0) {
    uVar2 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x94) == 0) {
      iVar1 = FUN_00498ba9(0x20);
      if (iVar1 != 0) {
        FUN_0048f774(iVar1,0x20,0);
        *(int *)(param_1 + 0x94) = iVar1;
      }
    }
    if (*(int *)(param_1 + 0x94) != 0) {
      **(undefined4 **)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0x34);
      FUN_0049f09b(param_1,*(int *)(param_1 + 0x94) + 4);
      uVar3 = 0x10;
      if ((*(byte *)(param_1 + 0x2a) & 0x80) == 0) {
        uVar3 = 0;
      }
      *(uint *)(*(int *)(param_1 + 0x94) + 0x14) = uVar3 | *(uint *)(param_1 + 0x44);
    }
    uVar2 = *(undefined4 *)(param_1 + 0x94);
  }
  return uVar2;
}

