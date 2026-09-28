// FUN_0044a7c8 @ 0044a7c8 size=109 sig=undefined FUN_0044a7c8() cc=unknown
// callers: FUN_0044ad14
// callees: FUN_0045be7c,FUN_0045d984,FUN_00418e00

void FUN_0044a7c8(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  if (DAT_004c5bc8 != '\0') {
    if (DAT_004d59b4 == 0) {
      FUN_0045d984(param_1,param_2);
    }
    else if (DAT_004d59b4 == 1) {
      FUN_0045be7c(param_1,param_2);
    }
    else if (DAT_004d59b4 == 0x22) {
      cVar1 = FUN_00418e00();
      if (cVar1 == '\0') {
        FUN_0045be7c(param_1,param_2);
      }
      else {
        FUN_0045d984(param_1,param_2);
      }
    }
  }
  DAT_004c5bc8 = 0;
  return;
}

