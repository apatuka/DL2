// FUN_0045ae00 @ 0045ae00 size=53 sig=undefined FUN_0045ae00() cc=unknown
// callers: FUN_0045f148,RunAITurns,FUN_0045e554
// callees: 

int FUN_0045ae00(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  pcVar1 = &DAT_0059f161;
  for (iVar3 = 0; iVar3 < DAT_004d5aec; iVar3 = iVar3 + 1) {
    if (*pcVar1 != '\0') {
      iVar2 = iVar2 + 1;
    }
    pcVar1 = pcVar1 + 0x2d8;
  }
  if ((DAT_004d5aa0 != '\0') && (iVar2 == 0)) {
    return 1;
  }
  return iVar2;
}

