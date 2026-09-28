// FUN_004aa380 @ 004aa380 size=57 sig=undefined FUN_004aa380() cc=unknown
// callers: FUN_0041287c
// callees: FUN_004ab648,FUN_004aa9c4,FUN_004ab710

undefined4 FUN_004aa380(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  FUN_004ab648(param_1);
  uVar1 = FUN_004aa9c4(FUN_004ac634,FUN_004ab744,param_1,param_2,&stack0x0000000c);
  FUN_004ab710(param_1);
  return uVar1;
}

