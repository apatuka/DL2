// FUN_00426594 @ 00426594 size=71 sig=undefined FUN_00426594() cc=unknown
// callers: CheckUnitList,CheckColonyAssistant,CheckSubInfo,FUN_0043be98,FUN_00416474,FUN_0042e080,FUN_0041e81c,FUN_0042f5d8,CheckBuildingList,CheckExitSave,FUN_00437668,FUN_00428a50,UserMessageObject__CheckMessage,CheckArmy,CheckEventLog,CheckBuilding,FUN_004265dc,CheckSubUnit,FUN_00427440,FUN_0043baf4,FUN_00415514,CheckSubTech,CheckTechTree,FUN_0043044c,FUN_00436ef4,FUN_0041585c
// callees: FUN_00425ef8,FUN_00426140,FUN_004152ec,FUN_0042623c,FUN_004152e0,FUN_00425f58

void FUN_00426594(undefined4 param_1)

{
  int iVar1;
  
  FUN_004152e0();
  iVar1 = FUN_00425f58(param_1);
  if (iVar1 == 0) {
    FUN_004152ec();
  }
  else {
    FUN_00425ef8();
    DAT_004d8260 = 1;
    do {
      iVar1 = FUN_0042623c();
    } while (iVar1 == 0);
    FUN_00426140();
    DAT_004d8260 = 0;
  }
  return;
}

