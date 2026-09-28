// FUN_00465540 @ 00465540 size=66 sig=undefined FUN_00465540() cc=unknown
// callers: @ProgressDialog$qqspvuiuil,@PlayerNameDialog$qqspvuiuil,@DebugMinisterDialog$qqspvuiuil,@TaskForceDialog$qqspvuiuil,@CheatTechDialog$qqspvuiuil,@CampaignNumDialog$qqspvuiuil,@TransferDialog$qqspvuiuil,@EditTileResourcesDialog$qqspvuiuil,@DebugJobsDialog$qqspvuiuil,@GameStyleDialog$qqspvuiuil,@EditTerritoryResourcesDialog$qqspvuiuil
// callees: SetBkMode,FUN_0046534c,GetStockObject,GetClientRect

void FUN_00465540(HDC param_1,HWND param_2,undefined4 param_3)

{
  tagRECT local_14;
  
  GetClientRect(param_2,&local_14);
  SetBkMode(param_1,1);
  FUN_0046534c(param_1,param_3,&local_14,0x80,0x40);
  GetStockObject(5);
  return;
}

