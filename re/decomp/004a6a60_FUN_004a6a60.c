// FUN_004a6a60 @ 004a6a60 size=52 sig=undefined FUN_004a6a60() cc=unknown
// callers: FUN_00458640,FUN_00473324,FUN_00461ff4
// callees: 

int FUN_004a6a60(char *param_1,char *param_2,int param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  
  iVar3 = 0;
  iVar4 = param_3;
  pcVar5 = param_2;
  if (param_3 != 0) {
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    param_3 = param_3 - iVar4;
    do {
      pcVar5 = param_1;
      pcVar6 = param_2;
      if (param_3 == 0) break;
      param_3 = param_3 + -1;
      pcVar6 = param_2 + 1;
      pcVar5 = param_1 + 1;
      cVar2 = *param_2;
      cVar1 = *param_1;
      param_1 = pcVar5;
      param_2 = pcVar6;
    } while (cVar1 == cVar2);
    iVar3 = (uint)(byte)pcVar5[-1] - (uint)(byte)pcVar6[-1];
  }
  return iVar3;
}

