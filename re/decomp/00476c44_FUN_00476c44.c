// FUN_00476c44 @ 00476c44 size=58 sig=undefined FUN_00476c44() cc=unknown
// callers: FUN_004073e4,FUN_00406dd8,FUN_00429464
// callees: FUN_004779c0,FUN_004767f0,FUN_00474d0c

void FUN_00476c44(undefined4 param_1,int param_2,undefined4 param_3)

{
  if (*(int *)(&DAT_006534fc + param_2 * 4) == 0) {
    FUN_004779c0(param_1,0x3e,param_3,param_1,param_2,0,0);
    FUN_00474d0c(0x3e);
  }
  else {
    FUN_004767f0(param_1,1);
  }
  return;
}

