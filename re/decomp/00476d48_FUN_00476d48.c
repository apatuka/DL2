// FUN_00476d48 @ 00476d48 size=80 sig=undefined FUN_00476d48() cc=unknown
// callers: CheckSubUnit
// callees: FUN_00474d90,FUN_00474cfc,FUN_00431e58,FUN_004779c0

void FUN_00476d48(char *param_1,undefined4 param_2,undefined4 param_3)

{
  short sVar1;
  
  if (DAT_0058f1fc == 0) {
    sVar1 = FUN_00474cfc();
    FUN_00431e58(param_1,param_2,param_3,(int)sVar1);
  }
  else {
    FUN_004779c0((int)*param_1,0x2c,param_2,param_3,0,0,0);
    FUN_00474d90(0x2c,(int)*param_1);
  }
  return;
}

