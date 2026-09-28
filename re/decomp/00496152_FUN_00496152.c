// FUN_00496152 @ 00496152 size=71 sig=undefined FUN_00496152() cc=unknown
// callers: 
// callees: FUN_0048a61d

int FUN_00496152(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  if (DAT_0051e08c != (int *)0x0) {
    for (iVar1 = *DAT_0051e08c; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
      if (((param_1 == 0) || (param_1 == *(int *)(iVar1 + 0x30))) &&
         (uVar2 = FUN_0048a61d(iVar1), (uVar2 & 1) == 1)) {
        iVar3 = iVar3 + 1;
      }
    }
  }
  return iVar3;
}

