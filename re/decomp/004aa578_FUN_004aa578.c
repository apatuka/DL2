// FUN_004aa578 @ 004aa578 size=52 sig=undefined FUN_004aa578() cc=unknown
// callers: FUN_004aa5ac,FUN_004aa630
// callees: FUN_004a9c80

void FUN_004aa578(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_0051fce4;
  iVar2 = 0x32;
  while (iVar2 != 0) {
    if ((*(ushort *)((int)puVar1 + 0x12) & 0x300) == 0x300) {
      FUN_004a9c80(puVar1);
    }
    puVar1 = puVar1 + 6;
    iVar2 = iVar2 + -1;
  }
  return;
}

