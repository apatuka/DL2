// FUN_0044c978 @ 0044c978 size=39 sig=undefined FUN_0044c978() cc=unknown
// callers: FUN_0044bea8
// callees: 

int FUN_0044c978(int param_1)

{
  int iVar1;
  char *pcVar2;
  
  if (param_1 != 0) {
    iVar1 = 0;
    pcVar2 = (char *)(param_1 + 0x2c);
    do {
      if (*pcVar2 != '\0') {
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      pcVar2 = pcVar2 + 1;
    } while (iVar1 < 5);
  }
  return -1;
}

