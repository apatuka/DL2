// FUN_0046c9f8 @ 0046c9f8 size=70 sig=undefined FUN_0046c9f8() cc=unknown
// callers: WinMain
// callees: FUN_00405798

void FUN_0046c9f8(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  FUN_00405798();
  iVar2 = 0;
  puVar1 = &DAT_005a4d6a;
  do {
    iVar2 = iVar2 + 1;
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1 = puVar1 + 0x2b7;
  } while (iVar2 < 0x70);
  iVar2 = 0;
  puVar1 = &DAT_0059f19a;
  do {
    iVar2 = iVar2 + 1;
    *puVar1 = 0;
    puVar1 = puVar1 + 0xb6;
  } while (iVar2 < 8);
  return;
}

