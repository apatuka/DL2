// FUN_004743d0 @ 004743d0 size=293 sig=undefined FUN_004743d0() cc=unknown
// callers: FUN_0047425c,FUN_0047450c,FUN_004745b0
// callees: FUN_0044e9e4,SetDlgItemInt

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004743d0(HWND param_1,undefined1 param_2)

{
  switch(param_2) {
  case 0:
    _DAT_00653484 = FUN_0044e9e4(DAT_00657de0,DAT_006534c0,0xc,100,1);
    SetDlgItemInt(param_1,0xc9,_DAT_00653484,0);
    break;
  case 1:
    _DAT_0065348c = FUN_0044e9e4(DAT_00657de0,DAT_006534c0,0xf,100,1);
    SetDlgItemInt(param_1,0xcb,_DAT_0065348c,0);
    break;
  case 2:
    _DAT_00653494 = FUN_0044e9e4(DAT_00657de0,DAT_006534c0,4,100,1);
    SetDlgItemInt(param_1,0xcd,_DAT_00653494,0);
    break;
  case 3:
    _DAT_00653488 = FUN_0044e9e4(DAT_00657de0,DAT_006534c0,0xd,100,1);
    SetDlgItemInt(param_1,0xca,_DAT_00653488,0);
    break;
  case 4:
    _DAT_00653490 = FUN_0044e9e4(DAT_00657de0,DAT_006534c0,3,100,1);
    SetDlgItemInt(param_1,0xcc,_DAT_00653490,0);
  }
  return;
}

