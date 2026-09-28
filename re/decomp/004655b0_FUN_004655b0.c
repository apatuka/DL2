// FUN_004655b0 @ 004655b0 size=143 sig=undefined FUN_004655b0() cc=unknown
// callers: @ProgressDialog$qqspvuiuil,@PlayerNameDialog$qqspvuiuil,@DebugMinisterDialog$qqspvuiuil,@TaskForceDialog$qqspvuiuil,@CheatTechDialog$qqspvuiuil,@CampaignNumDialog$qqspvuiuil,@TransferDialog$qqspvuiuil,@EditTileResourcesDialog$qqspvuiuil,@DebugJobsDialog$qqspvuiuil,@GameStyleDialog$qqspvuiuil,@EditTerritoryResourcesDialog$qqspvuiuil
// callees: GetUpdateRect,FUN_00464f80,ReleaseDC,FUN_0046534c,GetDC,InvalidateRect,GetClientRect

undefined4 FUN_004655b0(HWND param_1)

{
  HDC hDC;
  tagRECT local_14;
  
  hDC = GetDC(param_1);
  GetUpdateRect(param_1,&local_14,0);
  if ((local_14.right == 0) || (local_14.bottom == 0)) {
    GetClientRect(param_1,&local_14);
    InvalidateRect(param_1,(RECT *)0x0,0);
  }
  FUN_0046534c(hDC,DAT_0058f1b4,&local_14,0x80,0x40);
  InvalidateRect(param_1,&local_14,0);
  GetClientRect(param_1,&local_14);
  FUN_00464f80(hDC,&local_14,1);
  ReleaseDC(param_1,hDC);
  return 1;
}

