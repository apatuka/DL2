// FUN_00414004 @ 00414004 size=1185 sig=undefined FUN_00414004() cc=unknown
// callers: FUN_00414870
// callees: FUN_00449fe8,FUN_0049eb44,FUN_00449dec,FUN_00482f94,FUN_0046e56c,FUN_0044bea8,FUN_0046b0e4,FUN_004ae26c,FUN_0046c1f0

void FUN_00414004(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  undefined *puVar7;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_98;
  int local_94;
  undefined1 local_90 [128];
  
  iVar1 = DAT_004c5b50;
  iVar6 = DAT_004c5b50 * 0xadc;
  puVar7 = &DAT_005a43d0 + iVar6;
  FUN_0049eb44(DAT_004b7054,6,1,0xe,0x7f,local_90);
  iVar2 = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,8,1,0xe,0x7f,local_90);
  iVar3 = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,10,1,0xe,0x7f,local_90);
  iVar4 = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,0xc,1,0xe,0x7f,local_90);
  local_bc = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,0xe,1,0xe,0x7f,local_90);
  local_b8 = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,0x10,1,0xe,0x7f,local_90);
  local_a0 = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,0x12,1,0xe,0x7f,local_90);
  local_b4 = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,0x14,1,0xe,0x7f,local_90);
  local_b0 = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,0x16,1,0xe,0x7f,local_90);
  local_ac = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,0x18,1,0xe,0x7f,local_90);
  local_a8 = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,0x1a,1,0xe,0x7f,local_90);
  local_a4 = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,0x1c,1,0xe,0x7f,local_90);
  local_9c = FUN_004ae26c(local_90);
  FUN_0049eb44(DAT_004b7054,0x1e,1,0xe,0x7f,local_90);
  local_98 = FUN_004ae26c(local_90);
  if (iVar2 < 0x186a1) {
    if (iVar2 < 0) {
      iVar2 = 0;
    }
  }
  else {
    iVar2 = 100000;
  }
  if (iVar3 < 0x186a1) {
    if (iVar3 < 0) {
      iVar3 = 0;
    }
  }
  else {
    iVar3 = 100000;
  }
  if (iVar4 < 0x186a1) {
    if (iVar4 < 0) {
      iVar4 = 0;
    }
  }
  else {
    iVar4 = 100000;
  }
  if (local_bc < 0x186a1) {
    if (local_bc < 0) {
      local_bc = 0;
    }
  }
  else {
    local_bc = 100000;
  }
  if (local_b8 < 0x186a1) {
    if (local_b8 < 0) {
      local_b8 = 0;
    }
  }
  else {
    local_b8 = 100000;
  }
  if (local_a0 < 0x1389) {
    if (local_a0 < 0) {
      local_a0 = 0;
    }
  }
  else {
    local_a0 = 5000;
  }
  if (local_b4 < 0x186a1) {
    if (local_b4 < 0) {
      local_b4 = 0;
    }
  }
  else {
    local_b4 = 100000;
  }
  if (local_b0 < 0x186a1) {
    if (local_b0 < 0) {
      local_b0 = 0;
    }
  }
  else {
    local_b0 = 100000;
  }
  if (local_ac < 0x186a1) {
    if (local_ac < 0) {
      local_ac = 0;
    }
  }
  else {
    local_ac = 100000;
  }
  if (local_a8 < 0x186a1) {
    if (local_a8 < 0) {
      local_a8 = 0;
    }
  }
  else {
    local_a8 = 100000;
  }
  if (local_a4 < 0x186a1) {
    if (local_a4 < 0) {
      local_a4 = 0;
    }
  }
  else {
    local_a4 = 100000;
  }
  if (local_9c < 0xf4241) {
    if (local_9c < 0) {
      local_9c = 0;
    }
  }
  else {
    local_9c = 1000000;
  }
  if (local_98 < 0x65) {
    if (local_98 < 0) {
      local_98 = 0;
    }
  }
  else {
    local_98 = 100;
  }
  local_94 = FUN_0046b0e4(puVar7);
  if (local_a0 < local_94) {
    piVar5 = &local_a0;
  }
  else {
    piVar5 = &local_94;
  }
  local_a0 = *piVar5;
  if ((0 < local_a0) && ((&DAT_005a43f0)[iVar6] == -1)) {
    FUN_0046e56c(puVar7,DAT_0058f1f4);
  }
  FUN_0046c1f0();
  if ((short)(&DAT_005a4400)[iVar1 * 0x56e] != local_a0) {
    (&DAT_005a4400)[iVar1 * 0x56e] = (undefined2)local_a0;
    FUN_0044bea8(puVar7);
    FUN_00449fe8();
    FUN_00449dec();
  }
  if ((char)(&DAT_005a43f0)[iVar6] == DAT_0058f1f4) {
    FUN_00482f94(PTR_DAT_004d5988);
  }
  (&DAT_005a440e)[iVar1 * 0x2b7] = iVar2;
  (&DAT_005a4412)[iVar1 * 0x2b7] = iVar3;
  *(int *)(&DAT_005a4416 + iVar6) = iVar4;
  *(int *)(&DAT_005a441a + iVar6) = local_bc;
  *(int *)(&DAT_005a441e + iVar6) = local_b8;
  *(int *)(&DAT_005a4422 + iVar6) = local_b4;
  *(int *)(&DAT_005a4426 + iVar6) = local_b0;
  *(int *)(&DAT_005a442a + iVar6) = local_ac;
  *(int *)(&DAT_005a442e + iVar6) = local_a8;
  *(int *)(&DAT_005a4432 + iVar6) = local_a4;
  (&DAT_0059f16c)[DAT_0058f1f4 * 0xb6] = local_9c;
  (&DAT_005a43f7)[iVar6] = (undefined1)local_98;
  return;
}

