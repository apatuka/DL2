// FUN_00426c90 @ 00426c90 size=72 sig=undefined FUN_00426c90() cc=unknown
// callers: FUN_00426cd8
// callees: 

int FUN_00426c90(void)

{
  undefined *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = &DAT_005a43d0;
  while( true ) {
    if (DAT_004d5b18 < iVar2) {
      return -1;
    }
    if ((((puVar1[0x20] == -1) && (puVar1[0x21] != '\0')) && (puVar1[0x21] != '\x05')) &&
       ((puVar1[0x7e] != '\0' && ((*(uint *)(puVar1 + 0x1c) & 0x104) == 0)))) break;
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0xadc;
  }
  return iVar2;
}

