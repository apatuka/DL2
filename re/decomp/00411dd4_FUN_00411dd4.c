// FUN_00411dd4 @ 00411dd4 size=84 sig=undefined FUN_00411dd4() cc=unknown
// callers: OpenDataFiles
// callees: free,fclose

void FUN_00411dd4(int *param_1,byte param_2)

{
  if (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      free(*param_1);
    }
    if (param_1[4] != 0) {
      fclose(param_1[4]);
    }
    if (param_1[5] != 0) {
      free(param_1[5]);
    }
    if (param_1[6] != 0) {
      free(param_1[6]);
    }
    if ((param_2 & 1) != 0) {
      free(param_1);
    }
  }
  return;
}

