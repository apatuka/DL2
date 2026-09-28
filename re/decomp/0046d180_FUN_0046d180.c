// FUN_0046d180 @ 0046d180 size=91 sig=undefined FUN_0046d180() cc=unknown
// callers: @GameStyleDialog$qqspvuiuil,@CampaignNumDialog$qqspvuiuil,FUN_00484980,@DebugMinisterDialog$qqspvuiuil,@PlayerNameDialog$qqspvuiuil,@ProgressDialog$qqspvuiuil
// callees: GetWindowRect,SetWindowPos

void FUN_0046d180(HWND param_1)

{
  uint uVar1;
  int X;
  tagRECT local_14;
  
  GetWindowRect(param_1,&local_14);
  uVar1 = DAT_0058f1c0 - (local_14.right - local_14.left);
  X = (int)uVar1 >> 1;
  if (X < 0) {
    X = X + (uint)((uVar1 & 1) != 0);
  }
  SetWindowPos(param_1,(HWND)0x0,X,(DAT_0058f1c4 - (local_14.bottom - local_14.top)) / 3,0,0,9);
  return;
}

