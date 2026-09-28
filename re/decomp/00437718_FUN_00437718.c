// FUN_00437718 @ 00437718 size=543 sig=undefined FUN_00437718() cc=unknown
// callers: FUN_0045ca3c
// callees: FUN_00427e80,FUN_00477f9c,FUN_0042836c,FUN_00427f04,FUN_00476760,sprintf,FUN_0043735c,FUN_004767f0,FUN_004371e4,FUN_00427e6c,FUN_00427ee8,FUN_00437668,FUN_0044a000,FUN_0047691c
// strings: \"Selling Materials\"|\"Offering to sell some of our %s in %s to the %s.\"|\"This colony felt that your offer would cost too much.  They refuse to trade with you.\"|\"Trade Completed!\"|\"The %s are busy with other matters.  Try them later.\"|\"Proposing a pact\"|\"Your offer is accepted with enthusiasm.  More money is yours!\"

undefined4 FUN_00437718(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined1 local_80c [1024];
  undefined1 local_40c [1024];
  undefined4 local_c;
  undefined4 local_8;
  
  iVar1 = FUN_0043735c(param_1,param_2,param_3);
  if (iVar1 == 0) {
    return 2;
  }
  FUN_004371e4();
  iVar1 = 0;
  while ((iVar1 != 0xc && (iVar1 != 0xb))) {
    iVar1 = FUN_00437668(&local_c,&local_8);
  }
  if (iVar1 != 0xb) {
    return 2;
  }
  sprintf(local_40c,s__d__s_004c46ac + 3,PTR_s_Selling_Materials_00509a4c);
  sprintf(local_80c,PTR_s_Offering_to_sell_some_of_our__s_i_00509a50,
          (&PTR_s_credits_00509098)[param_3],param_1,
          (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[*(char *)(param_2 + 0x20) * 0x2d8]]);
  FUN_00427e80(1,local_40c,local_80c,0,0x11);
  FUN_00427f04();
  FUN_0044a000();
  FUN_004767f0(DAT_0058f1f4,2);
  FUN_0047691c(param_1,param_2,param_3,local_c,local_8);
  iVar1 = 0;
  while ((*(int *)(&DAT_006534fc + DAT_0058f1f4 * 4) == 2 && (iVar1 == 0))) {
    FUN_00477f9c();
    iVar1 = FUN_00427e6c();
  }
  FUN_00427ee8();
  if (iVar1 == 4) {
    FUN_004767f0((int)*(char *)(param_2 + 0x20),0);
    FUN_004767f0(DAT_0058f1f4,0);
    return 2;
  }
  iVar1 = *(int *)(&DAT_006534fc + DAT_0058f1f4 * 4);
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      sprintf(local_40c,PTR_s_The__s_are_busy_with_other_matte_005093bc,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[*(char *)(param_2 + 0x20) * 0x2d8]]);
      FUN_0042836c(PTR_s_Proposing_a_pact_00509398,local_40c,4,0,0x11);
      goto LAB_00437915;
    }
    if (iVar1 == 3) {
      FUN_0042836c(PTR_s_Trade_Completed__005096dc,PTR_s_Your_offer_is_accepted_with_enth_005096e0,4
                   ,0,0x11);
      FUN_00476760(param_1,param_2,param_3,local_c,local_8);
      goto LAB_00437915;
    }
    if (iVar1 != 4) goto LAB_00437915;
  }
  FUN_0042836c(PTR_s_Trade_Completed__005096dc,PTR_s_This_colony_felt_that_your_offer_005096e8,4,0,
               0x11);
LAB_00437915:
  FUN_004767f0(DAT_0058f1f4,0);
  return 1;
}

