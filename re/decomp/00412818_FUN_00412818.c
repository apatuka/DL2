// FUN_00412818 @ 00412818 size=97 sig=undefined FUN_00412818() cc=unknown
// callers: 
// callees: free,malloc,strlen

undefined4 FUN_00412818(int *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  
  if (*param_1 != 0) {
    free(*param_1);
  }
  iVar2 = strlen(param_2);
  pcVar3 = (char *)malloc(iVar2 + 1);
  *param_1 = (int)pcVar3;
  if (pcVar3 == (char *)0x0) {
    uVar4 = 0xfffffffc;
  }
  else {
    uVar5 = 0xffffffff;
    do {
      pcVar7 = param_2;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar7 = param_2 + 1;
      cVar1 = *param_2;
      param_2 = pcVar7;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar7 = pcVar7 + -uVar5;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar3 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pcVar3 = pcVar3 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar3 = *pcVar7;
      pcVar7 = pcVar7 + 1;
      pcVar3 = pcVar3 + 1;
    }
    uVar4 = 0;
  }
  return uVar4;
}

