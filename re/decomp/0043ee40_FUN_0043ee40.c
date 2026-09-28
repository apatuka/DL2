// FUN_0043ee40 @ 0043ee40 size=77 sig=undefined FUN_0043ee40() cc=unknown
// callers: FUN_00459948,FUN_0045a50c,FUN_00459a3c,FUN_0045bf78,FUN_0045deb0,FUN_0044081c,FUN_0045a6e4,FUN_0045a8a4,FUN_0045a3e4
// callees: 

void FUN_0043ee40(int param_1,int param_2,int *param_3,int *param_4)

{
  *param_3 = (param_1 - param_2) * 0x20 + DAT_004c4a58 * -0x20 + DAT_004c5458;
  *param_4 = (param_2 + param_1) * 0x10 + DAT_004c4a5c * -0x20 + DAT_004c545c + 0x20;
  return;
}

