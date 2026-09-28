// FUN_00419110 @ 00419110 size=68 sig=undefined FUN_00419110() cc=unknown
// callers: FUN_00419154,FUN_004193e0
// callees: FUN_004921f8,strlen

void FUN_00419110(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  
  iVar1 = strlen(param_1);
  pcVar3 = (char *)(param_1 + -5 + iVar1);
  while( true ) {
    iVar1 = FUN_004921f8(param_1);
    if (iVar1 <= param_2) break;
    pcVar2 = pcVar3 + -1;
    if (*pcVar2 == ' ') {
      pcVar2 = pcVar3 + -2;
    }
    builtin_strncpy(pcVar2 + 1,"...",4);
    pcVar3 = pcVar2;
  }
  return;
}

