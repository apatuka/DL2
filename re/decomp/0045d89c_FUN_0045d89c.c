// FUN_0045d89c @ 0045d89c size=231 sig=undefined FUN_0045d89c() cc=unknown
// callers: FUN_0044a750
// callees: FUN_0043edd8,FUN_00459ea8,FUN_0045bf78

undefined4 FUN_0045d89c(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int local_c;
  int local_8;
  
  DAT_00583d8c = 0xffffffff;
  DAT_00583d94 = 0xffffffff;
  DAT_00583d88 = -1;
  DAT_00583d90 = -1;
  if (DAT_004d5ad0 == 0) {
    FUN_00459ea8(param_1,param_2,&local_8,&local_c);
  }
  else {
    FUN_0043edd8(param_1,param_2,&local_8,&local_c);
  }
  if ((((local_8 < 0) || (DAT_004d5b1a <= local_8)) || (local_c < 0)) || (DAT_004d5b1b <= local_c))
  {
    uVar1 = 0;
  }
  else {
    DAT_00583d88 = (int)(short)(&DAT_005a0552)[local_c * 200 + local_8 * 5];
    DAT_00583d90 = FUN_0045bf78(local_8,local_c,param_1,param_2,1);
    DAT_00583d84 = DAT_00583d90 != -1;
    uVar1 = 1;
  }
  return uVar1;
}

