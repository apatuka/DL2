// FUN_00412154 @ 00412154 size=514 sig=undefined FUN_00412154() cc=unknown
// callers: OpenDataFiles
// callees: free,fclose,qsort,fopen,FUN_004aa518

undefined4 FUN_00412154(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_1[3] == 1) {
    fclose(param_1[4]);
    free(*param_1);
    free(param_1[5]);
    free(param_1[6]);
    param_1[4] = 0;
    *param_1 = 0;
    param_1[6] = 0;
    param_1[5] = 0;
  }
  else {
    fclose(param_1[4]);
    param_1[4] = 0;
    qsort(*param_1,param_1[1],0xe,&LAB_00411d74);
    iVar1 = fopen(param_1[5],&DAT_004b6fdd);
    if (iVar1 == 0) {
      free(*param_1);
      free(param_1[5]);
      free(param_1[6]);
      *param_1 = 0;
      param_1[6] = 0;
      param_1[5] = 0;
      return 0;
    }
    iVar2 = FUN_004aa518(param_1 + 1,4,1,iVar1);
    if (iVar2 != 1) {
      fclose(iVar1);
      free(*param_1);
      free(param_1[5]);
      free(param_1[6]);
      *param_1 = 0;
      param_1[6] = 0;
      param_1[5] = 0;
      return 0;
    }
    for (iVar2 = 0; iVar2 < param_1[1]; iVar2 = iVar2 + 1) {
      iVar3 = FUN_004aa518(iVar2 * 0xe + *param_1,1,8,iVar1);
      if (iVar3 != 8) {
        fclose(iVar1);
        free(*param_1);
        free(param_1[5]);
        free(param_1[6]);
        *param_1 = 0;
        param_1[6] = 0;
        param_1[5] = 0;
        return 0;
      }
      iVar3 = FUN_004aa518(iVar2 * 0xe + *param_1 + 10,4,1,iVar1);
      if (iVar3 != 1) {
        fclose(iVar1);
        free(*param_1);
        free(param_1[5]);
        free(param_1[6]);
        *param_1 = 0;
        param_1[6] = 0;
        param_1[5] = 0;
        return 0;
      }
    }
    fclose(iVar1);
    free(*param_1);
    free(param_1[5]);
    free(param_1[6]);
    *param_1 = 0;
    param_1[6] = 0;
    param_1[5] = 0;
  }
  return 1;
}

