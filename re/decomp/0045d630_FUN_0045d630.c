// FUN_0045d630 @ 0045d630 size=116 sig=undefined FUN_0045d630() cc=unknown
// callers: FUN_0044b058
// callees: FUN_00481a5c

undefined4 FUN_0045d630(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int local_c;
  int local_8;
  
  DAT_00583d8c = 0xffffffff;
  DAT_00583d94 = 0xffffffff;
  DAT_00583d88 = 0xffffffff;
  DAT_00583d90 = 0xffffffff;
  FUN_00481a5c(param_1,param_2,&local_8,&local_c);
  DAT_00583d8c = (int)(short)(&DAT_005a0552 + local_c * 200)[local_8 * 5];
  if (DAT_00583d8c == -1) {
    uVar1 = 0;
  }
  else {
    uVar1 = CONCAT31((int3)((uint)(&DAT_005a0552 + local_c * 200) >> 8),1);
  }
  return uVar1;
}

