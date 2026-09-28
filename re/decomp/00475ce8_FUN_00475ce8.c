// FUN_00475ce8 @ 00475ce8 size=88 sig=undefined FUN_00475ce8() cc=unknown
// callers: FUN_004487b8,FUN_0044c8ac,MoveLaborToHousing
// callees: FUN_004779c0,FUN_00474d90,FUN_0044c320

void FUN_00475ce8(int param_1,undefined2 *param_2,undefined4 param_3,undefined2 *param_4,
                 undefined4 param_5)

{
  if (DAT_0058f1fc == 0) {
    FUN_0044c320(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x1f,(int)*(short *)(param_1 + 0x1a),*param_2,
                 *param_4,param_3,param_5);
    FUN_00474d90(0x1f,(int)*(char *)(param_1 + 0x20));
  }
  return;
}

