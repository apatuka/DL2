// FUN_00478090 @ 00478090 size=83 sig=undefined FUN_00478090() cc=unknown
// callers: FUN_0046e39c,WinMain
// callees: FUN_0046e374,FUN_00458298

void FUN_00478090(void)

{
  char *pcVar1;
  int iVar2;
  
  DAT_0058f1fc = 0;
  DAT_004d5a50 = 0;
  FUN_00458298();
  iVar2 = 0;
  DAT_004d5a58 = DAT_0058f1f4;
  pcVar1 = &DAT_0059f161;
  do {
    if (((iVar2 != DAT_0058f1f4) && (*pcVar1 != '\0')) && (*pcVar1 < '\x03')) {
      *pcVar1 = '\x03';
    }
    iVar2 = iVar2 + 1;
    pcVar1 = pcVar1 + 0x2d8;
  } while (iVar2 < 7);
  FUN_0046e374();
  return;
}

