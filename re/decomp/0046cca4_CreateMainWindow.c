// CreateMainWindow @ 0046cca4 size=364 sig=undefined CreateMainWindow() cc=unknown
// callers: WinMain
// callees: CreateGamePalette2,GetDC,FUN_00463a74,UpdateWindow,LoadAcceleratorsA,CreateWindowExA,FUN_00465640,ReleaseDC,CreateCompatibleDC,ShowWindow,memcpy,LoadBitmapA,CreateBrushIndirect,GetDeviceCaps
// strings: \"Deadlock 2: Shrine Wars\"|\"XenoMainWnd\"

/* Creates "Deadlock 2: Shrine Wars" main window */

undefined4 CreateMainWindow(int param_1)

{
  HDC hdc;
  undefined4 uVar1;
  LOGBRUSH local_10;
  
  DAT_0058f1a4 = CreateWindowExA(0,s_XenoMainWnd_004d594c,PTR_s_Deadlock_2__Shrine_Wars_0050983c,
                                 0x80000000,0,0,DAT_0058f1c0,DAT_0058f1c4,(HWND)0x0,(HMENU)0x0,
                                 DAT_0058f19c,(LPVOID)0x0);
  if (DAT_0058f1a4 == (HWND)0x0) {
    uVar1 = 0xfffe;
  }
  else {
    if (DAT_004d597c == (HDC)0x0) {
      DAT_004d597c = GetDC(DAT_0058f1a4);
    }
    CreateGamePalette2();
    hdc = GetDC((HWND)0x0);
    DAT_0058f1cc = GetDeviceCaps(hdc,0xc);
    DAT_0058f1c8 = GetDeviceCaps(hdc,0xe);
    ReleaseDC((HWND)0x0,hdc);
    DAT_0058f1b0 = CreateCompatibleDC(DAT_004d597c);
    DAT_0058f1b4 = FUN_00465640(DAT_0058f1a4,2);
    memcpy(&DAT_00590d9c,DAT_0058df48,0x2000);
    DAT_0058f1b8 = LoadBitmapA(DAT_0058f19c,(LPCSTR)0x37);
    local_10.lbStyle = DAT_004d5c18;
    local_10.lbColor = DAT_004d5c1c;
    local_10.lbHatch = (ULONG_PTR)DAT_0058f1b8;
    DAT_0058f1bc = CreateBrushIndirect(&local_10);
    DAT_0058f1a0 = LoadAcceleratorsA(DAT_0058f19c,(LPCSTR)0x190);
    ShowWindow(DAT_0058f1a4,param_1);
    UpdateWindow(DAT_0058f1a4);
    memcpy(&DAT_0051a8cc,&DAT_0051accc,0x3b0);
    FUN_00463a74();
    uVar1 = 0;
  }
  return uVar1;
}

