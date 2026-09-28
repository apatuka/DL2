// FUN_004760d0 @ 004760d0 size=79 sig=undefined FUN_004760d0() cc=unknown
// callers: FUN_00420d34,FUN_0041d710
// callees: FUN_004779c0,FUN_00474d90,FUN_0044e0a8

void FUN_004760d0(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  if (DAT_0058f1fc == 0) {
    FUN_0044e0a8(param_1,param_2,param_3,param_4);
  }
  else {
    FUN_004779c0((int)*param_2,0x18,(int)(short)param_3,param_4,(int)*(short *)(param_1 + 0x1a),0,0)
    ;
    FUN_00474d90(0x18,(int)*param_2);
  }
  return;
}

