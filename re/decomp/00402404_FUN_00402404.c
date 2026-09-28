// FUN_00402404 @ 00402404 size=51 sig=undefined FUN_00402404() cc=unknown
// callers: 
// callees: 

int FUN_00402404(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = 0;
  pcVar2 = &DAT_004f9dd4 + param_1 * 0x32;
  do {
    if (param_2 == *pcVar2) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 1;
  } while (iVar1 < 5);
  return -1;
}

