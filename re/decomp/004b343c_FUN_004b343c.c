// FUN_004b343c @ 004b343c size=295 sig=undefined FUN_004b343c() cc=unknown
// callers: 
// callees: memset,memcpy,FUN_004a67ec,FUN_004a9090,FUN_004b0a30,FUN_004b3400,FUN_004b0b44,FUN_004a6ccc,FUN_004b33b0

void FUN_004b343c(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  iVar3 = (*(int *)(param_1 + 6) + param_5) - param_3;
  uVar1 = FUN_004b3400(iVar3);
  if (*(uint *)(param_1 + 10) < uVar1) {
    FUN_004b33b0(param_1,uVar1);
    iVar2 = *(int *)(param_1 + 2);
  }
  else if ((DAT_005217f4 < *(int *)(param_1 + 10) - uVar1) && ((*(byte *)(param_1 + 0xe) & 1) == 0))
  {
    iVar2 = FUN_004b0b44(uVar1 + 1);
    if (*(int *)(param_1 + 2) == 0) {
      FUN_004a6ccc(&DAT_0052114c);
    }
    if (param_2 != 0) {
      memcpy(iVar2,*(undefined4 *)(param_1 + 2),param_2);
    }
    *(uint *)(param_1 + 10) = uVar1;
  }
  else {
    iVar2 = *(int *)(param_1 + 2);
  }
  if ((iVar2 != *(int *)(param_1 + 2)) || (param_5 != param_3)) {
    FUN_004a67ec(param_2 + iVar2 + param_5,*(int *)(param_1 + 2) + param_2 + param_3,
                 (*(int *)(param_1 + 6) - param_2) - param_3);
  }
  if (param_5 != 0) {
    if (param_4 == 0) {
      memset(param_2 + iVar2,0x20,param_5);
    }
    else {
      FUN_004a67ec(param_2 + iVar2,param_4,param_5);
    }
  }
  *(int *)(param_1 + 6) = iVar3;
  *(undefined1 *)(iVar2 + iVar3) = 0;
  if (iVar2 != *(int *)(param_1 + 2)) {
    FUN_004b0a30(*(int *)(param_1 + 2));
    *(int *)(param_1 + 2) = iVar2;
  }
  *unaff_FS_OFFSET = local_28;
  return;
}

