// FUN_00476dcc @ 00476dcc size=64 sig=undefined FUN_00476dcc() cc=unknown
// callers: CheckSubTech
// callees: FUN_00474d90,FUN_00431f6c,FUN_004779c0

void FUN_00476dcc(char *param_1,undefined4 param_2)

{
  if (DAT_0058f1fc == 0) {
    FUN_00431f6c(param_1,param_2);
  }
  else {
    FUN_004779c0((int)*param_1,0x2d,param_2,0,0,0,0);
    FUN_00474d90(0x2d,(int)*param_1);
  }
  return;
}

