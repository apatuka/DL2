// FUN_004a74d5 @ 004a74d5 size=45 sig=undefined FUN_004a74d5() cc=unknown
// callers: 
// callees: FUN_004010f9,FUN_004b0a30

void FUN_004a74d5(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_004010f9();
  if (param_1 == *(int *)(iVar1 + 0x28)) {
    iVar1 = FUN_004010f9();
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) & 0xfffffffe;
    return;
  }
  FUN_004b0a30(param_1);
  return;
}

