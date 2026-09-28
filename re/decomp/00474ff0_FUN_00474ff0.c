// FUN_00474ff0 @ 00474ff0 size=71 sig=undefined FUN_00474ff0() cc=unknown
// callers: FUN_0045e554
// callees: FUN_00474f5c,FUN_004779c0,FUN_00474d90

undefined4 FUN_00474ff0(undefined4 param_1)

{
  undefined4 uVar1;
  
  if (DAT_0058f1fc == 0) {
    FUN_00474f5c(param_1,DAT_0059f154);
    uVar1 = 1;
  }
  else {
    FUN_004779c0(param_1,0x38,DAT_0059f154,0,0,0,0);
    uVar1 = FUN_00474d90(0x38,param_1);
  }
  return uVar1;
}

