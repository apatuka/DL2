// FUN_004aa0dc @ 004aa0dc size=212 sig=undefined FUN_004aa0dc() cc=unknown
// callers: FUN_004aa518
// callees: FUN_004aa718,FUN_004a9c80,FUN_004ac4cc,memcpy

uint FUN_004aa0dc(char *param_1,uint param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_2;
  if ((*(byte *)((int)param_3 + 0x12) & 8) == 0) {
    uVar2 = param_3[3];
    if ((uVar2 == 0) || (uVar2 < param_2)) {
      if ((param_3[3] == 0) || ((param_3[2] == 0 || (iVar1 = FUN_004a9c80(param_3), iVar1 == 0)))) {
        uVar2 = FUN_004ac4cc((int)*(char *)((int)param_3 + 0x16),param_1,param_2);
        if ((uVar2 == 0xffffffff) || (uVar2 < param_2)) {
          param_2 = 0;
        }
      }
      else {
        param_2 = 0;
      }
    }
    else {
      if (-1 < (int)(param_3[2] + param_2)) {
        if (param_3[2] == 0) {
          param_3[2] = -1 - uVar2;
        }
        else {
          iVar1 = FUN_004a9c80(param_3);
          if (iVar1 != 0) {
            return 0;
          }
        }
      }
      memcpy(*param_3,param_1,param_2);
      param_3[2] = param_3[2] + param_2;
      *param_3 = *param_3 + param_2;
    }
  }
  else {
    for (; uVar2 != 0; uVar2 = uVar2 - 1) {
      iVar1 = FUN_004aa718((int)*param_1,param_3);
      if (iVar1 == -1) {
        return 0;
      }
      param_1 = param_1 + 1;
    }
  }
  return param_2;
}

