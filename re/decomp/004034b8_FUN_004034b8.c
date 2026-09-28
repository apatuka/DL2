// FUN_004034b8 @ 004034b8 size=81 sig=undefined FUN_004034b8() cc=unknown
// callers: FUN_00408a88
// callees: FUN_00403350

void FUN_004034b8(int param_1)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = &DAT_0059f161;
  for (iVar1 = 0; (*(uint *)(&DAT_0052222c + param_1 * 4) != 0 && (iVar1 < 7)); iVar1 = iVar1 + 1) {
    if (((1 << ((byte)iVar1 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) != 0) &&
       (*pcVar2 == '\0')) {
      FUN_00403350(param_1,iVar1);
    }
    pcVar2 = pcVar2 + 0x2d8;
  }
  return;
}

