// FUN_0040e868 @ 0040e868 size=66 sig=undefined FUN_0040e868() cc=unknown
// callers: FUN_00409b28,FUN_0040e8ac
// callees: 

int FUN_0040e868(int param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  if (*(short *)(param_1 + 0x30) != 0) {
    iVar3 = 0;
    pcVar1 = (char *)(param_1 + 0x144);
    do {
      if ((*pcVar1 == '\0') && ((*(short *)(pcVar1 + -2) != 0) < 5)) {
        iVar2 = iVar2 + 1;
      }
      iVar3 = iVar3 + 1;
      pcVar1 = pcVar1 + 0x34;
    } while (iVar3 < 0x24);
  }
  return iVar2;
}

