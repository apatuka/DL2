// FUN_004a70a2 @ 004a70a2 size=40 sig=undefined FUN_004a70a2() cc=unknown
// callers: 
// callees: FUN_004010f9

undefined4 FUN_004a70a2(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = FUN_004010f9();
  uVar1 = *(undefined4 *)(iVar2 + 0x14);
  if (param_1 != 0) {
    iVar2 = FUN_004010f9();
    *(int *)(iVar2 + 0x14) = param_1;
  }
  return uVar1;
}

