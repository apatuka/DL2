// CheckSubTech @ 00435804 size=671 sig=undefined CheckSubTech() cc=unknown
// callers: FUN_00435e34
// callees: FUN_00434f28,FUN_0043242c,FUN_0049eb44,FUN_00412d38,FUN_00412f10,FUN_00432ad0,FUN_0048db5d,FUN_004ae26c,FUN_00426594,FUN_00431128,FUN_004a4025,FUN_00432cf4,FUN_0042836c,DebugMessage,FUN_004a2cb5,FUN_00432e0c,FUN_00431534,FUN_00476dcc,FUN_004314d8
// strings: \"gpSkirTech NULL in CheckSubTech()\"|\"You do not have enough funds for this technology!\\nObviously, we cannot complete this sale.  A pity.  Now this technology will have to be sold to someone else.\"|\"Not Enough Credits\"

/* auto-named from string evidence: CheckSubTech */

undefined4 CheckSubTech(void)

{
  int iVar1;
  undefined4 uVar2;
  int local_cc;
  undefined1 local_c8 [200];
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  if (DAT_004c42dc == 0) {
    DebugMessage(s_gpSkirTech_NULL_in_CheckSubTech__004c4614);
  }
  else {
    if ((((DAT_004c42e4 != 0) && (DAT_004c42f0 == 0)) && (*(char *)(DAT_004c42e4 + 0x3c) == '\0'))
       && (DAT_004c42ec == 0)) {
      DAT_004c5b78 = 0;
      DAT_004c5b70 = 0;
      DAT_004c5b7c = 0;
      DAT_004c5b74 = 0;
      FUN_00412f10(DAT_004c42e4);
      FUN_00412d38(DAT_004c42e4,*(undefined4 *)(DAT_004c42dc + 0x3c));
      DAT_004c42f0 = 1;
    }
    iVar1 = FUN_004a2cb5(DAT_004c42dc,&local_cc);
    if (((iVar1 == 0) && (local_cc != 0)) && (*(int *)(DAT_004c42dc + 100) == 0)) {
      switch(local_cc) {
      case 5:
        FUN_00426594(&DAT_004d47a0);
        break;
      case 6:
        FUN_00431128();
        FUN_00432e0c();
        DAT_004d59a4 = 0;
        return 1;
      case 7:
        if (DAT_004c4504 != -1) {
          FUN_0049eb44(DAT_004c42dc,0x11,1,0xe,0x3ff,local_c8);
          iVar1 = FUN_004ae26c(local_c8);
          if ((int)(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6] < iVar1 * 5) {
            FUN_0042836c(PTR_s_Not_Enough_Credits_00509570,
                         PTR_s_You_do_not_have_enough_funds_for_00509574,4,0,9);
          }
          else {
            FUN_00476dcc(PTR_DAT_004d5988,DAT_004c4504);
            uVar2 = FUN_0049eb44(DAT_004c42dc,0x14,1,0x22,0,0);
            FUN_004314d8(uVar2);
            if (DAT_00558e60 == 0) {
              FUN_004a4025(DAT_004c42dc);
              DAT_004c42dc = 0;
              FUN_00434f28();
              FUN_00432cf4();
              DAT_004d59a4 = 0;
            }
            else {
              FUN_00431534(DAT_00558de0);
              FUN_0049eb44(DAT_004c42dc,0x14,1,0x1b,0,0);
            }
          }
        }
        break;
      case 9:
        FUN_004a4025(DAT_004c42dc);
        DAT_004c42dc = 0;
        FUN_00434f28();
        FUN_00432cf4();
        DAT_004d59a4 = 0;
        break;
      case 10:
        FUN_004a4025(DAT_004c42dc);
        DAT_004c42dc = 0;
        FUN_00432ad0();
        FUN_00432cf4();
        DAT_004d59a4 = 0;
        break;
      case 0xc:
        FUN_004a4025(DAT_004c42dc);
        DAT_004c42dc = 0;
        FUN_0043242c();
        FUN_00432cf4();
        DAT_004d59a4 = 0;
      }
      FUN_00432cf4();
      DAT_004d59a4 = 0;
    }
    else {
      DAT_004d59a4 = 0;
    }
  }
  return 0;
}

