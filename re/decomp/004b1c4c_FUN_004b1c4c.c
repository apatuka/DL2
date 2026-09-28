// FUN_004b1c4c @ 004b1c4c size=269 sig=undefined FUN_004b1c4c() cc=unknown
// callers: FUN_004b1c1c
// callees: FUN_004ac7ec,thunk_FUN_004ace38,FUN_004affd4,strlen,FUN_004ac718,FUN_004b0a30,FUN_004a68dc

void FUN_004b1c4c(undefined4 param_1,char *param_2,char *param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  iVar2 = FUN_004ac7ec(0,param_3,0x104);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = strlen(param_3);
  }
  while( true ) {
    param_3[iVar2] = '\0';
    if (iVar2 != 0) {
      pcVar3 = (char *)FUN_004affd4(param_3,param_3 + iVar2);
      if ((*pcVar3 != '\\') && (*pcVar3 != '/')) {
        FUN_004a68dc(param_3,&DAT_00521374);
      }
    }
    FUN_004a68dc(param_3,param_1);
    iVar2 = thunk_FUN_004ace38(param_3,0);
    if (iVar2 == 0) break;
    if (*param_2 == '\0') {
      *param_3 = '\0';
      return;
    }
    iVar2 = 0;
    pcVar3 = param_3;
    for (; (cVar1 = *param_2, cVar1 != ';' && (cVar1 != '\0')); param_2 = param_2 + 1) {
      *pcVar3 = cVar1;
      pcVar3 = pcVar3 + 1;
      iVar2 = iVar2 + 1;
    }
    if (*param_2 != '\0') {
      param_2 = param_2 + 1;
    }
  }
  pcVar3 = (char *)FUN_004ac718(0,param_3,0x104);
  if (pcVar3 == (char *)0x0) {
    return;
  }
  uVar4 = 0xffffffff;
  pcVar6 = pcVar3;
  do {
    pcVar7 = pcVar6;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = pcVar7 + -uVar4;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)param_3 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    param_3 = param_3 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *param_3 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    param_3 = param_3 + 1;
  }
  FUN_004b0a30(pcVar3);
  return;
}

