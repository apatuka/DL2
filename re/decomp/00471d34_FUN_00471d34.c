// FUN_00471d34 @ 00471d34 size=291 sig=undefined FUN_00471d34() cc=unknown
// callers: FUN_0041d414,FUN_0044db50,CheckBuildingList,FUN_00420e34
// callees: FUN_0042836c,sprintf,FUN_004a68dc
// strings: \"To build a %s you will need:\\n\"|\"%d credits and the import cost of the materials\\n\"|\"%d %s\\n\"|\"Tech: %s\\n\"|\"Not enough Stuff!\"

void FUN_00471d34(undefined4 param_1,uint param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined **ppuVar3;
  undefined1 local_448 [64];
  undefined1 local_408 [1024];
  uint local_8;
  
  sprintf(local_408,PTR_s_To_build_a__s_you_will_need__00509960,param_1);
  local_8 = 1;
  iVar2 = 0;
  ppuVar3 = &PTR_s_credits_005090c4;
  puVar1 = param_3;
  do {
    puVar1 = puVar1 + 1;
    if ((param_2 & local_8) != 0) {
      if ((iVar2 == 0) && ((param_2 & 0x2000) != 0)) {
        sprintf(local_448,PTR_s__d_credits_and_the_import_cost_o_0050996c,*puVar1);
      }
      else {
        sprintf(local_448,s__d__s_004d638e,*puVar1,*ppuVar3);
      }
      FUN_004a68dc(local_408,local_448);
    }
    local_8 = local_8 << 1;
    ppuVar3 = ppuVar3 + 1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb);
  FUN_004a68dc(local_408,s__d__s_004d638e + 5);
  if ((param_2 & 0x1000) != 0) {
    sprintf(local_448,PTR_s_Tech___s_00509964,
            *(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + param_3[0xc] * 0x32));
    FUN_004a68dc(local_408,local_448);
  }
  FUN_0042836c(PTR_s_Not_enough_Stuff__00509968,local_408,4,0,0xf);
  return;
}

