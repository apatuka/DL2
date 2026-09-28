// FUN_00427ab0 @ 00427ab0 size=398 sig=undefined FUN_00427ab0() cc=unknown
// callers: FUN_0044b4f8
// callees: FUN_00481a5c,sprintf,FUN_00441bf4,FUN_00441c90,FUN_00441c28
// strings: \"Can't Land: Ocean Territory\"|\"Can't Land: Wasteland Territory\"|\"Can't Land: Adjacent to enemy colony.\"|\"We may land here.\"|\"Can't Land: Owned by %s\"|\"%s\\nTerrain Type: %s\\n\\n%d building sites\\n%d adjacent land territories\\n\\n%s\\n\"

undefined * FUN_00427ab0(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined *puVar5;
  undefined1 *puVar6;
  undefined1 local_4c [64];
  int local_c;
  int local_8;
  
  if ((DAT_004b7d70 != 0) && (DAT_00557794 != 0)) {
    iVar1 = *param_1;
    if ((iVar1 < DAT_004b7d4c) ||
       (((DAT_004b7d54 < iVar1 || (param_1[1] < DAT_004b7d48)) || (DAT_004b7d50 < param_1[1])))) {
      iVar1 = 0;
    }
    else {
      FUN_00481a5c(iVar1 - DAT_004b7d4c,param_1[1] - DAT_004b7d48,&local_8,&local_c);
      iVar1 = (int)(short)(&DAT_005a0552)[local_c * 200 + local_8 * 5];
    }
    if (iVar1 != 0) {
      iVar4 = iVar1 * 0xadc;
      puVar5 = &DAT_005a43d0 + iVar4;
      if ((&DAT_005a43f0)[iVar4] == -1) {
        if ((&DAT_005a43f1)[iVar4] == '\0') {
          sprintf(local_4c,PTR_s_Can_t_Land__Ocean_Territory_005095c4);
        }
        else if ((&DAT_005a43f1)[iVar4] == '\x05') {
          sprintf(local_4c,PTR_s_Can_t_Land__Wasteland_Territory_005095d8);
        }
        else if ((*(byte *)(&DAT_005a43ec + iVar1 * 0x2b7) & 4) == 0) {
          sprintf(local_4c,PTR_s_We_may_land_here__005095cc);
        }
        else {
          sprintf(local_4c,PTR_s_Can_t_Land__Adjacent_to_enemy_co_005095c8);
        }
      }
      else {
        sprintf(local_4c,PTR_s_Can_t_Land__Owned_by__s_005095d0,
                (&PTR_s_ChCh_t_00509038)
                [(char)(&DAT_0059f162)[(char)(&DAT_005a43f0)[iVar4] * 0x2d8]]);
      }
      FUN_00441c90();
      puVar6 = local_4c;
      uVar2 = FUN_00441c28(puVar5);
      uVar3 = FUN_00441bf4(puVar5);
      sprintf(&DAT_00557584,PTR_s__s_Terrain_Type___s__d_building_s_005095d4,puVar5,
              (&PTR_DAT_00509054)[(char)(&DAT_005a43f1)[iVar4]],uVar3,uVar2,puVar6);
      return &DAT_00557584;
    }
  }
  return (undefined *)0x0;
}

