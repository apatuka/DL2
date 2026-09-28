// FUN_004960fd @ 004960fd size=85 sig=undefined FUN_004960fd() cc=unknown
// callers: FUN_004a2cb5,FUN_00482ba0
// callees: FUN_0048a61d,FUN_00495fc5

void FUN_004960fd(void)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_0051e08c != (int *)0x0) {
    iVar1 = *DAT_0051e08c;
    while (iVar1 != 0) {
      if ((((*(byte *)(iVar1 + 0xc) & 2) == 0) || (uVar2 = FUN_0048a61d(iVar1), (uVar2 & 1) == 1))
         || (((iVar1 != *(int *)(iVar1 + 0x20) || ((*(byte *)(iVar1 + 0xc) & 4) != 0)) &&
             (iVar1 == *(int *)(iVar1 + 0x20))))) {
        iVar1 = *(int *)(iVar1 + 4);
      }
      else {
        FUN_00495fc5(iVar1);
        iVar1 = *DAT_0051e08c;
      }
    }
  }
  return;
}

