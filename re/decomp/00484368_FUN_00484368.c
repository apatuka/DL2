// FUN_00484368 @ 00484368 size=65 sig=undefined FUN_00484368() cc=unknown
// callers: FUN_00466218
// callees: memset

void FUN_00484368(void)

{
  undefined2 *puVar1;
  int iVar2;
  undefined **ppuVar3;
  int iVar4;
  
  iVar4 = 0;
  ppuVar3 = &PTR_DAT_00503e12;
  do {
    puVar1 = (undefined2 *)*ppuVar3;
    for (iVar2 = 0; iVar2 < *(short *)((int)ppuVar3 + -2); iVar2 = iVar2 + 1) {
      *puVar1 = 0;
      puVar1 = puVar1 + 3;
    }
    iVar4 = iVar4 + 1;
    ppuVar3 = (undefined **)((int)ppuVar3 + 6);
  } while (iVar4 < 6);
  memset(&DAT_00501b50,0,10);
  return;
}

