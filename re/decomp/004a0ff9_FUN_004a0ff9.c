// FUN_004a0ff9 @ 004a0ff9 size=186 sig=undefined FUN_004a0ff9() cc=unknown
// callers: FUN_004a10b3
// callees: FUN_004935fc

undefined4 FUN_004a0ff9(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *(int *)(param_1 + 0xc);
  iVar2 = *(int *)(param_1 + 8);
  iVar4 = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
  iVar3 = *(int *)(param_1 + 8) + *(int *)(param_1 + 0x14);
  FUN_004935fc(iVar2 + 1,iVar1 + 1,iVar3 + -1,iVar4 + -1,*(undefined4 *)(param_1 + 0xf0));
  FUN_004935fc(iVar2,iVar1,iVar3,iVar1 + 1,*(undefined4 *)(param_1 + 0xfc));
  FUN_004935fc(iVar2,iVar1,iVar2 + 1,iVar4 + -1,*(undefined4 *)(param_1 + 0xfc));
  FUN_004935fc(iVar2,iVar4 + -1,iVar3,iVar4,*(undefined4 *)(param_1 + 0x108));
  FUN_004935fc(iVar3 + -1,iVar1 + 1,iVar3,iVar4,*(undefined4 *)(param_1 + 0x108));
  return 1;
}

