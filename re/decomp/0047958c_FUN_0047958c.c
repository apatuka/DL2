// FUN_0047958c @ 0047958c size=93 sig=undefined FUN_0047958c() cc=unknown
// callers: ResetNetGame
// callees: FUN_004050ac,FUN_0047549c,FUN_00401830

void FUN_0047958c(void)

{
  char *pcVar1;
  int iVar2;
  undefined1 *puVar3;
  
  iVar2 = 0;
  pcVar1 = &DAT_0059f161;
  do {
    if (*pcVar1 == -1) {
      *pcVar1 = '\x03';
    }
    iVar2 = iVar2 + 1;
    pcVar1 = pcVar1 + 0x2d8;
  } while (iVar2 < 7);
  iVar2 = 0;
  puVar3 = &DAT_0059f160;
  do {
    *puVar3 = (char)iVar2;
    FUN_00401830(iVar2);
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 0x2d8;
  } while (iVar2 < 7);
  if ((DAT_0058f1f4 == DAT_004d5a58) && (DAT_0059f154 == 1)) {
    FUN_004050ac();
    FUN_0047549c();
  }
  return;
}

