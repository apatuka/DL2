// FUN_0049604c @ 0049604c size=71 sig=undefined FUN_0049604c() cc=unknown
// callers: FUN_00482a1c,FUN_00482a38,FUN_004962e7
// callees: FUN_0048a316,FUN_0048a3ef,FUN_00495fc5

void FUN_0049604c(void)

{
  int iVar1;
  int iVar2;
  
  if (DAT_0051e08c != (int *)0x0) {
    iVar1 = *DAT_0051e08c;
    while (iVar1 != 0) {
      iVar2 = FUN_0048a316(iVar1);
      if ((iVar2 == 0) || ((*(byte *)(iVar1 + 0xc) & 4) != 0)) {
        iVar1 = *(int *)(iVar1 + 4);
      }
      else {
        FUN_0048a3ef(iVar1);
        FUN_00495fc5(iVar1);
        iVar1 = *DAT_0051e08c;
      }
    }
  }
  return;
}

