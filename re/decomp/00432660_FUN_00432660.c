// FUN_00432660 @ 00432660 size=79 sig=undefined FUN_00432660() cc=unknown
// callers: FUN_00432ad0,CheckSubInfo
// callees: 

int FUN_00432660(void)

{
  undefined *puVar1;
  int iVar2;
  
  DAT_00558cc0 = 0xffffffff;
  iVar2 = 1;
  puVar1 = &DAT_005a43d0;
  while( true ) {
    if (DAT_004d5b18 < iVar2) {
      return -1;
    }
    if ((((*(uint *)(puVar1 + 0x1c) & 4) == 0) && (puVar1[0x7e] != '\0')) &&
       ((*(uint *)(puVar1 + 0x1c) & 0x100) == 0)) break;
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0xadc;
  }
  *(uint *)(puVar1 + 0x1c) = *(uint *)(puVar1 + 0x1c) | 2;
  DAT_00558cc0 = (int)*(short *)(puVar1 + 0x1a);
  return (int)*(short *)(puVar1 + 0x1a);
}

