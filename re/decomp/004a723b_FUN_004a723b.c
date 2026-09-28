// FUN_004a723b @ 004a723b size=154 sig=undefined FUN_004a723b() cc=unknown
// callers: entry
// callees: FUN_004010f9,FUN_004a72d6,memcpy

void FUN_004a723b(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  undefined1 local_c [4];
  int local_8;
  
  bVar3 = param_1 != 0;
  if (param_1 == 0) {
    FUN_004a72d6(local_c);
    param_1 = local_8;
  }
  else {
    *(undefined1 **)(param_1 + 0x14) = &LAB_004a709c;
    *(undefined1 **)(param_1 + 0x18) = &LAB_004a717c;
  }
  uVar1 = FUN_004010f9(param_1,0xb0);
  memcpy(uVar1);
  if (bVar3) {
    iVar2 = FUN_004010f9();
    *(undefined **)(iVar2 + 0xc) = &DAT_0051f114;
    iVar2 = FUN_004010f9();
    *(undefined **)(iVar2 + 0x10) = &__DebuggerHookData;
  }
  iVar2 = FUN_004010f9();
  *(undefined1 **)(iVar2 + 0x14) = &LAB_004a709c;
  iVar2 = FUN_004010f9();
  *(undefined1 **)(iVar2 + 0x18) = &LAB_004a717c;
  return;
}

