// FUN_0044a8bc @ 0044a8bc size=109 sig=undefined FUN_0044a8bc() cc=unknown
// callers: FUN_0044b168
// callees: FUN_0045bc10,FUN_0045dd18,FUN_00418e00

void FUN_0044a8bc(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  
  if (DAT_004c5bc9 != '\0') {
    if (DAT_004d59b4 == 0) {
      FUN_0045dd18(param_1,param_2);
    }
    else if (DAT_004d59b4 == 1) {
      FUN_0045bc10(param_1,param_2);
    }
    else if (DAT_004d59b4 == 0x22) {
      cVar1 = FUN_00418e00();
      if (cVar1 == '\0') {
        FUN_0045bc10(param_1,param_2);
      }
      else {
        FUN_0045dd18(param_1,param_2);
      }
    }
  }
  DAT_004c5bc9 = 0;
  return;
}

