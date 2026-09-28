// HdxArchive_Open @ 00411e28 size=809 sig=undefined HdxArchive_Open() cc=unknown
// callers: OpenDataFiles,FUN_00467e58
// callees: fread,free,fclose,qsort,malloc,fopen,strlen,sprintf
// strings: \"%s.HDX\"|\"%s.HDD\"

/* Opens <name>.HDX/<name>.HDD, reads and sorts the entry table */

undefined4 HdxArchive_Open(int *param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char local_404 [1024];
  
  sprintf(local_404,s__s_HDX_004b6fcc,param_2);
  iVar2 = strlen(local_404);
  pcVar3 = (char *)malloc(iVar2 + 1);
  param_1[5] = (int)pcVar3;
  uVar6 = 0xffffffff;
  pcVar8 = local_404;
  do {
    pcVar9 = pcVar8;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar9 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar8 = pcVar9 + -uVar6;
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
  sprintf(local_404,s__s_HDD_004b6fd3,param_2);
  iVar2 = strlen(local_404);
  pcVar3 = (char *)malloc(iVar2 + 1);
  param_1[6] = (int)pcVar3;
  uVar6 = 0xffffffff;
  pcVar8 = local_404;
  do {
    pcVar9 = pcVar8;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar9 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar8 = pcVar9 + -uVar6;
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
  if (param_3 == 1) {
    iVar2 = fopen(param_1[6],&DAT_004b6fda);
    param_1[4] = iVar2;
    if (iVar2 == 0) {
      free(param_1[5]);
      free(param_1[6]);
      param_1[6] = 0;
      param_1[5] = 0;
      return 0;
    }
  }
  else {
    iVar2 = fopen(param_1[6],&DAT_004b6fdd);
    param_1[4] = iVar2;
    if (iVar2 == 0) {
      free(param_1[5]);
      free(param_1[6]);
      param_1[6] = 0;
      param_1[5] = 0;
      return 0;
    }
  }
  if (param_3 == 1) {
    iVar2 = fopen(param_1[5],&DAT_004b6fda);
    if (iVar2 == 0) {
      free(param_1[5]);
      free(param_1[6]);
      fclose(param_1[4]);
      param_1[4] = 0;
      param_1[6] = 0;
      param_1[5] = 0;
      return 0;
    }
    iVar4 = fread(param_1 + 1,4,1,iVar2);
    if (iVar4 != 1) {
      free(param_1[5]);
      free(param_1[6]);
      fclose(param_1[4]);
      fclose(iVar2);
      param_1[4] = 0;
      param_1[6] = 0;
      param_1[5] = 0;
      return 0;
    }
    iVar4 = malloc(param_1[1] * 0xe);
    *param_1 = iVar4;
    for (iVar4 = 0; iVar4 < param_1[1]; iVar4 = iVar4 + 1) {
      iVar5 = fread(iVar4 * 0xe + *param_1,1,8,iVar2);
      if (iVar5 != 8) {
        free(param_1[5]);
        free(param_1[6]);
        free(*param_1);
        fclose(param_1[4]);
        fclose(iVar2);
        param_1[4] = 0;
        *param_1 = 0;
        param_1[6] = 0;
        param_1[5] = 0;
        return 0;
      }
      iVar5 = *param_1;
      *(undefined1 *)(iVar5 + 8 + iVar4 * 0xe) = 0;
      iVar5 = fread(iVar4 * 0xe + iVar5 + 10,4,1,iVar2);
      if (iVar5 != 1) {
        free(param_1[5]);
        free(param_1[6]);
        free(*param_1);
        fclose(param_1[4]);
        fclose(iVar2);
        param_1[4] = 0;
        *param_1 = 0;
        param_1[6] = 0;
        param_1[5] = 0;
        return 0;
      }
    }
    fclose(iVar2);
    param_1[2] = param_1[1];
    param_1[3] = 1;
    qsort(*param_1,param_1[1],0xe,&LAB_00411d74);
  }
  else {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = param_3;
  }
  return 1;
}

