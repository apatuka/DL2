// FUN_004a6bf8 @ 004a6bf8 size=55 sig=undefined FUN_004a6bf8() cc=unknown
// callers: FUN_004aa828,FUN_004b1f50,FUN_004b1e64
// callees: 

void FUN_004a6bf8(char *param_1,char *param_2)

{
  char cVar1;
  
  while (((cVar1 = *param_2, *param_1 = cVar1, cVar1 != '\0' &&
          (cVar1 = param_2[1], param_1[1] = cVar1, cVar1 != '\0')) &&
         (cVar1 = param_2[2], param_1[2] = cVar1, cVar1 != '\0'))) {
    cVar1 = param_2[3];
    param_2 = param_2 + 4;
    param_1[3] = cVar1;
    if (cVar1 == '\0') {
      return;
    }
    param_1 = param_1 + 4;
  }
  return;
}

