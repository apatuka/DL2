// SetItemStats @ 0041a634 size=1310 sig=undefined SetItemStats() cc=unknown
// callers: FUN_0041ab54,FUN_0041acf8
// callees: FUN_0046d250,FUN_0044de9c,FUN_0049eb44,FUN_00498ba9,FUN_00472ca0,FUN_00471cc0,FUN_00471cec,sprintf,DebugMessage
// strings: \"pColorList NULL in SetItemStats()\"|\"%d Labor\"|\"%s cr.\"|\"tons of food\"|\"%d %s\"|\"A Random Resource\"|\"Nothing\"|\"Upkeep: %d Energy/turn\"|\"Upkeep: None\"

/* auto-named from string evidence: SetItemStats, Upkeep */

void SetItemStats(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  int local_490;
  int local_48c;
  undefined **local_488;
  undefined1 local_484 [1024];
  undefined1 local_84 [64];
  undefined4 local_44;
  int local_40;
  int local_3c [11];
  
  DAT_004b76f4 = DAT_004b76fc;
  sprintf(local_484,&DAT_004b7700,*(undefined4 *)(&DAT_004f9dbc + DAT_004b76fc * 0x32));
  FUN_0049eb44(DAT_004b76f8,9,1,0xf,0,local_484);
  puVar1 = (undefined4 *)FUN_00498ba9(0x10);
  if (puVar1 == (undefined4 *)0x0) {
    DebugMessage(s_pColorList_NULL_in_SetItemStats__004b7703);
  }
  else {
    *puVar1 = 3;
    FUN_0049eb44(DAT_004b76f8,0xc,1,0x12,2,puVar1);
    FUN_0044de9c(PTR_DAT_004d5988,DAT_004b76f4,(int)*(char *)(DAT_0053b334 + 0x21),&local_44);
    local_490 = FUN_00472ca0(DAT_0053b334,&local_40);
    piVar4 = &local_490;
    local_48c = 0;
    if (local_490 < 0) {
      piVar4 = &local_48c;
    }
    DAT_0053b330 = *piVar4;
    sprintf(local_484,PTR_s__d_Labor_00509298,local_44);
    FUN_0049eb44(DAT_004b76f8,0xd,1,0xf,0,local_484);
    if ((*(int *)(PTR_DAT_004d5988 + 0xc) < local_40) && (DAT_004d5aa0 == '\0')) {
      puVar1[1] = 0x60;
    }
    else if ((*(int *)(PTR_DAT_004d5988 + 0xc) < local_40 + DAT_0053b330) && (DAT_004d5aa0 == '\0'))
    {
      puVar1[1] = 0xf2;
    }
    else {
      puVar1[1] = 0x30;
    }
    FUN_0049eb44(DAT_004b76f8,0xc,1,0x13,2,puVar1);
    uVar2 = FUN_0046d250(local_40 + DAT_0053b330,local_84);
    sprintf(local_484,PTR_s__s_cr__00509294,uVar2);
    FUN_0049eb44(DAT_004b76f8,0xc,1,0xf,0,local_484);
    iVar5 = 0;
    iVar6 = 1;
    local_488 = &PTR_s_tons_of_food_005090f4;
    piVar4 = local_3c;
    do {
      if (*piVar4 != 0) {
        if (iVar6 == 4) {
          iVar3 = FUN_00471cc0(DAT_0053b334 + 0x3a);
        }
        else {
          iVar3 = *(int *)(DAT_0053b334 + 0x3a + iVar6 * 4);
        }
        if ((iVar3 < *piVar4) && (DAT_004d5aa0 == '\0')) {
          iVar3 = FUN_00471cec((int)*(char *)(DAT_0053b334 + 0x20),iVar6,*piVar4);
          if (iVar3 == 0) {
            puVar1[1] = 0x60;
          }
          else {
            puVar1[1] = 0xf2;
          }
        }
        else {
          puVar1[1] = 0x30;
        }
        FUN_0049eb44(DAT_004b76f8,iVar5 + 0xe,1,0x13,2,puVar1);
        sprintf(local_484,s__d__s_004b7725,*piVar4,*local_488);
        FUN_0049eb44(DAT_004b76f8,iVar5 + 0xe,1,0xf,0,local_484);
        iVar5 = iVar5 + 1;
      }
      local_488 = local_488 + 1;
      iVar6 = iVar6 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar6 < 0xb);
    DAT_0053b32c = (int)(char)(&DAT_004f9de3)[DAT_004b76f4 * 0x32];
    if (DAT_0053b32c != 0) {
      FUN_0049eb44(DAT_004b76f8,iVar5 + 0xe,1,0x12,2,puVar1);
      if ((((int)(short)(&DAT_004fbbac)[DAT_0053b32c * 0x19] & 1 << (*PTR_DAT_004d5988 & 0x1f)) == 0
          ) && (DAT_004d5aa0 == '\0')) {
        puVar1[1] = 0x60;
      }
      else {
        puVar1[1] = 0x30;
      }
      FUN_0049eb44(DAT_004b76f8,iVar5 + 0xe,1,0x13,2,puVar1);
      sprintf(local_484,&DAT_004b7700,
              *(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + DAT_0053b32c * 0x32));
      FUN_0049eb44(DAT_004b76f8,iVar5 + 0xe,1,0xf,0,local_484);
      iVar5 = iVar5 + 1;
    }
    local_484[0] = 0;
    for (; iVar5 < 5; iVar5 = iVar5 + 1) {
      FUN_0049eb44(DAT_004b76f8,iVar5 + 0xe,1,0xf,0,local_484);
    }
    iVar6 = 1;
    iVar5 = 0;
    puVar7 = &DAT_004f9dbd;
    do {
      if ((iVar6 == 1) && ((DAT_004b76f4 == 0x2e || (DAT_004b76f4 == 0x2f)))) {
        sprintf(local_484,&DAT_004b7700,PTR_s_A_Random_Resource_005092a8);
        FUN_0049eb44(DAT_004b76f8,iVar5 + 0x14,1,0xf,0,local_484);
        iVar5 = iVar5 + 1;
      }
      else if ((char)puVar7[DAT_004b76f4 * 0x32 + 0x18] != 0) {
        sprintf(local_484,&DAT_004b7700,(&PTR_s__00509240)[(char)puVar7[DAT_004b76f4 * 0x32 + 0x18]]
               );
        FUN_0049eb44(DAT_004b76f8,iVar5 + 0x14,1,0xf,0,local_484);
        iVar5 = iVar5 + 1;
      }
      iVar6 = iVar6 + 1;
      puVar7 = puVar7 + 1;
    } while (iVar6 < 5);
    for (; iVar5 < 4; iVar5 = iVar5 + 1) {
      if (iVar5 == 0) {
        sprintf(local_484,&DAT_004b7700,PTR_s_Nothing_0050929c);
        FUN_0049eb44(DAT_004b76f8,0x14,1,0xf,0,local_484);
      }
      else {
        local_484[0] = 0;
        FUN_0049eb44(DAT_004b76f8,iVar5 + 0x14,1,0xf,0,local_484);
      }
    }
    if ((char)(&DAT_004f9dc8)[DAT_004b76f4 * 0x32] == 0) {
      sprintf(local_484,PTR_s_Upkeep__None_005092a4,0);
    }
    else {
      sprintf(local_484,PTR_s_Upkeep___d_Energy_turn_005092a0,
              (int)(char)(&DAT_004f9dc8)[DAT_004b76f4 * 0x32]);
    }
    FUN_0049eb44(DAT_004b76f8,10,1,0xf,0,local_484);
  }
  return;
}

