// FUN_004aa0a8 @ 004aa0a8 size=52 sig=undefined FUN_004aa0a8() cc=unknown
// callers: InitDebugLogs,DumpGameOptions,DebugLog
// callees: FUN_004ab648,FUN_004ab834,FUN_004ab710

undefined4 FUN_004aa0a8(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  FUN_004ab648(param_1);
  uVar1 = FUN_004ab834(FUN_004aa0dc,param_1,param_2,&stack0x0000000c);
  FUN_004ab710(param_1);
  return uVar1;
}

