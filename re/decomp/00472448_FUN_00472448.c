// FUN_00472448 @ 00472448 size=304 sig=undefined FUN_00472448() cc=unknown
// callers: FUN_004766e8,FUN_00476760
// callees: FUN_004727dc,FUN_00482f94,memset,FUN_00472334

undefined4 FUN_00472448(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int local_34 [11];
  int local_8;
  
  if (*(char *)(param_1 + 0x20) != -1) {
    memset(local_34,0,0x2c);
    iVar1 = FUN_004727dc(param_1,param_2);
    if ((int)(&DAT_0059f16c)[*(char *)(param_2 + 0x20) * 0xb6] < (iVar1 + param_5) * param_4) {
      if (param_5 + iVar1 < 1) {
        param_4 = (&DAT_0059f16c)[*(char *)(param_2 + 0x20) * 0xb6];
      }
      else {
        param_4 = (int)(&DAT_0059f16c)[*(char *)(param_2 + 0x20) * 0xb6] / (param_5 + iVar1);
      }
    }
    if (param_4 == 0) {
      return 0;
    }
    local_8 = (iVar1 + param_5) * param_4;
    local_34[param_3] = param_4;
    iVar1 = FUN_00472334(param_1,param_2,local_34);
    if (iVar1 != 0) {
      if (local_8 <= (int)(&DAT_0059f16c)[*(char *)(param_2 + 0x20) * 0xb6]) {
        (&DAT_0059f16c)[*(char *)(param_2 + 0x20) * 0xb6] =
             (&DAT_0059f16c)[*(char *)(param_2 + 0x20) * 0xb6] - local_8;
      }
      (&DAT_0059f16c)[*(char *)(param_1 + 0x20) * 0xb6] =
           (&DAT_0059f16c)[*(char *)(param_1 + 0x20) * 0xb6] + param_4 * param_5;
      FUN_00482f94(PTR_DAT_004d5988);
      return 1;
    }
  }
  return 0;
}

