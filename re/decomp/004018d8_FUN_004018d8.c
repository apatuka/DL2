// FUN_004018d8 @ 004018d8 size=176 sig=undefined FUN_004018d8() cc=unknown
// callers: ResetVariables
// callees: FUN_004057c4,memset,FUN_00401830,FUN_0040231c

void FUN_004018d8(void)

{
  int iVar1;
  char *pcVar2;
  
  FUN_004057c4();
  memset(&DAT_00522584,0,0x10bf8);
  memset(&DAT_0052222c,0,0x1c);
  memset(&DAT_005220a4,0,0xc4);
  memset(&DAT_00522168,0,0xc4);
  memset(&DAT_00522088,0,0x1c);
  memset(&DAT_0052206c,0,0x1c);
  memset(&DAT_0053317c,0,0x1c);
  iVar1 = 0;
  pcVar2 = &DAT_0059f161;
  do {
    if ('\x02' < *pcVar2) {
      FUN_00401830(iVar1);
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 0x2d8;
  } while (iVar1 < 7);
  FUN_0040231c();
  return;
}

