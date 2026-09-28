// FUN_0043793c @ 0043793c size=218 sig=undefined FUN_0043793c() cc=unknown
// callers: FUN_0047681c
// callees: FUN_00427e80,FUN_00477f9c,FUN_004727dc,FUN_00427f04,sprintf,FUN_00427e6c,FUN_00427ee8,FUN_0044a000
// strings: \"The %s offer to transfer %d %s to %s for %d credits per unit.\\n\\nIt would cost us an additional %d credits to transfer the materials.\\n\\nThe total cost would be %d credits.\"|\"An offer to you\"

bool FUN_0043793c(int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined1 local_42c [1064];
  
  iVar1 = FUN_004727dc(param_1,param_2);
  sprintf(local_42c,PTR_s_The__s_offer_to_transfer__d__s_t_00509390,
          (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8]],param_4
          ,(&PTR_s_credits_005090f0)[param_3],param_2,param_5,iVar1 * param_4,
          param_4 * param_5 + iVar1 * param_4);
  FUN_00427e80(0x28a1,PTR_s_An_offer_to_you_0050938c,local_42c,0,0x11);
  FUN_00427f04();
  FUN_0044a000();
  iVar1 = 0;
  while ((*(int *)(&DAT_006534fc + DAT_0058f1f4 * 4) == 2 && (iVar1 == 0))) {
    FUN_00477f9c();
    iVar1 = FUN_00427e6c();
  }
  FUN_00427ee8();
  return iVar1 == 3;
}

