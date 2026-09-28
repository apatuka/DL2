// FUN_004762a8 @ 004762a8 size=84 sig=undefined FUN_004762a8() cc=unknown
// callers: FUN_00403858,FUN_0041d2bc,FUN_0041d188,CheckBuilding,FUN_004038c4,FUN_0041db10,FUN_0041d414
// callees: FUN_0044c44c,FUN_004779c0,FUN_00474d90

void FUN_004762a8(int param_1,undefined2 *param_2)

{
  if (DAT_0058f1fc == 0) {
    FUN_0044c44c(param_2,(int)(short)param_2[1],(int)(short)param_2[8]);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x1a,*param_2,(int)(short)param_2[1],
                 (int)(short)param_2[8],0,0);
    FUN_00474d90(0x1a,(int)*(char *)(param_1 + 0x20));
  }
  return;
}

