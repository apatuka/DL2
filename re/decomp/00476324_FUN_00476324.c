// FUN_00476324 @ 00476324 size=69 sig=undefined FUN_00476324() cc=unknown
// callers: FUN_004105e8,CheckBuilding
// callees: FUN_0044c3e4,FUN_004779c0,FUN_00474d90

void FUN_00476324(int param_1,undefined4 param_2)

{
  if (DAT_0058f1fc == 0) {
    FUN_0044c3e4(param_1,param_2);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x1b,(int)*(short *)(param_1 + 0x1a),param_2,0,0,0);
    FUN_00474d90(0x1b,(int)*(char *)(param_1 + 0x20));
  }
  return;
}

