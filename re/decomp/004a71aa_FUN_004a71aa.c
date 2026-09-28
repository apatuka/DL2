// FUN_004a71aa @ 004a71aa size=114 sig=undefined FUN_004a71aa() cc=unknown
// callers: _ExceptionHandler
// callees: FUN_004b17d4,@__unlockDebuggerData$qv,@__lockDebuggerData$qv,FUN_004010f9

void FUN_004a71aa(void)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = FUN_004010f9();
  if (**(int **)(iVar2 + 0xc) != 0) {
    ___lockDebuggerData_qv();
    iVar2 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar2 + 0x10) + 0x14) = 4;
    iVar2 = FUN_004010f9();
    uVar1 = *(undefined4 *)(iVar2 + 0x18);
    iVar2 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar2 + 0x10) + 0x18) = uVar1;
    DAT_0051f190 = 1;
    iVar2 = FUN_004010f9();
    (**(code **)(*(int *)(iVar2 + 0x10) + 0xc))();
    ___unlockDebuggerData_qv();
  }
  iVar2 = FUN_004010f9();
  (**(code **)(iVar2 + 0x18))();
  FUN_004b17d4();
  return;
}

