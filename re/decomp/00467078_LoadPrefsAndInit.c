// LoadPrefsAndInit @ 00467078 size=243 sig=undefined LoadPrefsAndInit() cc=unknown
// callers: WinMain
// callees: timeGetTime,LoadPrefs,FUN_004880e0,FUN_00488074,sprintf,FUN_0048463c
// strings: \"DEADLOCK 2 v%d.%d%d\"|\"Deadlock and Accolade are trademarks of Accolade, Inc.\\nThe Deadlock 2 game is (c)1997/1998 Accolade, Inc. Portions (c)Microsoft, Inc. All Rights Reserved.\"

/* Loads prefs at startup */

undefined4 LoadPrefsAndInit(void)

{
  int iVar1;
  undefined1 local_100 [256];
  
  LoadPrefs();
  FUN_0048463c(0);
  timeGetTime();
  if (DAT_004d59a8 == '\0') {
    iVar1 = FUN_00488074(0xffffffff,0,0,0);
    if (iVar1 == 0) {
      sprintf(local_100,PTR_s_DEADLOCK_2_v_d__d_d_00509c68,(int)DAT_004d5ae8 >> 8,
              (int)DAT_004d5ae8 >> 4 & 0xf,DAT_004d5ae8 & 0xf);
      FUN_004880e0(0x33303049,3000,local_100);
    }
    iVar1 = FUN_00488074(0xffffffff,0,0,0);
    if (iVar1 == 0) {
      FUN_004880e0(0x34303049,3000,0);
    }
    FUN_00488074(0x4e45504f,0,0,0);
    FUN_00488074(0x314f3244,0,0,0);
  }
  sprintf(local_100,PTR_s_Deadlock_and_Accolade_are_tradem_00509c6c);
  FUN_004880e0(0x35303049,7000,local_100);
  FUN_0048463c(DAT_0058f1d0);
  DAT_004d59a0 = 0;
  return 0;
}

