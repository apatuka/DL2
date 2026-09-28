// FUN_00412654 @ 00412654 size=426 sig=undefined FUN_00412654() cc=unknown
// callers: FUN_0042540c,FUN_00421b24,FUN_0041e9e8,FUN_00424a84,FUN_00430cd8,FUN_0042c50c
// callees: free,fclose,thunk_FUN_004ad1a4,malloc,fopen,FUN_00411cbc,FUN_0041244c,FUN_004116f4,FUN_0041287c,strlen,FUN_004b02a8,FUN_004aa518
// strings: \"tmp.sct\"

int FUN_00412654(int param_1,int param_2,undefined4 param_3,undefined4 param_4,char *param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int in_ECX;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  char *pcVar11;
  int local_8;
  
  if (DAT_004b6fe8 != 0) {
    return -1;
  }
  DAT_004b6fe8 = 1;
  *(undefined4 *)(param_1 + 0x1e) = param_6;
  *(undefined4 *)(param_1 + 0x22) = param_7;
  *(undefined4 *)(param_1 + 0x26) = param_8;
  local_8 = in_ECX;
  if (param_2 == 0) {
    *(undefined1 *)(param_1 + 0x4c) = 1;
    puVar2 = (undefined4 *)FUN_004b02a8(0x18);
    if (puVar2 != (undefined4 *)0x0) {
      FUN_004116f4(puVar2);
      *puVar2 = &PTR_FUN_004b700c;
    }
    *(undefined4 **)(param_1 + 0x44) = puVar2;
  }
  else {
    *(int *)(param_1 + 0x44) = param_2;
  }
  iVar3 = FUN_004b02a8(0x1c);
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = FUN_00411cbc(iVar3,*(undefined4 *)(param_1 + 0x44));
  }
  *(undefined4 *)(param_1 + 0x48) = uVar4;
  *(undefined4 *)(param_1 + 0x4e) = param_3;
  *(undefined4 *)(param_1 + 0x52) = param_4;
  if (param_5 != (char *)0x0) {
    iVar3 = strlen(param_5);
    pcVar5 = (char *)malloc(iVar3 + 1);
    *(char **)(param_1 + 0x56) = pcVar5;
    if (pcVar5 == (char *)0x0) {
      return -4;
    }
    uVar8 = 0xffffffff;
    pcVar10 = param_5;
    do {
      pcVar11 = pcVar10;
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      pcVar11 = pcVar10 + 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar11;
    } while (cVar1 != '\0');
    uVar8 = ~uVar8;
    pcVar10 = pcVar11 + -uVar8;
    for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)pcVar5 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar5 = pcVar5 + 4;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *pcVar5 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar5 = pcVar5 + 1;
    }
  }
  if (*(int *)(param_1 + 0x4e) == 0) {
    iVar3 = FUN_0041287c(param_1,param_5);
  }
  else {
    iVar3 = FUN_0041244c(*(int *)(param_1 + 0x4e),param_5,&local_8);
    if (iVar3 == 0) {
      return -2;
    }
    iVar6 = fopen(s_tmp_sct_004b6fec,&DAT_004b6ff4);
    if (iVar6 == 0) {
      free(iVar3);
      return -2;
    }
    iVar7 = FUN_004aa518(iVar3,1,local_8,iVar6);
    if (iVar7 != local_8) {
      free(iVar3);
      fclose(iVar6);
      thunk_FUN_004ad1a4(s_tmp_sct_004b6fec);
      return -1;
    }
    free(iVar3);
    fclose(iVar6);
    iVar3 = FUN_0041287c(param_1,s_tmp_sct_004b6fec);
    thunk_FUN_004ad1a4(s_tmp_sct_004b6fec);
  }
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  return iVar3;
}

