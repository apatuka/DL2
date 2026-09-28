// WriteUnitData @ 00437cd0 size=1121 sig=undefined WriteUnitData() cc=unknown
// callers: FUN_004383a4,FUN_00438134
// callees: FUN_0049eb44,FUN_00471cec,FUN_0044ddf4,DebugMessage,FUN_00498ba9,FUN_00471cc0,sprintf,FUN_00437a3c,FUN_00472ca0,FUN_0046d250,memset,FUN_004989cf
// strings: \"pColorList NULL in WriteUnitData()\"|\"%s cr.\"|\"%d Labor\"|\"tons of food\"|\"KW of energy\"|\"%d %s\"

/* auto-named from string evidence: WriteUnitData */

void WriteUnitData(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  int local_1f4 [3];
  int *local_1e8;
  undefined **local_1e4;
  undefined1 local_1e0 [256];
  undefined1 local_e0 [64];
  undefined4 local_a0;
  int local_9c;
  int local_98 [11];
  undefined1 local_6c [6];
  undefined1 local_66;
  undefined1 local_64;
  
  sprintf(local_1e0,s__d__s_004c473c + 5);
  FUN_0049eb44(DAT_004c46b4,0xe,1,0xf,0,0);
  FUN_0049eb44(DAT_004c46b4,0x10,1,0xf,0,0);
  FUN_0049eb44(DAT_004c46b4,0x11,1,0xf,0,0);
  FUN_0049eb44(DAT_004c46b4,0x12,1,0xf,0,0);
  FUN_0049eb44(DAT_004c46b4,0x13,1,0xf,0,0);
  FUN_0049eb44(DAT_004c46b4,0x14,1,0xf,0,0);
  FUN_0049eb44(DAT_004c46b4,0x15,1,0xf,0,0);
  FUN_0049eb44(DAT_004c46b4,0x16,1,0xf,0,0);
  FUN_0049eb44(DAT_004c46b4,0x17,1,0xf,0,0);
  if (DAT_004c4738 != 0) {
    memset(local_6c,0,0x5c);
    local_66 = (undefined1)DAT_004c4738;
    local_64 = (undefined1)DAT_0058f1f4;
    FUN_00437a3c(local_6c);
    FUN_0044ddf4(PTR_DAT_004d5988,DAT_004c4738,&local_a0);
    if ((DAT_004d5aa0 == '\0') || (DAT_00559338 != 0)) {
      local_1f4[0] = FUN_00472ca0(DAT_0055933c,&local_9c);
      piVar4 = local_1f4;
      local_1f4[1] = 0;
      if (local_1f4[0] < 0) {
        piVar4 = local_1f4 + 1;
      }
      iVar6 = *piVar4;
    }
    else {
      iVar6 = 0;
    }
    puVar1 = (undefined4 *)FUN_00498ba9(0x10);
    if (puVar1 == (undefined4 *)0x0) {
      DebugMessage(s_pColorList_NULL_in_WriteUnitData_004c4742);
    }
    else {
      *puVar1 = 3;
      FUN_0049eb44(DAT_004c46b4,0x10,1,0x12,2,puVar1);
      if (*(int *)(PTR_DAT_004d5988 + 0xc) < *(int *)(&DAT_004fb4f8 + DAT_004c4738 * 0x2c)) {
        puVar1[1] = 0x60;
      }
      else {
        puVar1[1] = 0x30;
      }
      FUN_0049eb44(DAT_004c46b4,0x10,1,0x13,2,puVar1);
      uVar2 = FUN_0046d250(iVar6 + local_9c,local_e0);
      sprintf(local_1e0,PTR_s__s_cr__00509b50,uVar2);
      FUN_0049eb44(DAT_004c46b4,0x10,1,0xf,0,local_1e0);
      sprintf(local_1e0,PTR_s__d_Labor_00509b54,local_a0);
      FUN_0049eb44(DAT_004c46b4,0x11,1,0xf,0,local_1e0);
      local_1e4 = &PTR_s_tons_of_food_005090f4;
      local_1e8 = local_98;
      iVar6 = 0;
      iVar7 = 1;
      puVar5 = &DAT_004fb4fc;
      do {
        if (*local_1e8 != 0) {
          sprintf(local_1e0,s__d__s_004c473c,*local_1e8,*local_1e4);
          if (iVar7 == 4) {
            local_1f4[2] = FUN_00471cc0(DAT_0055933c + 0x3a);
          }
          else {
            local_1f4[2] = *(int *)(DAT_0055933c + 0x3a + iVar7 * 4);
          }
          FUN_0049eb44(DAT_004c46b4,iVar6 + 0x12,1,0x12,2,puVar1);
          if (local_1f4[2] < *(int *)(puVar5 + DAT_004c4738 * 0x2c)) {
            iVar3 = FUN_00471cec((int)*(char *)(DAT_0055933c + 0x20),iVar7,
                                 *(int *)(puVar5 + DAT_004c4738 * 0x2c));
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
          FUN_0049eb44(DAT_004c46b4,iVar6 + 0x12,1,0x13,2,puVar1);
          FUN_0049eb44(DAT_004c46b4,iVar6 + 0x12,1,0xf,0,local_1e0);
          iVar6 = iVar6 + 1;
        }
        iVar7 = iVar7 + 1;
        puVar5 = puVar5 + 4;
        local_1e4 = local_1e4 + 1;
        local_1e8 = local_1e8 + 1;
      } while (iVar7 < 0xb);
      iVar7 = (int)(char)(&DAT_004faf8b)[DAT_004c4738 * 0x24];
      if (iVar7 != 0) {
        FUN_0049eb44(DAT_004c46b4,iVar6 + 0x12,1,0x12,2,puVar1);
        if ((1 << ((byte)DAT_0058f1f4 & 0x1f) & (int)(short)(&DAT_004fbbac)[iVar7 * 0x19]) == 0) {
          puVar1[1] = 0x60;
        }
        else {
          puVar1[1] = 0x30;
        }
        FUN_0049eb44(DAT_004c46b4,iVar6 + 0x12,1,0x13,2,puVar1);
        sprintf(local_1e0,s__d__s_004c473c + 3,
                *(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + iVar7 * 0x32));
        FUN_0049eb44(DAT_004c46b4,iVar6 + 0x12,1,0xf,0,local_1e0);
      }
      FUN_004989cf(puVar1);
    }
  }
  return;
}

