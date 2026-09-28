// FUN_00475ba4 @ 00475ba4 size=78 sig=undefined FUN_00475ba4() cc=unknown
// callers: FUN_0045b448
// callees: FUN_0044c2c0,FUN_004779c0,FUN_00474d90

void FUN_00475ba4(int param_1,undefined2 *param_2,undefined2 *param_3)

{
  if (DAT_0058f1fc == 0) {
    FUN_0044c2c0(param_1,param_2,param_3);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x1e,(int)*(short *)(param_1 + 0x1a),*param_2,
                 *param_3,0,0);
    FUN_00474d90(0x1e,(int)*(char *)(param_1 + 0x20));
  }
  return;
}

