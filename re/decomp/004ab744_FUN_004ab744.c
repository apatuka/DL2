// FUN_004ab744 @ 004ab744 size=98 sig=undefined FUN_004ab744() cc=unknown
// callers: 
// callees: FUN_004ab648,FUN_004ab710

int FUN_004ab744(int param_1,uint *param_2)

{
  uint uVar1;
  
  FUN_004ab648(param_2);
  if ((param_1 == -1) || ((int)param_2[2] < 0)) {
    param_1 = -1;
  }
  else {
    *(ushort *)((int)param_2 + 0x12) = *(ushort *)((int)param_2 + 0x12) & 0xffdf;
    if (param_2 + 5 != (uint *)*param_2) {
      uVar1 = param_2[2];
      param_2[2] = uVar1 + 1;
      if ((int)(uVar1 + 1) < 2) {
        *param_2 = (uint)(param_2 + 5);
      }
      else {
        *param_2 = *param_2 - 1;
        if (*param_2 < param_2[1]) {
          *param_2 = *param_2 + 1;
          param_2[2] = param_2[2] - 1;
        }
      }
    }
    *(char *)*param_2 = (char)param_1;
  }
  FUN_004ab710(param_2);
  return param_1;
}

