// FUN_00441a44 @ 00441a44 size=33 sig=undefined FUN_00441a44() cc=unknown
// callers: WinMain,FUN_0046ce10,ShutdownGame
// callees: FUN_004419c8

void FUN_00441a44(void)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &DAT_0055a192;
  do {
    if (*piVar1 != 0) {
      FUN_004419c8(*piVar1);
    }
    iVar2 = iVar2 + 1;
    piVar1 = (int *)((int)piVar1 + 0x1a);
  } while (iVar2 < 0x40);
  return;
}

