// FUN_00445040 @ 00445040 size=48 sig=undefined FUN_00445040() cc=unknown
// callers: FUN_00454690,FUN_004543f8,FUN_00453ec8,FUN_00480be0,FUN_0043d184,FUN_004867d8,FUN_00454160,DrawSprite,DestroyAnim
// callees: 

void FUN_00445040(int param_1,undefined2 param_2,short param_3)

{
  *(undefined2 *)(param_1 + 0x2c) = param_2;
  if (param_3 != 0) {
    *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(&DAT_004d02f8 + *(short *)(param_1 + 2) * 0xc)
    ;
    *(undefined2 *)(param_1 + 0x1e) = 1;
  }
  return;
}

