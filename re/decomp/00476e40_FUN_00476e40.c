// FUN_00476e40 @ 00476e40 size=64 sig=undefined FUN_00476e40() cc=unknown
// callers: CheckSubInfo
// callees: FUN_00474d90,FUN_004779c0,FUN_00435f5c

void FUN_00476e40(char *param_1,undefined4 param_2)

{
  if (DAT_0058f1fc == 0) {
    FUN_00435f5c(param_1,param_2);
  }
  else {
    FUN_004779c0((int)*param_1,0x2e,param_2,0,0,0,0);
    FUN_00474d90(0x2e,(int)*param_1);
  }
  return;
}

