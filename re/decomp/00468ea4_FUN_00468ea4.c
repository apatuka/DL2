// FUN_00468ea4 @ 00468ea4 size=405 sig=undefined FUN_00468ea4() cc=unknown
// callers: 
// callees: FUN_004a6b48,FUN_0042e4c0,FUN_0042e3e4,FUN_00479b6c,FUN_0042e434,FUN_00479700,FUN_0047526c,FUN_004360ec,FUN_0042e2b8,FUN_00436098,FUN_00477f9c,FUN_004ae594,FUN_00461c68,MessagePump
// strings: \"New Player\"

undefined4 FUN_00468ea4(void)

{
  bool bVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  
  uVar4 = 0x46;
  if (DAT_004d513c == 0) {
    if (DAT_004d5a88 != 0) {
      bVar1 = false;
      if (DAT_004d5a50 != 0) {
        if (DAT_004d5a4c == 0) {
          iVar2 = FUN_00479b6c();
          if (iVar2 == 0) {
            bVar1 = true;
          }
        }
        else {
          DAT_004dc300 = 0;
          while (DAT_004dc300 == 0) {
            MessagePump();
            FUN_00477f9c();
          }
        }
      }
      if ((!bVar1) && (iVar2 = FUN_00461c68(&DAT_005597d5), iVar2 != 0)) {
        DAT_004d59a8 = 0;
        return 0x46;
      }
      uVar4 = 0x35;
    }
  }
  else {
    FUN_004ae594(DAT_0059f158);
    FUN_004360ec();
    FUN_0042e434();
    FUN_0042e3e4();
    FUN_0042e2b8();
    FUN_0042e4c0();
    FUN_00436098();
    if (DAT_0058f1ec == 0) {
      if (DAT_004d5a4c == 0) {
        iVar2 = FUN_00479700();
        if (iVar2 == 0) {
          uVar4 = 0x35;
          DAT_004d513c = 0;
        }
      }
      else {
        DAT_004dc300 = 0;
        while (DAT_004dc300 == 0) {
          MessagePump();
          FUN_00477f9c();
        }
      }
      iVar2 = 0;
      pcVar3 = &DAT_0059f162;
      do {
        if (iVar2 == DAT_0058f1f4) {
          FUN_004a6b48(&DAT_0059f413 + iVar2 * 0x2d8,s_New_Player_00509804,0x1f);
        }
        else {
          FUN_004a6b48(&DAT_0059f413 + iVar2 * 0x2d8,(&PTR_s_Sting_00509938)[*pcVar3],0x1f);
        }
        iVar2 = iVar2 + 1;
        pcVar3 = pcVar3 + 0x2d8;
      } while (iVar2 < 7);
      FUN_0047526c(DAT_0058f1f4,s_New_Player_00509804);
      DAT_004d598c = 1;
    }
    else {
      uVar4 = 0x35;
      DAT_004d513c = 0;
    }
  }
  DAT_004d59a8 = 0;
  return uVar4;
}

