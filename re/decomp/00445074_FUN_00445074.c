// FUN_00445074 @ 00445074 size=106 sig=undefined FUN_00445074() cc=unknown
// callers: FUN_00444b74,FUN_00444fd4,FUN_00445270,FUN_0043d184,FUN_004451d4
// callees: 

void FUN_00445074(int param_1,int param_2,int param_3,int param_4)

{
  if ((param_1 < DAT_00561a20) || (DAT_00561a20 == DAT_00561a28)) {
    DAT_00561a20 = param_1;
  }
  if (DAT_00561a28 < param_3 + param_1) {
    DAT_00561a28 = param_3 + param_1;
  }
  if ((param_2 < DAT_00561a24) || (DAT_00561a24 == DAT_00561a2c)) {
    DAT_00561a24 = param_2;
  }
  if (DAT_00561a2c < param_4 + param_2) {
    DAT_00561a2c = param_4 + param_2;
  }
  return;
}

