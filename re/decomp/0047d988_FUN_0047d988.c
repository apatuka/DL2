// FUN_0047d988 @ 0047d988 size=109 sig=undefined FUN_0047d988() cc=unknown
// callers: FUN_0047da24
// callees: 

undefined4 FUN_0047d988(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((((param_1 < 0) || (DAT_004d5b1a <= param_1)) || (param_2 < 0)) ||
     (((DAT_004d5b1b <= param_2 ||
       ((&DAT_005a4400)[(short)(&DAT_005a0552)[param_2 * 200 + param_1 * 5] * 0x56e] == 0)) ||
      ((char)(&DAT_005a43f0)[(short)(&DAT_005a0552)[param_2 * 200 + param_1 * 5] * 0xadc] !=
       DAT_0058f1f4)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

