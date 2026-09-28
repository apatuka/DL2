// FUN_0045f108 @ 0045f108 size=64 sig=undefined FUN_0045f108() cc=unknown
// callers: FUN_0045f148,RunAITurns,FUN_0045e554
// callees: 

int FUN_0045f108(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  pcVar1 = &DAT_0059f161;
  do {
    if ((*pcVar1 != '\0') && (pcVar1[7] != '\0')) {
      iVar2 = iVar2 + 1;
    }
    iVar3 = iVar3 + 1;
    pcVar1 = pcVar1 + 0x2d8;
  } while (iVar3 < 7);
  if (((DAT_004d5aa0 != '\0') && (iVar2 == 0)) && (DAT_0059f168 != '\0')) {
    return 1;
  }
  return iVar2;
}

