// FUN_004767f0 @ 004767f0 size=41 sig=undefined FUN_004767f0() cc=unknown
// callers: FUN_0047681c,FUN_0042a36c,FUN_0042ac2c,FUN_00437718,FUN_004073e4,FUN_00429464,FUN_00476b8c,FUN_00476c44,FUN_00406dd8,FUN_00407864,FUN_0047691c
// callees: FUN_004779c0

void FUN_004767f0(int param_1,undefined4 param_2)

{
  *(undefined4 *)(&DAT_006534fc + param_1 * 4) = param_2;
  FUN_004779c0(DAT_0058f1f4,0x28,param_1,param_2,0,0,0);
  return;
}

