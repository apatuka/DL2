// WinMain @ 00470804 size=1980 sig=undefined WinMain() cc=unknown
// callers: 
// callees: FUN_004238c8,FUN_0043aa88,FUN_0046f0e0,OpenDataFiles,InitDebugLogs,FUN_00485668,FUN_00486964,FUN_0044b9e4,GetDeviceCaps,SyncBeginTurn,FUN_004842e4,TestMemory,InitHelp,GetNetGameOptions,FUN_00414a30,FUN_00482f6c,FUN_0046ac44,FUN_00414e74,timeGetTime,LoadSmacker,FUN_00478090,FUN_0046c7d4,FUN_0046fa7c,FUN_00427f04,FUN_00450b20,CalculatePlayersScores,FUN_00436064,FUN_004a5b1c,SeaManipulationEffects,FUN_0046ce10,FUN_0049117e,ResetVariables,FUN_0046fae4,FUN_00445710,GetDC,FUN_00486910,FUN_0046c9f8,FUN_00427eb4,FUN_0044cabc,FUN_004579a4,SetForegroundWindow,FUN_0046c780,DumpGameOptions,FUN_00494def,DebugLog,LoadPrefsAndInit,FUN_004b3dbc,InitCYGame,FindWindowA,FUN_004ae594,FUN_004152ec,FUN_0046fa54,FUN_004152e0,FUN_0046ca60,FUN_00457624,FUN_004360ec,AutoSave,FUN_004589a0,ShutdownGame,FUN_0042836c,FreeSmacker,SavePrefs,CreateRandomEvents,XenoIntro,SynchronizeGame,PreloadSprite2,GetGameOptions,FUN_0047c730,FUN_00458a5c,WaitSync,FUN_00465e20,FUN_00477f98,FUN_00482b38,FUN_00471b3c,FUN_00427ee8,FUN_0045add0,FUN_0046f5d4,FUN_0046cc14,RegisterWindowClasses,FUN_00436098,FUN_0046eea0,FUN_00441400,FUN_0046c1a8,FUN_004149fc,FUN_00482f3c,RaceInit,FUN_0046f804,FUN_00405378,FUN_0046ee88,ReleaseDC,RunAITurns,FUN_0044a000,FUN_004878a8,FUN_004658a8,FUN_0046f938,FUN_0046e730,FUN_0046cc6c,FUN_0046e338,FUN_00486e34,FUN_0046cc00,FUN_00441a44,CreateMainWindow
// strings: \"XenoMainWnd\"|\"GetDeviceCaps\"|\"Deadlock 2 is designed to run with at least 256-colors and may look odd with your current settings.\\n\\nSet the number of screen colors by using the windows setup program, control panel, or your video card configuration program.\"|\"Possible display problems\"|\"Intro\"|\"FreeSmacker\"|\"LoadSmacker\"|\"TestMemory\"|\"InitHelp\"|\"PreloadSprite2\"|\"ResetVariables\"|\"GetGameOptions\"|\"All players are now being synchronized.  This may take some time.  Please wait...\"|\"Re-synching Machines\"|\"WndMain--SynchronizeGame After LogisticsPhase\"|\"WndMain--Before SynchronizeGame at end of turn\"|\"WndMain--After SynchronizeGame at end of turn\"

/* Main entry: window creation, game loop (turn loop with debug log tags) */

undefined4 WinMain(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  HWND hWnd;
  undefined4 uVar2;
  int iVar3;
  DWORD DVar4;
  HDC hdc;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 local_cc [120];
  undefined1 local_54 [4];
  undefined1 local_50 [76];
  
  DAT_0058f19c = param_1;
  hWnd = FindWindowA(s_XenoMainWnd_004d594c,(LPCSTR)0x0);
  if (hWnd == (HWND)0x0) {
    InitDebugLogs();
    FUN_00458a5c();
    iVar3 = FUN_0046fa7c(param_3,local_50,0x14);
    iVar3 = FUN_0046fae4(iVar3 + 1,local_54);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else {
      FUN_0046cc14();
      (*(code *)PTR_FUN_004d5c14)(param_1);
      FUN_00441a44();
      FUN_00477f98();
      if ((param_2 == 0) && (iVar3 = RegisterWindowClasses(param_1), iVar3 == 0)) {
        return 0xffffffff;
      }
      sVar1 = FUN_0046cc6c(param_1);
      if (sVar1 == 0) {
        DVar4 = timeGetTime();
        FUN_0046ca60(DVar4);
        sVar1 = CreateMainWindow(param_4);
        if (sVar1 == 0) {
          iVar3 = InitCYGame(param_1,DAT_0058f1a4);
          if (iVar3 == 0) {
            uVar2 = 0xffffffff;
          }
          else {
            DebugLog(s_GetDeviceCaps_004d5e2c);
            hdc = GetDC((HWND)0x0);
            iVar3 = GetDeviceCaps(hdc,0x18);
            if (iVar3 == 0x10) {
              FUN_0042836c(PTR_s_Possible_display_problems_00509834,
                           PTR_s_Deadlock_2_is_designed_to_run_wi_00509838,4,0,0);
            }
            ReleaseDC((HWND)0x0,hdc);
            FUN_00465e20();
            DebugLog(s_Intro_004d5e3a);
            FUN_00494def(0);
            iVar3 = LoadPrefsAndInit();
            if (iVar3 == 0) {
              FUN_00494def(1);
              DebugLog(s_FreeSmacker_004d5e40);
              FreeSmacker();
              DebugLog(s_LoadSmacker_004d5e4c);
              LoadSmacker();
              uVar2 = FUN_004b3dbc(0);
              FUN_004ae594(uVar2);
              iVar3 = OpenDataFiles();
              if (iVar3 == 0) {
                uVar2 = 0xfffffffc;
              }
              else {
                FUN_0046c9f8();
                if (DAT_004d5ab0 != 0) {
                  FUN_00482f6c((DAT_004d5adc * 3000) / 100 + -3000);
                }
                if (DAT_004d5aac != 0) {
                  FUN_00482f3c((DAT_004d5ad8 * 3000) / 100 + -3000);
                }
                while (DAT_0058f1f0 == 0) {
                  if (DAT_004d5ab0 == 0) {
                    FUN_00482f6c(0xffffd8f0);
                  }
                  if (DAT_004d5aac == 0) {
                    FUN_00482f3c(0xffffd8f0);
                  }
                  DAT_004d59b4 = 0x32;
                  XenoIntro();
                  if (DAT_004d59b4 != 0x2a) {
                    FUN_00436098();
                    FUN_00436064();
                  }
                  DebugLog(s_TestMemory_004d5e58);
                  TestMemory();
                  DebugLog(s_InitHelp_004d5e63);
                  InitHelp();
                  DebugLog(s_PreloadSprite2_004d5e6c);
                  PreloadSprite2();
                  if (DAT_004d5aa0 == '\0') {
                    FUN_00482b38(1,0);
                  }
                  DebugLog(s_ResetVariables_004d5e7b);
                  ResetVariables(1);
                  GetNetGameOptions();
                  FUN_004579a4();
                  DebugLog(s_GetGameOptions_004d5e8a);
                  iVar3 = GetGameOptions();
                  if (iVar3 == 0) break;
                  if (((DAT_004d598c == 0) && (DAT_0058f1ec == 0)) &&
                     (RaceInit(), DAT_0058f1ec == 0)) {
                    FUN_0046e730(0);
                    FUN_0046f5d4();
                    DAT_0059f154 = 1;
                  }
                  DumpGameOptions();
                  if (DAT_0058f1ec == 0) {
                    if (DAT_004d59b4 != 0x2a) {
                      FUN_00436098();
                    }
                    if (DAT_004d598c == 0) {
                      FUN_00486910(0);
                      FUN_004842e4();
                    }
                    FUN_00486964();
                    FUN_0046c1a8(1);
                    FUN_0046e338();
                    FUN_0043aa88();
                    if (DAT_004d59b4 == 0x2a) {
                      FUN_004360ec();
                    }
                    DAT_004d59b4 = 0;
                    FUN_004a5b1c();
                    FUN_0044a000();
                    FUN_004152e0();
                    uVar6 = 1;
                    uVar5 = 0x37333044;
                    uVar2 = FUN_0049117e(0,0x54415453,0);
                    uVar2 = FUN_00414a30(0,uVar2,uVar5,uVar6);
                    FUN_00414e74();
                    FUN_004658a8();
                    FUN_004149fc(uVar2,1);
                    FUN_004152ec();
                    FUN_00450b20();
                    if (DAT_004d598c == 0) {
                      FUN_004238c8();
                    }
                    if (DAT_004d5aa0 == '\0') {
                      FUN_00482b38(2,0);
                    }
                    DAT_004d59a8 = 0;
                  }
                  DAT_004d59bc = 1;
                  while (DAT_0058f1ec == 0) {
                    iVar3 = FUN_0045add0();
                    if ((iVar3 == 1) && (DAT_004d5a50 != 0)) {
                      FUN_00478090();
                    }
                    if ((DAT_0058f1fc == 0) && (DAT_004d5b34 != 0)) {
                      DAT_004d5b34 = 0;
                    }
                    if (DAT_004d598c == 0) {
                      CreateRandomEvents();
                    }
                    FUN_004589a0(&DAT_004d5e99);
                    FUN_004589a0(&DAT_004d5e9d);
                    SyncBeginTurn(DAT_0059f154);
                    if (DAT_0058f1ec == 0) {
                      FUN_004152ec();
                      if (DAT_004d598c == 0) {
                        FUN_00471b3c();
                      }
                      FUN_004589a0(&DAT_004d5ea1);
                      FUN_0046f804();
                      FUN_004589a0(s_SyncBeginTurn1_004d5ca6 + 0xd);
                      FUN_0046c780();
                      FUN_004589a0(s_SyncBeginTurn2_004d5cb5 + 0xd);
                      FUN_0046eea0();
                      FUN_004589a0(&DAT_004d5ea5);
                      DAT_005644d4 = 1;
                      FUN_0046f0e0(0);
                      CalculatePlayersScores();
                      if ((DAT_0058f1fc != 0) && (DAT_004d5a78 != 0)) {
                        FUN_00427ee8();
                        DAT_004d5a78 = 0;
                      }
                      if (DAT_0059f154 == 1) {
                        AutoSave();
                      }
                      FUN_004589a0(&DAT_004d5ea7);
                      RunAITurns();
                      if (DAT_0058f1fc != 0) {
                        FUN_00427eb4(1,PTR_s_Re_synching_Machines_00509844,
                                     PTR_s_All_players_are_now_being_synchr_00509848,0,2);
                        FUN_00427f04();
                        DAT_004d5a78 = 1;
                      }
                      FUN_0046fa54();
                      FUN_004589a0(&DAT_004d5ea9);
                      AutoSave();
                      FUN_00405378();
                      if (DAT_0058f1ec == 0) {
                        FUN_004589a0(&DAT_004d5d34);
                        FUN_004152e0();
                        DAT_005644d4 = 0;
                        FUN_004589a0(&DAT_004d5eab);
                        FUN_004238c8();
                        FUN_004589a0(&DAT_004d5eae);
                        FUN_0046ee88();
                        FUN_004589a0(&DAT_004d5eb1);
                        FUN_004878a8();
                        FUN_004589a0(&DAT_004d5eb4);
                        SyncBeginTurn(DAT_0059f154);
                        FUN_004589a0(&DAT_004d5eb7);
                        FUN_0046f938();
                        FUN_00441400();
                        SeaManipulationEffects();
                        if (DAT_0058f1ec == 0) {
                          FUN_0047c730();
                          FUN_004589a0(&DAT_004d5eba);
                          FUN_00485668(1);
                          FUN_004589a0(&DAT_004d5d30);
                          FUN_0046c7d4();
                          if (DAT_0058f1fc != 0) {
                            WaitSync(s_WndMain__SynchronizeGame_After_L_004d5ebd);
                            SynchronizeGame();
                            WaitSync(s_WndMain__SynchronizeGame_After_L_004d5ebd);
                            FUN_0044cabc();
                            FUN_00445710();
                          }
                          FUN_004589a0(&DAT_004d5eeb);
                          FUN_00457624();
                          FUN_0044b9e4();
                          FUN_004589a0(&DAT_004d5eee);
                          FUN_0046c780();
                          FUN_004589a0(&DAT_004d5ef1);
                          FUN_00485668(2);
                          FUN_004589a0(&DAT_004d5ef4);
                          FUN_0046e730(0);
                          FUN_004589a0(&DAT_004d5ef7);
                          FUN_00486e34();
                        }
                      }
                      FUN_004589a0(&DAT_004d5efa);
                      for (iVar3 = 0; iVar3 < DAT_004d5aec; iVar3 = iVar3 + 1) {
                        FUN_0046ac44(local_cc,iVar3);
                      }
                      if (DAT_0058f1fc != 0) {
                        if (DAT_0058f1ec == 0) {
                          if ((DAT_0058f1fc != 0) && (DAT_0058f1f4 != DAT_004d5a58)) {
                            uVar7 = 2;
                            uVar6 = 0;
                            uVar2 = FUN_0049117e(0,0x54415453,0x13);
                            uVar5 = FUN_0049117e(0,0x54415453,0x12);
                            FUN_00427eb4(0,uVar5,uVar2,uVar6,uVar7);
                          }
                          WaitSync(s_WndMain__Before_SynchronizeGame_a_004d5efd);
                          if ((DAT_0058f1fc != 0) && (DAT_0058f1f4 != DAT_004d5a58)) {
                            SynchronizeGame();
                          }
                          WaitSync(s_WndMain__After_SynchronizeGame_a_004d5f2c);
                          if ((DAT_0058f1fc != 0) && (DAT_0058f1f4 != DAT_004d5a58)) {
                            FUN_00427ee8();
                          }
                        }
                        FUN_0044cabc();
                        FUN_00445710();
                      }
                    }
                    FUN_004152ec();
                    DAT_0059f154 = DAT_0059f154 + 1;
                  }
                  if ((DAT_0058f1fc != 0) && (DAT_004d5a78 != 0)) {
                    FUN_00427ee8();
                    DAT_004d5a78 = 0;
                  }
                  SavePrefs();
                  FUN_0046ce10(1);
                  if (DAT_004d59b4 == 0x2a) {
                    FUN_004360ec();
                    DAT_004d59b4 = 0x32;
                  }
                }
                ShutdownGame();
                uVar2 = 0;
              }
            }
            else {
              uVar2 = 0xfffffffc;
            }
          }
        }
        else {
          uVar2 = 0xfffffffd;
        }
      }
      else {
        uVar2 = 0xfffffffe;
      }
    }
  }
  else {
    SetForegroundWindow(hWnd);
    uVar2 = 0;
  }
  return uVar2;
}

