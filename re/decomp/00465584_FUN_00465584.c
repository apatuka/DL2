// FUN_00465584 @ 00465584 size=43 sig=undefined FUN_00465584() cc=unknown
// callers: @CampaignNumDialog$qqspvuiuil,@EditTileResourcesDialog$qqspvuiuil,@EditTerritoryResourcesDialog$qqspvuiuil
// callees: GetWindowLongA,SetBkMode

undefined4 FUN_00465584(HDC param_1,HWND param_2)

{
  LONG LVar1;
  undefined4 uVar2;
  
  LVar1 = GetWindowLongA(param_2,-0xc);
  if (LVar1 < 10) {
    uVar2 = 0;
  }
  else {
    SetBkMode(param_1,1);
    uVar2 = DAT_0058f1bc;
  }
  return uVar2;
}

