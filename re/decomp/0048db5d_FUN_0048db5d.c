// FUN_0048db5d @ 0048db5d size=176 sig=undefined FUN_0048db5d() cc=unknown
// callers: FUN_0041585c,CheckExitSave,CheckSubRes,FUN_00424590,FUN_00426ab0,FUN_0043632c,FUN_00425364,FUN_0042d304,FUN_0043044c,CheckSubTech,FUN_00437668,FUN_00413eb4,FUN_00414870,FUN_00435ed0,FUN_00427440,FUN_0042bc50,FUN_00425268,FUN_004169e8,FUN_0042e7ec,FUN_00427da0,FUN_0048dc0d,FUN_00416474,FUN_0042ebb8,CheckBuildingList,FUN_00413784,FUN_00422f7c,CheckSubUnit,FUN_00415514,CheckSubInfo,UserMessageObject__CheckMessage,FUN_0041665c,FUN_00439e98,FUN_0042623c,CheckUnitList,FUN_0041edd8,FUN_0042e080,CheckTechDet,FUN_00428a50,FUN_0042d3dc,FUN_004219bc,FUN_004393e8,CheckMoveStuff,FUN_0041e81c,FUN_00431128,FUN_0042f04c,FUN_0041f544,FUN_00423f44,FUN_00436864,FUN_0042c328,FUN_00425ac4,FUN_0042ac68
// callees: FUN_004b185c,PeekMessageA,WaitMessage,TranslateMessage,FUN_0048d920,DispatchMessageA

void FUN_0048db5d(void)

{
  BOOL BVar1;
  int iVar2;
  tagMSG local_20;
  
  BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,1);
  if (BVar1 == 0) {
    if (DAT_0051b830 == 0) {
      while (DAT_0051b824 == 0) {
        WaitMessage();
        BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,1);
        if (BVar1 != 0) {
          if (local_20.message == 0x12) {
            FUN_004b185c(0);
            return;
          }
          TranslateMessage(&local_20);
          DispatchMessageA(&local_20);
        }
      }
    }
  }
  else {
    do {
      iVar2 = FUN_0048d920(local_20.hwnd,local_20.message,local_20.wParam,local_20.lParam);
      if (iVar2 == 0) {
        if (local_20.message == 0x12) {
          FUN_004b185c(0);
        }
        else {
          TranslateMessage(&local_20);
          DispatchMessageA(&local_20);
        }
      }
      BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,1);
    } while (BVar1 != 0);
  }
  return;
}

