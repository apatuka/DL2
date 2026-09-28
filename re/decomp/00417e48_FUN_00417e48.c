// FUN_00417e48 @ 00417e48 size=48 sig=undefined FUN_00417e48() cc=unknown
// callers: FUN_004185d4
// callees: 

void FUN_00417e48(void)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  puVar2 = &DAT_00533405;
  do {
    *puVar2 = 1;
    iVar3 = 0;
    puVar1 = (undefined4 *)(puVar2 + -0x12d);
    do {
      iVar3 = iVar3 + 1;
      *puVar1 = 0;
      puVar1 = puVar1 + 8;
    } while (iVar3 < 10);
    iVar4 = iVar4 + 1;
    puVar2 = puVar2 + 0x146;
  } while (iVar4 < 100);
  return;
}

