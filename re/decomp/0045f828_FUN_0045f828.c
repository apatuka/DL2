// FUN_0045f828 @ 0045f828 size=485 sig=undefined FUN_0045f828() cc=unknown
// callers: FUN_004618e8
// callees: FUN_0044fd14,FUN_00462100

int FUN_0045f828(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  undefined1 *puVar8;
  undefined4 *puVar9;
  byte *pbVar10;
  undefined1 *puVar11;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined1 local_a0;
  undefined4 local_9e;
  undefined4 local_9a;
  int local_96;
  undefined4 local_82;
  undefined4 local_7e;
  undefined4 local_7a;
  undefined4 local_76;
  undefined4 local_72;
  undefined4 local_6e;
  undefined4 local_6a;
  undefined4 local_66;
  undefined4 local_62;
  undefined4 local_5e;
  undefined4 local_48;
  undefined4 local_44;
  int local_40;
  undefined1 local_3c [7];
  undefined1 local_35;
  undefined4 local_34 [7];
  byte local_18 [4];
  undefined4 local_14;
  int local_10;
  int local_c [2];
  
  iVar4 = FUN_00462100(param_1,&local_bc,DAT_00583da8,DAT_00583da4);
  if (iVar4 == 1) {
    DAT_0059f154 = local_bc;
    DAT_0059f158 = local_b8;
    DAT_0059f15c = local_b4;
    DAT_004d5aec = local_b0;
    DAT_004d5af0 = local_ac;
    DAT_004d5af8 = local_a8;
    DAT_004d5afc = local_a4;
    DAT_004d5b00 = local_a0;
    DAT_004d5b08 = local_9e;
    DAT_004d5b04 = local_9a;
    local_c[1] = 4;
    local_c[0] = 0;
    if (local_96 < 1) {
      piVar5 = local_c;
    }
    else {
      piVar5 = &DAT_004d5b0c;
    }
    if (3 < *piVar5) {
      piVar5 = local_c + 1;
    }
    DAT_004d5b0c = *piVar5;
    DAT_004d5b24 = local_82;
    if (param_2 != 0) {
      DAT_0058f1f4 = local_7e;
    }
    DAT_00651cb0 = local_7a;
    DAT_0065209c = local_76;
    DAT_004d5b2c = local_72;
    DAT_004d5af4 = local_14;
    DAT_004d5b28 = local_6e;
    DAT_004d5b30 = local_6a;
    DAT_004d5b34 = local_66;
    DAT_004d5b38 = local_62;
    DAT_004d5b3c = local_5e;
    DAT_004d5a90 = local_48;
    DAT_004d825c = local_44;
    DAT_004d5a94 = local_40;
    local_10 = 0;
    puVar8 = local_3c;
    puVar9 = &DAT_0065e404;
    puVar6 = local_34;
    puVar11 = &DAT_005a0548;
    do {
      uVar1 = *puVar8;
      puVar8 = puVar8 + 1;
      *puVar11 = uVar1;
      puVar11 = puVar11 + 1;
      uVar3 = *puVar6;
      puVar6 = puVar6 + 1;
      *puVar9 = uVar3;
      puVar9 = puVar9 + 1;
      local_10 = local_10 + 1;
    } while (local_10 < 7);
    iVar4 = 0;
    DAT_0059f0fc = local_35;
    puVar7 = &DAT_004c6194;
    pbVar10 = local_18;
    do {
      bVar2 = *pbVar10;
      pbVar10 = pbVar10 + 1;
      iVar4 = iVar4 + 1;
      *(uint *)(puVar7 + DAT_004d5a94 * 0xd8 + 0x4c) = (uint)bVar2;
      puVar7 = puVar7 + 0x44;
    } while (iVar4 < 3);
    iVar4 = FUN_0044fd14(0);
    if (iVar4 == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = 1;
    }
  }
  return iVar4;
}

