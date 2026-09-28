// FUN_00476448 @ 00476448 size=118 sig=undefined FUN_00476448() cc=unknown
// callers: FUN_00403e30,FUN_00403a10,FUN_0045b448,FUN_00406424,FUN_00406538,FUN_00403c04,FUN_0045c704
// callees: _MovePopulation,FUN_004779c0,FUN_00474d90

void FUN_00476448(int param_1,int param_2,uint param_3,int param_4,short param_5,short param_6)

{
  uint uVar1;
  
  if (param_4 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x4000;
  }
  if (DAT_0058f1fc == 0) {
    _MovePopulation(param_1,param_2,param_3,param_4,param_5,param_6);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x20,param_3 | uVar1,(int)*(short *)(param_1 + 0x1a)
                 ,(int)*(short *)(param_2 + 0x1a),(int)param_5,(int)param_6);
    FUN_00474d90(0x20,(int)*(char *)(param_1 + 0x20));
  }
  return;
}

