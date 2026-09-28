// FUN_00498ccb @ 00498ccb size=77 sig=undefined FUN_00498ccb() cc=unknown
// callers: FUN_00498d22,FUN_00498d6f
// callees: 

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00498ccb(int *param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_0051e1d8;
  DAT_0051e1d8 = param_1;
  if (param_1 != (int *)0x0) {
    _DAT_0065ee1c = param_1 + 6;
    _DAT_0051e1dc = param_1[2];
    _DAT_0051e1d0 = *param_1;
    _DAT_0051e1d4 = *param_1 + param_1[1];
    DAT_0065ee18 = param_1[5];
  }
  return uVar1;
}

