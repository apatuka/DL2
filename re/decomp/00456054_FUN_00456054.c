// FUN_00456054 @ 00456054 size=251 sig=undefined FUN_00456054() cc=unknown
// callers: FUN_004570e0
// callees: FUN_00447c2c,FUN_00450e04,FUN_00448008

int FUN_00456054(void)

{
  int iVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  short sVar5;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  sVar5 = 0;
  local_28 = 0;
  local_24 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = -1;
  sVar3 = 0x4000;
  local_20 = DAT_0057cdfc;
  for (iVar1 = DAT_0057cdfc; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x48)) {
    uVar4 = 0;
    if (sVar5 < *(short *)(iVar1 + 10)) {
      uVar4 = 0x20;
      sVar5 = *(short *)(iVar1 + 10);
    }
    if (*(short *)(iVar1 + 0x32) < sVar3) {
      uVar4 = uVar4 + 0x10;
      sVar3 = *(short *)(iVar1 + 0x32);
    }
    iVar2 = FUN_00450e04(iVar1);
    if (iVar2 != 0) {
      uVar4 = uVar4 + 8;
    }
    iVar2 = FUN_00448008(iVar1);
    if (local_18 < iVar2) {
      uVar4 = uVar4 + 4;
      local_18 = FUN_00448008(iVar1);
    }
    iVar2 = FUN_00447c2c(iVar1);
    if (local_14 < iVar2) {
      uVar4 = uVar4 + 2;
      local_14 = FUN_00447c2c(iVar1);
    }
    if (local_1c < uVar4) {
      local_28 = iVar1;
      local_20 = local_24;
      local_1c = uVar4;
    }
    local_24 = iVar1;
  }
  if (local_28 != 0) {
    if (DAT_0057cdfc == local_28) {
      DAT_0057cdfc = *(int *)(DAT_0057cdfc + 0x48);
    }
    else {
      *(undefined4 *)(local_20 + 0x48) = *(undefined4 *)(local_28 + 0x48);
    }
  }
  return local_28;
}

