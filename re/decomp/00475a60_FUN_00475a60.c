// FUN_00475a60 @ 00475a60 size=99 sig=undefined FUN_00475a60() cc=unknown
// callers: FUN_00403e30,FUN_0044d0e4,FUN_00408310,FUN_0045b094,FUN_00403ce8,FUN_00409e2c,FUN_0045b304
// callees: FUN_004779c0,FUN_00474d90,_DemolishBuilding

void FUN_00475a60(int param_1,undefined4 param_2,undefined4 param_3)

{
  if (DAT_0058f1fc == 0) {
    _DemolishBuilding(&DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8,param_1,param_2,param_3);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x16,(int)*(short *)(param_1 + 0x1a),param_2,param_3
                 ,0,0);
    FUN_00474d90(0x16,(int)*(char *)(param_1 + 0x20));
  }
  return;
}

