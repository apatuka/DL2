// FUN_004190c0 @ 004190c0 size=78 sig=undefined FUN_004190c0() cc=unknown
// callers: FUN_00419154
// callees: FUN_0049eb44

void FUN_004190c0(void)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  puVar1 = &DAT_0053b218;
  do {
    *puVar1 = 0xff;
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar2 < 0x1b);
  iVar2 = FUN_0049eb44(DAT_004b76b4,0x2c,1,0x18,0,0);
  iVar3 = 0;
  if (0 < iVar2) {
    do {
      FUN_0049eb44(DAT_004b76b4,0x2c,1,0x27,0,0);
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar2);
  }
  return;
}

