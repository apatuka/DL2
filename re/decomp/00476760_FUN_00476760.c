// FUN_00476760 @ 00476760 size=101 sig=undefined FUN_00476760() cc=unknown
// callers: FUN_00437718,FUN_00407864
// callees: FUN_00472448,FUN_004779c0,FUN_00474d90

void FUN_00476760(int param_1,int param_2,int param_3,undefined4 param_4,uint param_5)

{
  if (DAT_0058f1fc == 0) {
    FUN_00472448(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x2a,
                 (int)(short)(*(short *)(param_1 + 0x1a) << 8 | *(ushort *)(param_2 + 0x1a)),param_4
                 ,param_5 | param_3 << 8,0,0);
    FUN_00474d90(0x2a,(int)*(char *)(param_1 + 0x20));
  }
  return;
}

