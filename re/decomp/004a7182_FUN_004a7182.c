// FUN_004a7182 @ 004a7182 size=40 sig=undefined FUN_004a7182() cc=unknown
// callers: 
// callees: FUN_004010f9

undefined4 FUN_004a7182(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = FUN_004010f9();
  uVar1 = *(undefined4 *)(iVar2 + 0x18);
  if (param_1 != 0) {
    iVar2 = FUN_004010f9();
    *(int *)(iVar2 + 0x18) = param_1;
  }
  return uVar1;
}

