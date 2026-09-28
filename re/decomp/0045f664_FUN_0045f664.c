// FUN_0045f664 @ 0045f664 size=449 sig=undefined FUN_0045f664() cc=unknown
// callers: ChCht
// callees: memset,memcpy,FUN_004620dc

void FUN_0045f664(undefined4 param_1)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  undefined4 unaff_EBX;
  undefined1 *puVar8;
  undefined4 uVar9;
  undefined4 local_b4 [7];
  undefined1 local_98;
  undefined4 local_96;
  undefined4 local_92;
  undefined4 local_8e;
  undefined1 local_8a [16];
  undefined4 local_7a;
  undefined4 local_76;
  undefined4 local_72;
  undefined4 local_6e;
  undefined4 local_6a;
  undefined4 local_66;
  undefined4 local_62;
  undefined4 local_5e;
  undefined4 local_5a;
  undefined4 local_56;
  undefined1 local_4e [14];
  undefined4 local_40;
  undefined4 local_3c;
  int local_38;
  undefined1 local_34 [7];
  undefined1 local_2d;
  undefined4 local_2c [7];
  undefined1 local_10 [4];
  undefined4 local_c;
  int local_8;
  
  memset(local_b4,0,0xac);
  local_b4[0] = DAT_0059f154;
  local_b4[1] = DAT_0059f158;
  local_b4[2] = DAT_0059f15c;
  local_b4[3] = DAT_004d5aec;
  local_b4[4] = DAT_004d5af0;
  local_b4[5] = DAT_004d5af8;
  local_b4[6] = DAT_004d5afc;
  local_98 = DAT_004d5b00;
  local_96 = DAT_004d5b08;
  local_92 = DAT_004d5b04;
  local_8e = DAT_004d5b0c;
  memset(local_8a,0,0x10);
  local_7a = DAT_004d5b24;
  local_76 = DAT_0058f1f4;
  local_72 = DAT_00651cb0;
  local_6e = DAT_0065209c;
  local_6a = DAT_004d5b2c;
  local_66 = DAT_004d5b28;
  local_62 = DAT_004d5b30;
  local_5e = DAT_004d5b34;
  local_5a = DAT_004d5b38;
  local_56 = DAT_004d5b3c;
  uVar9 = 0xe;
  memcpy(local_4e,&DAT_0065e42c,0xe);
  local_40 = DAT_004d5a90;
  local_3c = DAT_004d825c;
  local_38 = DAT_004d5a94;
  local_8 = 0;
  puVar6 = local_2c;
  puVar3 = &DAT_0065e404;
  puVar8 = local_34;
  puVar4 = &DAT_005a0548;
  do {
    uVar1 = *puVar4;
    puVar4 = puVar4 + 1;
    *puVar8 = uVar1;
    puVar8 = puVar8 + 1;
    uVar2 = *puVar3;
    puVar3 = puVar3 + 1;
    *puVar6 = uVar2;
    puVar6 = puVar6 + 1;
    local_8 = local_8 + 1;
  } while (local_8 < 7);
  local_2d = DAT_0059f0fc;
  puVar8 = local_10;
  iVar5 = 0;
  puVar7 = &DAT_004c61e0 + DAT_004d5a94 * 0xd8;
  do {
    *puVar8 = *puVar7;
    iVar5 = iVar5 + 1;
    puVar8 = puVar8 + 1;
    puVar7 = puVar7 + 0x44;
  } while (iVar5 < 3);
  local_c = DAT_004d5af4;
  iVar5 = 0x2a;
  do {
    puVar6 = local_b4 + iVar5;
    iVar5 = iVar5 + -1;
  } while (-1 < iVar5);
  FUN_004620dc(param_1,uVar9,*puVar6,unaff_EBX);
  return;
}

