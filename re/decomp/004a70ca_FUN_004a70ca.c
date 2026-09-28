// FUN_004a70ca @ 004a70ca size=173 sig=undefined FUN_004a70ca() cc=unknown
// callers: FUN_004a7b8d
// callees: FUN_004a9090,FUN_004b17d4,@__unlockDebuggerData$qv,@__lockDebuggerData$qv,FUN_004010f9,FUN_004ac5d8

void FUN_004a70ca(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  iVar2 = FUN_004010f9();
  if ((**(int **)(iVar2 + 0xc) != 0) && (DAT_0051f190 == 0)) {
    ___lockDebuggerData_qv();
    iVar2 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar2 + 0x10) + 0x14) = 5;
    iVar2 = FUN_004010f9();
    uVar1 = *(undefined4 *)(iVar2 + 0x14);
    iVar2 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar2 + 0x10) + 0x18) = uVar1;
    iVar2 = FUN_004010f9();
    (**(code **)(*(int *)(iVar2 + 0x10) + 0xc))();
    ___unlockDebuggerData_qv();
    DAT_0051f190 = 0;
  }
  FUN_004ac5d8();
  iVar2 = FUN_004010f9();
  (**(code **)(iVar2 + 0x14))();
  FUN_004b17d4();
  *unaff_FS_OFFSET = local_28;
  return;
}

