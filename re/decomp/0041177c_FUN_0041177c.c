// FUN_0041177c @ 0041177c size=138 sig=undefined FUN_0041177c() cc=unknown
// callers: FUN_0041287c,FUN_00412800
// callees: free,strlen,FUN_004a68dc,malloc

undefined4 FUN_0041177c(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  
  if (*(int *)(param_1 + 8) != 0) {
    free(*(int *)(param_1 + 8));
  }
  iVar2 = strlen(param_2);
  pcVar3 = (char *)malloc(iVar2 + 2);
  *(char **)(param_1 + 8) = pcVar3;
  if (pcVar3 == (char *)0x0) {
    uVar4 = 0xfffffffc;
  }
  else {
    uVar6 = 0xffffffff;
    do {
      pcVar8 = param_2;
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      pcVar8 = param_2 + 1;
      cVar1 = *param_2;
      param_2 = pcVar8;
    } while (cVar1 != '\0');
    uVar6 = ~uVar6;
    pcVar8 = pcVar8 + -uVar6;
    for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *(undefined4 *)pcVar3 = *(undefined4 *)pcVar8;
      pcVar8 = pcVar8 + 4;
      pcVar3 = pcVar3 + 4;
    }
    for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pcVar3 = *pcVar8;
      pcVar8 = pcVar8 + 1;
      pcVar3 = pcVar3 + 1;
    }
    iVar2 = *(int *)(param_1 + 8);
    iVar5 = strlen(iVar2);
    if (*(char *)(iVar2 + -1 + iVar5) != '\\') {
      FUN_004a68dc(*(undefined4 *)(param_1 + 8),&DAT_004b6fbc);
    }
    uVar4 = 0;
  }
  return uVar4;
}

