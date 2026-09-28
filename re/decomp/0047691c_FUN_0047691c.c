// FUN_0047691c @ 0047691c size=81 sig=undefined FUN_0047691c() cc=unknown
// callers: FUN_00407864,FUN_00437718
// callees: FUN_004779c0,FUN_004767f0,FUN_00474d0c

void FUN_0047691c(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  if (*(int *)(&DAT_006534fc + *(char *)(param_2 + 0x20) * 4) == 0) {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x29,param_3,(int)*(short *)(param_1 + 0x1a),
                 (int)*(short *)(param_2 + 0x1a),param_4,param_5);
    FUN_00474d0c(0x29);
  }
  else {
    FUN_004767f0((int)*(char *)(param_1 + 0x20),1);
  }
  return;
}

