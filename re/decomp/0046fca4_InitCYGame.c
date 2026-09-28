// InitCYGame @ 0046fca4 size=753 sig=undefined InitCYGame() cc=unknown
// callers: WinMain
// callees: FUN_00415274,DebugLog,FUN_00498d22,sprintf,FUN_0046fc70,FUN_0048dd95,FUN_0049981f,FUN_00489c3e,CYGame_InitDirectDraw,FUN_0048de1d,FUN_00495b72,FUN_0048afe3,FUN_00491898,FUN_0048c28d,FUN_00490d98,FUN_0048baa6,FUN_004a5e40,FUN_00457864,FUN_00482964,FUN_0042836c,FUN_0049a760,FUN_0048e0b7,FUN_0046ff98,FUN_0048d1a2,FUN_004a4273,FUN_004a57e0,XenoIntro,FUN_00494def
// strings: \"deadcyb.cam\"|\"deadtext.cam\"|\"dl2sound.cam\"|\"FindCD\"|\"Please place the Deadlock 2 CD-ROM in your drive and press OK.\\n\\nIf you just wish to join a multiplayer game, you may press CANCEL to continue without the CD.\"|\"Deadlock 2 CD-ROM Not Found\"|\"dl2music.cam\"|\"dl2segue.cam\"|\"deadanim.cam\"|\"deadcine.cam\"

/* Initializes the CYLib game object (DirectDraw, sound, timer) */

undefined4 InitCYGame(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_cc [200];
  
  DAT_0065eb98 = param_1;
  iVar1 = CYGame_InitDirectDraw(param_2,DAT_004d5a80,0x280,0x1e0,DAT_004d5a8c);
  if (iVar1 != 0) {
    DAT_0065e5a8 = DAT_004d5a8c;
    FUN_0048afe3(param_2,0,0);
    FUN_0048d1a2(5);
    iVar1 = FUN_0048baa6(0x1f4000,0x7d0000);
    if ((iVar1 != 0) && (iVar1 = FUN_00498d22(0x1f4000,0x400), iVar1 != 0)) {
      FUN_0049a760(0);
      FUN_00490d98(10,1);
      FUN_0049981f(0);
      iVar1 = FUN_00491898(0x28,0x28);
      if (iVar1 != 0) {
        DAT_0051c304 = 0;
        FUN_0048dd95();
        FUN_0048de1d();
        FUN_0048e0b7();
        FUN_00482964(DAT_004d5b40 == 0);
        FUN_00495b72();
        FUN_00489c3e();
        iVar1 = FUN_0046fc70(s_deadcyb_cam_004d5d86,1);
        if ((iVar1 != 0) && (iVar1 = FUN_0046fc70(s_deadtext_cam_004d5d92,1), iVar1 != 0)) {
          sprintf(local_cc,&DAT_004d5d9f,&DAT_004d59c8,s_dl2sound_cam_004d5da4);
          FUN_0046fc70(local_cc,0);
          FUN_004a4273(1);
          FUN_004a57e0(0x31304c44);
          FUN_004a5e40(0,0,0x280,0x1e0);
          DAT_004d5c28 = FUN_0048c28d(0x280,0x1e0,0);
          DAT_004d59b4 = 0x32;
          XenoIntro();
          FUN_00415274(DAT_004d5978);
          FUN_00494def(1);
          DebugLog(s_FindCD_004d5db1);
          do {
            iVar1 = FUN_00457864();
            if ((iVar1 != 0) || (DAT_004d5980 != 0)) break;
            iVar1 = FUN_0042836c(PTR_s_Deadlock_2_CD_ROM_Not_Found_0050989c,
                                 PTR_s_Please_place_the_Deadlock_2_CD_R_00509880,6,0,1);
          } while (iVar1 == 1);
          if (DAT_004d59ac == 0) {
            DAT_004d5b40 = 1;
          }
          else {
            sprintf(local_cc,&DAT_004d5d9f,&DAT_0058f20c,s_dl2music_cam_004d5db8);
          }
          FUN_0046fc70(local_cc,0);
          iVar1 = FUN_0046fc70(s_dl2segue_cam_004d5dc5,0);
          if ((iVar1 == 0) && (DAT_004d59ac != 0)) {
            sprintf(local_cc,&DAT_004d5d9f,&DAT_0058f20c,s_dl2segue_cam_004d5dc5);
            FUN_0046fc70(local_cc,0);
          }
          iVar1 = FUN_0046fc70(s_deadanim_cam_004d5dd2,0);
          if ((iVar1 == 0) && (DAT_004d59ac != 0)) {
            sprintf(local_cc,&DAT_004d5d9f,&DAT_0058f20c,s_deadanim_cam_004d5dd2);
            FUN_0046fc70(local_cc,0);
          }
          if (DAT_004d59ac != 0) {
            sprintf(local_cc,&DAT_004d5d9f,&DAT_0058f20c,s_deadcine_cam_004d5ddf);
            FUN_0046fc70(local_cc,0);
          }
          return 1;
        }
        FUN_0046ff98();
      }
    }
  }
  return 0;
}

