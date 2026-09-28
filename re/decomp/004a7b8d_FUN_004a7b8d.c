// FUN_004a7b8d @ 004a7b8d size=83 sig=undefined FUN_004a7b8d() cc=unknown
// callers: 
// callees: FUN_004a70ca,FUN_004010f9,FUN_004a78a4

void FUN_004a7b8d(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)FUN_004010f9();
  iVar1 = *piVar2;
  if (iVar1 == 0) {
    FUN_004a70ca();
  }
  if (*(char *)(iVar1 + 0x44) == '\0') {
    iVar3 = *(int *)(iVar1 + 0x40);
  }
  else {
    iVar3 = iVar1 + 0x46;
  }
  FUN_004a78a4(*(undefined4 *)(iVar1 + 4),iVar3,*(undefined4 *)(iVar1 + 8),
               *(undefined4 *)(iVar1 + 0x20),*(undefined4 *)(iVar1 + 0x24),
               *(undefined4 *)(iVar1 + 0xc),param_1,param_2);
  return;
}

