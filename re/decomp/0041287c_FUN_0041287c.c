// FUN_0041287c @ 0041287c size=1110 sig=undefined FUN_0041287c() cc=unknown
// callers: FUN_00412654
// callees: FUN_004132cc,fopen,FUN_004ae26c,FUN_004a9d10,FUN_004b0b44,FUN_004aa380,free,fclose,FUN_0041177c,malloc,strlen,FUN_004b02a8,FUN_004a6b48
// strings: \"BEGIN\"

undefined4 FUN_0041287c(int *param_1,undefined4 param_2)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  bool bVar10;
  char local_108 [256];
  int local_8;
  
  iVar3 = fopen(param_2,&DAT_004b6ff7);
  if (iVar3 == 0) {
    return 0xfffffffe;
  }
  FUN_004a9d10(local_108,0x100,iVar3);
  iVar4 = strlen(local_108);
  pcVar9 = &DAT_004b6ff9;
  local_108[iVar4 + -1] = '\0';
  pcVar5 = local_108;
  do {
    if (*pcVar5 != *pcVar9) goto LAB_00412905;
    bVar10 = true;
    if (*pcVar5 == '\0') break;
    pcVar1 = pcVar5 + 1;
    if (*pcVar1 != pcVar9[1]) goto LAB_00412905;
    pcVar5 = pcVar5 + 2;
    pcVar9 = pcVar9 + 2;
    bVar10 = *pcVar1 == '\0';
  } while (!bVar10);
  if (bVar10) {
    *(undefined1 *)((int)param_1 + 0x3d) = 1;
  }
  else {
LAB_00412905:
    *(undefined1 *)((int)param_1 + 0x3d) = 0;
    if (*param_1 != 0) {
      free(*param_1);
    }
    iVar4 = strlen(local_108);
    iVar4 = malloc(iVar4 + 1);
    *param_1 = iVar4;
    if (iVar4 == 0) {
      fclose(iVar3);
      return 0xfffffffc;
    }
    uVar7 = 0xffffffff;
    pcVar5 = local_108;
    do {
      pcVar9 = pcVar5;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar9 = pcVar5 + 1;
      cVar2 = *pcVar5;
      pcVar5 = pcVar9;
    } while (cVar2 != '\0');
    uVar7 = ~uVar7;
    pcVar5 = pcVar9 + -uVar7;
    pcVar9 = (char *)*param_1;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar9 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar9 = pcVar9 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar9 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  FUN_004a9d10(local_108,0x100,iVar3);
  *(char *)(param_1 + 2) = local_108[0];
  FUN_004a9d10(local_108,0x100,iVar3);
  iVar4 = strlen(local_108);
  local_108[iVar4 + -1] = '\0';
  if (param_1[1] != 0) {
    free(param_1[1]);
  }
  iVar4 = strlen(local_108);
  iVar4 = malloc(iVar4 + 1);
  param_1[1] = iVar4;
  if (iVar4 == 0) {
    fclose(iVar3);
    return 0xfffffffc;
  }
  uVar7 = 0xffffffff;
  pcVar5 = local_108;
  do {
    pcVar9 = pcVar5;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar9 = pcVar5 + 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar9;
  } while (cVar2 != '\0');
  uVar7 = ~uVar7;
  pcVar5 = pcVar9 + -uVar7;
  pcVar9 = (char *)param_1[1];
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar9 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar9 = pcVar9 + 1;
  }
  FUN_004a9d10(local_108,0x100,iVar3);
  iVar4 = strlen(local_108);
  local_108[iVar4 + -1] = '\0';
  FUN_0041177c(param_1[0x11],local_108);
  FUN_004aa380(iVar3,&DAT_004b6ffb,(int)param_1 + 10);
  FUN_004aa380(iVar3,&DAT_004b6ffe,local_108);
  pcVar5 = local_108;
  pcVar9 = s_BEGIN_004b7001;
  do {
    bVar10 = *pcVar5 == *pcVar9;
    if (!bVar10) break;
    if (*pcVar5 == '\0') goto LAB_00412ab7;
    pcVar1 = pcVar5 + 1;
    bVar10 = *pcVar1 == pcVar9[1];
    if (!bVar10) break;
    pcVar5 = pcVar5 + 2;
    pcVar9 = pcVar9 + 2;
    bVar10 = *pcVar1 == '\0';
  } while (!bVar10);
  if (!bVar10) {
    fclose(iVar3);
    return 0xfffffffd;
  }
LAB_00412ab7:
  iVar4 = FUN_004b0b44(*(int *)((int)param_1 + 10) << 2);
  *(int *)((int)param_1 + 0xe) = iVar4;
  if (iVar4 == 0) {
    fclose(iVar3);
    return 0xfffffffc;
  }
  FUN_004aa380(iVar3,&DAT_004b6ffe,local_108);
  do {
    pcVar5 = local_108;
    pcVar9 = &DAT_004b7007;
    do {
      bVar10 = *pcVar5 == *pcVar9;
      if (!bVar10) break;
      if (*pcVar5 == '\0') goto LAB_00412c89;
      pcVar1 = pcVar5 + 1;
      bVar10 = *pcVar1 == pcVar9[1];
      if (!bVar10) break;
      pcVar5 = pcVar5 + 2;
      pcVar9 = pcVar9 + 2;
      bVar10 = *pcVar1 == '\0';
    } while (!bVar10);
    if ((bVar10) || ((*(byte *)(iVar3 + 0x12) & 0x20) != 0)) {
LAB_00412c89:
      pcVar5 = local_108;
      pcVar9 = &DAT_004b7007;
      break;
    }
    iVar4 = FUN_004ae26c(local_108);
    if (*(int *)((int)param_1 + 10) <= iVar4) {
      fclose(iVar3);
      return 0xfffffffd;
    }
    local_8 = FUN_004b02a8(0x12);
    if (local_8 == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = FUN_004132cc(local_8);
    }
    *(undefined4 *)(*(int *)((int)param_1 + 0xe) + iVar4 * 4) = uVar6;
    if (*(int *)(*(int *)((int)param_1 + 0xe) + iVar4 * 4) == 0) {
      fclose(iVar3);
      return 0xfffffffc;
    }
    FUN_004aa380(iVar3,&DAT_004b6ffe,local_108);
    if (local_108[0] == 'E') {
      **(undefined4 **)(*(int *)((int)param_1 + 0xe) + iVar4 * 4) = 0;
    }
    else if (local_108[0] == 'K') {
      **(undefined4 **)(*(int *)((int)param_1 + 0xe) + iVar4 * 4) = 2;
    }
    else {
      if (local_108[0] != 'T') {
        fclose(iVar3);
        return 0xfffffffd;
      }
      **(undefined4 **)(*(int *)((int)param_1 + 0xe) + iVar4 * 4) = 1;
    }
    FUN_004aa380(iVar3,&DAT_004b6ffe,local_108);
    FUN_004aa380(iVar3,&DAT_004b6ffe,local_108);
    FUN_004aa380(iVar3,&DAT_004b6ffe,local_108);
    if (**(int **)(*(int *)((int)param_1 + 0xe) + iVar4 * 4) != 0) {
      FUN_004aa380(iVar3,&DAT_004b6ffe,local_108);
      iVar4 = *(int *)(*(int *)((int)param_1 + 0xe) + iVar4 * 4);
      FUN_004a6b48(iVar4 + 4,local_108,9);
      *(undefined1 *)(iVar4 + 0xd) = 0;
    }
    FUN_004aa380(iVar3,&DAT_004b6ffe,local_108);
  } while( true );
  while( true ) {
    if (*pcVar5 == '\0') goto LAB_00412cc0;
    pcVar1 = pcVar5 + 1;
    bVar10 = *pcVar1 == pcVar9[1];
    if (!bVar10) break;
    pcVar5 = pcVar5 + 2;
    pcVar9 = pcVar9 + 2;
    bVar10 = true;
    if (*pcVar1 == '\0') break;
    bVar10 = *pcVar5 == *pcVar9;
    if (!bVar10) break;
  }
  if (bVar10) {
LAB_00412cc0:
    fclose(iVar3);
    uVar6 = 0;
  }
  else {
    fclose(iVar3);
    uVar6 = 0xfffffffd;
  }
  return uVar6;
}

