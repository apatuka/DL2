// FUN_00496093 @ 00496093 size=106 sig=undefined FUN_00496093() cc=unknown
// callers: 
// callees: FUN_0048a61d,FUN_0048a316,FUN_0048a3ef,FUN_00495fc5

void FUN_00496093(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  if (DAT_0051e08c != (int *)0x0) {
    iVar1 = *DAT_0051e08c;
    while (iVar1 != 0) {
      if (((*(uint *)(iVar1 + 0x10) < param_1) &&
          (((param_2 == 0 || (uVar2 = FUN_0048a61d(iVar1), (uVar2 & 1) != 1)) &&
           (iVar3 = FUN_0048a316(iVar1), iVar3 != 0)))) && ((*(byte *)(iVar1 + 0xc) & 4) == 0)) {
        FUN_0048a3ef(iVar1);
        FUN_00495fc5(iVar1);
        iVar1 = *DAT_0051e08c;
      }
      else {
        iVar1 = *(int *)(iVar1 + 4);
      }
    }
  }
  return;
}

