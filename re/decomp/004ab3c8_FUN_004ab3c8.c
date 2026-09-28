// FUN_004ab3c8 @ 004ab3c8 size=95 sig=undefined FUN_004ab3c8() cc=unknown
// callers: FUN_004a9fa0
// callees: FUN_004aa418,FUN_004ab648,FUN_004ab710,FUN_004a9b5c

undefined4 FUN_004ab3c8(int param_1,undefined4 param_2,int param_3,uint param_4)

{
  undefined4 uVar1;
  
  if ((((char)param_1 == *(char *)(param_1 + 0x17)) && (param_3 < 3)) && (param_4 < 0x80000000)) {
    FUN_004ab648(param_1);
    if (*(int *)(param_1 + 8) != 0) {
      FUN_004aa418(param_1,0,1);
    }
    uVar1 = FUN_004a9b5c(param_1,param_2,param_3,param_4);
    FUN_004ab710(param_1);
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

