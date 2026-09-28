// FUN_0041edac @ 0041edac size=41 sig=undefined FUN_0041edac() cc=unknown
// callers: FUN_0041edd8
// callees: 

int FUN_0041edac(int param_1)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = 0;
  pcVar2 = &DAT_0059f162;
  do {
    if (param_1 == *pcVar2) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 0x2d8;
  } while (iVar1 < 7);
  return -1;
}

