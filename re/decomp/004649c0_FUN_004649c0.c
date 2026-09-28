// FUN_004649c0 @ 004649c0 size=122 sig=undefined FUN_004649c0() cc=unknown
// callers: FUN_00458d28
// callees: FUN_0048c85e

undefined4 FUN_004649c0(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if ((param_4 < 0) || (param_5 < 0)) {
    uVar1 = 0;
  }
  else {
    local_14 = param_2;
    local_c = param_4 + param_2;
    local_10 = param_3;
    local_8 = param_5 + param_3;
    local_20 = 0;
    local_24 = 0;
    local_1c = param_4;
    local_18 = param_5;
    FUN_0048c85e(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c),param_1,&local_14,&local_24,
                 &DAT_0065e580,0,0);
    uVar1 = 1;
  }
  return uVar1;
}

