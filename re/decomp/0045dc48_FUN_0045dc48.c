// FUN_0045dc48 @ 0045dc48 size=207 sig=undefined FUN_0045dc48() cc=unknown
// callers: FUN_0044a838,FUN_0045de90,FUN_0044a92c
// callees: FUN_0043edd8,FUN_00459ea8,FUN_0045bf78

undefined4 FUN_0045dc48(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int local_c;
  int local_8;
  
  DAT_00583d8c = -1;
  DAT_00583d94 = 0xffffffff;
  DAT_00583d88 = 0xffffffff;
  DAT_00583d90 = 0xffffffff;
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
    DAT_00583d8c = (int)(short)(&DAT_005a0552)[local_c * 200 + local_8 * 5];
    DAT_00583d94 = FUN_0045bf78(local_8,local_c,param_1,param_2,1);
    uVar1 = 1;
  }
  return uVar1;
}

