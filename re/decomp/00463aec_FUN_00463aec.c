// FUN_00463aec @ 00463aec size=224 sig=undefined FUN_00463aec() cc=unknown
// callers: FUN_00444370,FUN_00463bcc,FUN_00464b90,FUN_004442dc
// callees: FUN_0048d13d,FUN_0048c3f4,memset,FUN_0048c4ad

void FUN_00463aec(int param_1)

{
  if (*(int *)(&DAT_0058de34 + param_1 * 0x1c) != 0) {
    FUN_0048c4ad(*(int *)(&DAT_0058de34 + param_1 * 0x1c));
    if (*(short *)(*(int *)(&DAT_0058de34 + param_1 * 0x1c) + 0x24) != 0) {
      FUN_0048c3f4(*(undefined4 *)(&DAT_0058de34 + param_1 * 0x1c));
    }
    if (*(int *)(&DAT_0058de30 + param_1 * 0x1c) == 0) {
      FUN_0048d13d(*(undefined4 *)(&DAT_0058de34 + param_1 * 0x1c));
    }
    memset(&DAT_0058de1c + param_1 * 0x1c,0,0x1c);
    if (param_1 == DAT_00583e18) {
      DAT_00583e0c = 0;
      DAT_00583e10 = 0;
      DAT_00583e04 = 0;
      DAT_00583e18 = 0;
      memset(&DAT_0058df34,0,0x10);
      DAT_00559de8 = 0;
      DAT_00559dec = 0;
      DAT_00559df0 = 0;
      DAT_00559df4 = 0;
    }
  }
  return;
}

