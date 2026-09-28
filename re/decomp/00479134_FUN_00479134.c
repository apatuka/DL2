// FUN_00479134 @ 00479134 size=48 sig=undefined FUN_00479134() cc=unknown
// callers: ResetNetGame
// callees: 

void FUN_00479134(void)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = 0;
  piVar3 = &DAT_00653600;
  pcVar1 = &DAT_0059f161;
  do {
    if (*pcVar1 == '\0') {
      *piVar3 = -1;
    }
    else {
      *piVar3 = (int)pcVar1[1];
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
    pcVar1 = pcVar1 + 0x2d8;
  } while (iVar2 < 7);
  return;
}

