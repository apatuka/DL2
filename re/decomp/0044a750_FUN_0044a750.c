// FUN_0044a750 @ 0044a750 size=120 sig=undefined FUN_0044a750() cc=unknown
// callers: FUN_0044ac18
// callees: FUN_0045d89c,FUN_00418e00,FUN_0045bd44

void FUN_0044a750(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  DAT_004c5bc8 = 0;
  if (DAT_004d59b4 == 0) {
    DAT_004c5bc8 = FUN_0045d89c(param_1,param_2);
  }
  else if (DAT_004d59b4 == 1) {
    DAT_004c5bc8 = FUN_0045bd44(param_1,param_2);
  }
  else if (DAT_004d59b4 == 0x22) {
    cVar1 = FUN_00418e00();
    if (cVar1 == '\0') {
      DAT_004c5bc8 = FUN_0045bd44(param_1,param_2);
    }
    else {
      DAT_004c5bc8 = FUN_0045d89c(param_1,param_2);
    }
  }
  return;
}

