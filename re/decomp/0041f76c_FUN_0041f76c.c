// FUN_0041f76c @ 0041f76c size=50 sig=undefined FUN_0041f76c() cc=unknown
// callers: 
// callees: 

int FUN_0041f76c(int param_1)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = 0;
  pcVar1 = &DAT_0059f161;
  while ((*pcVar1 == '\0' || (param_1 != pcVar1[1]))) {
    iVar2 = iVar2 + 1;
    pcVar1 = pcVar1 + 0x2d8;
    if (6 < iVar2) {
      return -1;
    }
  }
  return iVar2;
}

