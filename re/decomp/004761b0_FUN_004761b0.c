// FUN_004761b0 @ 004761b0 size=100 sig=undefined FUN_004761b0() cc=unknown
// callers: FUN_0041d2bc,FUN_0041d188,FUN_0041db10,FUN_0041d414
// callees: FUN_0044c3fc,FUN_004779c0,FUN_00474d90

void FUN_004761b0(int param_1,undefined2 *param_2,uint *param_3,undefined4 param_4)

{
  if (DAT_0058f1fc == 0) {
    FUN_0044c3fc(param_2,param_3,param_4);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x19,*param_2,param_3[1] << 8 | *param_3,
                 param_3[3] << 8 | param_3[2],param_3[4],(int)(short)(char)param_4);
    FUN_00474d90(0x19,(int)*(char *)(param_1 + 0x20));
  }
  return;
}

