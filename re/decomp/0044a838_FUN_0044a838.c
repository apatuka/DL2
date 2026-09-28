// FUN_0044a838 @ 0044a838 size=130 sig=undefined FUN_0044a838() cc=unknown
// callers: FUN_0044b0d4
// callees: FUN_0045dc48,FUN_0045bb34,FUN_00418e00

void FUN_0044a838(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  DAT_004c5bc9 = 0;
  if (DAT_004d59b4 == 0) {
    DAT_004c5bc9 = FUN_0045dc48(param_1,param_2);
  }
  else if (DAT_004d59b4 == 1) {
    DAT_004c5bc9 = FUN_0045bb34(param_1,param_2);
  }
  else if ((DAT_004d59b4 == 0x22) && (DAT_005332b0 == '\0')) {
    cVar1 = FUN_00418e00();
    if (cVar1 == '\0') {
      DAT_004c5bc9 = FUN_0045bb34(param_1,param_2);
    }
    else {
      DAT_004c5bc9 = FUN_0045dc48(param_1,param_2);
    }
  }
  return;
}

