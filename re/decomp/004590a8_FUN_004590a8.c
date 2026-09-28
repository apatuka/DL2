// FUN_004590a8 @ 004590a8 size=44 sig=undefined FUN_004590a8() cc=unknown
// callers: FUN_0044ac18,FUN_0044ad14
// callees: FUN_00459068

void FUN_004590a8(undefined4 param_1,undefined4 param_2)

{
  char in_DL;
  
  DAT_004d1c7c = 0;
  if (DAT_00583d54 != (code *)0x0) {
    in_DL = (*DAT_00583d54)(param_1,param_2);
  }
  if (in_DL != '\0') {
    FUN_00459068();
  }
  return;
}

