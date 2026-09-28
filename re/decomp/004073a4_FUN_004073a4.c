// FUN_004073a4 @ 004073a4 size=63 sig=undefined FUN_004073a4() cc=unknown
// callers: 
// callees: FUN_00406dd8

void FUN_004073a4(int param_1,undefined4 param_2,int param_3)

{
  if ((-1 < *(int *)(&DAT_005220a4 + param_3 * 4 + param_1 * 0x1c)) &&
     ((1 << ((byte)param_3 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0)) {
    FUN_00406dd8(param_1,param_3);
  }
  return;
}

