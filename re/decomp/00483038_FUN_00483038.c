// FUN_00483038 @ 00483038 size=66 sig=undefined FUN_00483038() cc=unknown
// callers: FUN_00483098,FUN_00483120,FUN_004818ac
// callees: 

void FUN_00483038(int param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  pcVar1 = *(char **)(param_1 + 8);
  iVar3 = (int)*(short *)(param_1 + 6);
  while (iVar4 = iVar3 + -1, iVar3 != 0) {
    iVar2 = (int)*(short *)(param_1 + 4);
    while (iVar3 = iVar4, iVar2 != 0) {
      if (*pcVar1 == -1) {
        *pcVar1 = -0x40;
      }
      else if (*pcVar1 == '\0') {
        *pcVar1 = -1;
      }
      pcVar1 = pcVar1 + 1;
      iVar2 = iVar2 + -1;
    }
  }
  return;
}

