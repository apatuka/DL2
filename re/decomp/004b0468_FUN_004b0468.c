// FUN_004b0468 @ 004b0468 size=255 sig=undefined FUN_004b0468() cc=unknown
// callers: FUN_004b0654
// callees: FUN_004b0428

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004b0468(uint *param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  undefined *puVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = 0;
  if (param_2 < 0x1000) {
    uVar1 = 0xffffffff;
  }
  else {
    param_1[2] = 1;
    param_1[3] = (uint)param_1;
    *param_1 = param_2;
    param_1[1] = param_3;
    param_1[0x23] = (uint)DAT_005211ec;
    param_1[0x24] = 0;
    if (DAT_005211ec == (uint *)0x0) {
      _DAT_005211f0 = param_1;
    }
    else {
      DAT_005211ec[0x24] = (uint)param_1;
    }
    DAT_005211ec = param_1;
    param_1[0x25] = 0;
    puVar3 = param_1 + 0x26;
    if (DAT_005211f4 == (uint *)0x0) {
      uVar5 = DAT_005211e0 * 2 + 3 & 0xfffffffc;
      DAT_005211f4 = param_1 + 0x27;
      *puVar3 = uVar5;
      puVar3 = (uint *)((int)puVar3 + uVar5 + 4);
      FUN_004b0428();
      iVar4 = uVar5 + 4;
    }
    uVar5 = (param_2 - 0xa0) - iVar4;
    *puVar3 = uVar5 + 1;
    *(undefined4 *)((int)puVar3 + (uVar5 + 1 & 0xfffffffc) + 4) = 2;
    puVar2 = PTR_DAT_00521204;
    if (uVar5 < DAT_005211e0) {
      puVar2 = (undefined *)((int)DAT_005211f4 + uVar5 * 2 + -0xc);
    }
    puVar3[1] = *(uint *)(puVar2 + 4);
    puVar3[2] = (uint)puVar2;
    *(uint **)(puVar3[1] + 8) = puVar3;
    *(uint **)(puVar2 + 4) = puVar3;
    *(uint *)((int)puVar3 + uVar5) = uVar5 + 4;
    uVar1 = 0;
  }
  return uVar1;
}

