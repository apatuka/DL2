// FUN_00478060 @ 00478060 size=45 sig=undefined FUN_00478060() cc=unknown
// callers: FUN_004780e4
// callees: 

int FUN_00478060(void)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = 0;
  pcVar1 = &DAT_0059f161;
  while (((iVar2 == DAT_004d5a58 || (*pcVar1 == '\0')) || ('\x02' < *pcVar1))) {
    iVar2 = iVar2 + 1;
    pcVar1 = pcVar1 + 0x2d8;
    if (6 < iVar2) {
      return 0;
    }
  }
  return iVar2;
}

