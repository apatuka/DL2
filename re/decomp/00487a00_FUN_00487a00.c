// FUN_00487a00 @ 00487a00 size=210 sig=undefined FUN_00487a00() cc=unknown
// callers: FUN_00423b20,FUN_004169e8
// callees: FUN_004493dc,FUN_00488074,FUN_004877c8,UpdateWindow,FUN_004880e0,FUN_00494def,FUN_004879f8,FUN_00482cec,FUN_004238c8,FUN_00482d3c,FUN_004a5af2

/* WARNING: Removing unreachable block (ram,0x00487b30) */
/* WARNING: Removing unreachable block (ram,0x00487b40) */
/* WARNING: Removing unreachable block (ram,0x00487b44) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00487a00(int param_1)

{
  undefined4 uVar1;
  
  FUN_00482cec();
  _DAT_005126d8 = 1;
  FUN_004879f8();
  FUN_004a5af2();
  FUN_004493dc(1);
  uVar1 = DAT_004d59b4;
  DAT_004d59b4 = 0x32;
  FUN_004877c8(DAT_004d5c28,0);
  if (DAT_004d5974 != (HWND)0x0) {
    UpdateWindow(DAT_004d5974);
  }
  FUN_00494def(0);
  if (0x11 < param_1 - 0x7dU) {
    FUN_004238c8();
    _DAT_005126d8 = 0;
    FUN_00494def(1);
    DAT_004d59b4 = uVar1;
    FUN_004493dc(0);
    FUN_00482d3c();
    return 0;
  }
                    /* WARNING: Could not emulate address calculation at 0x00487a6c */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(&DAT_00487a8b +
                      CONCAT31((int3)(param_1 - 0x7dU >> 8),FUN_004879fc[param_1]) * 4))();
  return uVar1;
}

