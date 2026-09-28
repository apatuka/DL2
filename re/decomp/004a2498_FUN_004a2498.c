// FUN_004a2498 @ 004a2498 size=89 sig=undefined FUN_004a2498() cc=unknown
// callers: FUN_004a2cb5
// callees: FUN_0049cd32,FUN_0049f715,FUN_0049e007,FUN_004a128d

undefined4 FUN_004a2498(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0049f715(param_1);
  if (iVar1 != 0) {
    if (((DAT_0051dca4 & 2) != 0) && (iVar2 = FUN_004a128d(iVar1,param_2), iVar2 != 0)) {
      return 0;
    }
    if (*(int *)(iVar1 + 0x1c) == 5) {
      uVar3 = FUN_0049e007(param_1,iVar1,param_2);
      return uVar3;
    }
    if (*(int *)(iVar1 + 0x1c) == 6) {
      uVar3 = FUN_0049cd32(param_1,iVar1,param_2);
      return uVar3;
    }
  }
  return 0;
}

