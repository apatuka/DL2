// FUN_004626f0 @ 004626f0 size=50 sig=undefined FUN_004626f0() cc=unknown
// callers: FUN_004634a0
// callees: 

void FUN_004626f0(void)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  
  iVar2 = 0;
  puVar4 = &DAT_005a0550;
  do {
    iVar3 = 0;
    puVar1 = puVar4;
    do {
      *puVar1 = (char)iVar3;
      puVar1[1] = (char)iVar2;
      *(undefined2 *)(puVar1 + 2) = 0xffff;
      puVar1[4] = 0;
      iVar3 = iVar3 + 1;
      puVar1 = puVar1 + 10;
    } while (iVar3 < 0x28);
    iVar2 = iVar2 + 1;
    puVar4 = puVar4 + 400;
  } while (iVar2 < 0x28);
  return;
}

