// FUN_004442dc @ 004442dc size=145 sig=undefined FUN_004442dc() cc=unknown
// callers: @WinGWndProc$qqspvuiuil,FUN_0044a2fc,FUN_00469250
// callees: FUN_00463da8,GetWindowLongA,SetWindowLongA,FUN_00463bcc,FUN_00464620,FUN_00463e04,FUN_00463aec

undefined4 FUN_004442dc(HWND param_1,uint param_2,int param_3)

{
  LONG LVar1;
  int dwNewLong;
  int iVar2;
  uint uVar3;
  
  LVar1 = GetWindowLongA(param_1,0xc);
  uVar3 = param_2 & 0xffff;
  param_2 = param_2 >> 0x10;
  if (LVar1 != 0) {
    FUN_00463aec(LVar1);
  }
  if ((((uVar3 != 0) && (param_2 != 0)) && (dwNewLong = FUN_00463e04(), dwNewLong != -1)) &&
     (iVar2 = FUN_00463bcc(dwNewLong,uVar3,param_2,param_3), iVar2 != 0)) {
    if (param_3 == 0) {
      FUN_00463da8(dwNewLong);
      FUN_00464620(0,0,uVar3,param_2,0,1);
      FUN_00463da8(1);
    }
    SetWindowLongA(param_1,0xc,dwNewLong);
    return 1;
  }
  return 0;
}

