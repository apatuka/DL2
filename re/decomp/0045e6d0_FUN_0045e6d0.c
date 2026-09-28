// FUN_0045e6d0 @ 0045e6d0 size=194 sig=undefined FUN_0045e6d0() cc=unknown
// callers: FUN_0043baf4,FUN_0045f214
// callees: FUN_004878a8,FUN_00435e64,FUN_0046ca40,FUN_00435ed0,FUN_0042836c
// strings: \"You can only summon the Skirineen from your own settled territories. Select a new territory and try again.\"|\"Oolan's Advice\"|\"Skirineen Communique\"

void FUN_0045e6d0(void)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  FUN_004878a8();
  iVar1 = DAT_0059f154;
  if ((&DAT_005644fc)[DAT_0058f1f4 * 2] != DAT_0059f154) {
    if ((int)(&DAT_005644fc)[DAT_0058f1f4 * 2] < DAT_0059f154) {
      uVar2 = FUN_0046ca40();
      (&DAT_005644fc)[DAT_0058f1f4 * 2] = (uVar2 & 3) + iVar1 + 1;
    }
    uVar5 = 1;
    uVar4 = 0;
    uVar3 = 4;
    uVar2 = FUN_0046ca40(4,0,1);
    FUN_0042836c(PTR_s_Skirineen_Communique_005097bc,
                 (&PTR_s_This_shrewd_move_elevates_you_ab_005097b0)[uVar2 % 3],uVar3,uVar4,uVar5);
    return;
  }
  if ((char)(&DAT_005a43f0)[DAT_004c5b50 * 0xadc] == DAT_0058f1f4) {
    FUN_00435e64();
    FUN_00435ed0();
    return;
  }
  FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_can_only_summon_the_Skirinee_005097ac,4,0,1);
  return;
}

