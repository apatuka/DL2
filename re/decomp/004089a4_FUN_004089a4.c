// FUN_004089a4 @ 004089a4 size=47 sig=undefined FUN_004089a4() cc=unknown
// callers: FUN_00408a88
// callees: FUN_00408894

void FUN_004089a4(undefined4 param_1)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = &DAT_0059f161;
  iVar1 = 0;
  do {
    if (-1 < *pcVar2) {
      FUN_00408894(param_1,iVar1);
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 0x2d8;
  } while (iVar1 < 7);
  return;
}

