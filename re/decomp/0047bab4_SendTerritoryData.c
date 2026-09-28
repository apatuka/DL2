// SendTerritoryData @ 0047bab4 size=1031 sig=undefined SendTerritoryData() cc=unknown
// callers: FUN_0047b4ac
// callees: FUN_004419c8,memset,FUN_00484ee0,FUN_0047b660,FUN_00484ea4,FUN_004418ec,FUN_00484e88,FUN_00484f10,memcpy,FUN_00484f48,FUN_00484ebc
// strings: \"SendTerritoryData\"

/* auto-named from string evidence: SendTerritoryData */

void SendTerritoryData(void)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  uint *puVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  uint auStack_4c89a [2];
  char acStack_4c892 [2];
  uint auStack_4c890 [53];
  uint auStack_4c7bc [610];
  undefined4 auStack_4be34 [76102];
  undefined4 *local_10;
  int local_8;
  
  iVar3 = 0x4c;
  do {
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  local_10 = auStack_4be34;
  local_8 = 0;
  do {
    if ((local_8 == 0) || (DAT_004d5b18 < local_8)) {
      memset();
    }
    else {
      memcpy();
      if ((ushort *)auStack_4c89a[local_8 * 700] != (ushort *)0x0) {
        auStack_4c89a[local_8 * 700] = (uint)*(ushort *)auStack_4c89a[local_8 * 700];
      }
      if ((ushort *)auStack_4c89a[local_8 * 700 + 1] != (ushort *)0x0) {
        auStack_4c89a[local_8 * 700 + 1] = (uint)*(ushort *)auStack_4c89a[local_8 * 700 + 1];
      }
      puVar4 = (uint *)(acStack_4c892 + local_8 * 0xaf0 + 2);
      for (iVar3 = 0; iVar3 < acStack_4c892[local_8 * 0xaf0]; iVar3 = iVar3 + 1) {
        *puVar4 = (int)*(char *)*puVar4 & 0xffffU | (int)*(char *)(*puVar4 + 1) << 0x10;
        puVar4 = puVar4 + 1;
      }
      iVar3 = 0;
      puVar4 = auStack_4c7bc + local_8 * 700;
      do {
        if ((ushort *)*puVar4 != (ushort *)0x0) {
          *puVar4 = (uint)*(ushort *)*puVar4;
        }
        iVar3 = iVar3 + 1;
        puVar4 = puVar4 + 0xd;
      } while (iVar3 < 0x24);
      uVar5 = FUN_00484e88();
      *local_10 = uVar5;
      uVar5 = FUN_00484e88();
      local_10[1] = uVar5;
      uVar5 = FUN_00484e88();
      local_10[2] = uVar5;
      uVar5 = FUN_00484e88();
      local_10[3] = uVar5;
      uVar5 = FUN_00484e88();
      local_10[4] = uVar5;
    }
    local_8 = local_8 + 1;
    local_10 = local_10 + 700;
  } while (local_8 < 0x70);
  for (local_8 = 1; local_8 <= DAT_004d5b18; local_8 = local_8 + 1) {
  }
  puVar6 = (undefined1 *)FUN_004418ec();
  if (puVar6 != (undefined1 *)0x0) {
    memset();
    for (local_8 = 1; local_8 <= DAT_004d5b18; local_8 = local_8 + 1) {
      iVar3 = FUN_00484ea4();
      while (iVar3 != 0) {
        uVar1 = FUN_00484ee0();
        *puVar6 = uVar1;
        uVar2 = FUN_00484f10();
        *(undefined2 *)(puVar6 + 2) = uVar2;
        FUN_00484f48();
        puVar6 = puVar6 + 0x30;
        iVar3 = FUN_00484ebc();
      }
      iVar3 = FUN_00484ea4();
      while (iVar3 != 0) {
        uVar1 = FUN_00484ee0();
        *puVar6 = uVar1;
        uVar2 = FUN_00484f10();
        *(undefined2 *)(puVar6 + 2) = uVar2;
        FUN_00484f48();
        puVar6 = puVar6 + 0x30;
        iVar3 = FUN_00484ebc();
      }
      iVar3 = FUN_00484ea4();
      while (iVar3 != 0) {
        uVar1 = FUN_00484ee0();
        *puVar6 = uVar1;
        uVar2 = FUN_00484f10();
        *(undefined2 *)(puVar6 + 2) = uVar2;
        FUN_00484f48();
        puVar6 = puVar6 + 0x30;
        iVar3 = FUN_00484ebc();
      }
      iVar3 = FUN_00484ea4();
      while (iVar3 != 0) {
        uVar1 = FUN_00484ee0();
        *puVar6 = uVar1;
        uVar2 = FUN_00484f10();
        *(undefined2 *)(puVar6 + 2) = uVar2;
        FUN_00484f48();
        puVar6 = puVar6 + 0x30;
        iVar3 = FUN_00484ebc();
      }
      iVar3 = FUN_00484ea4();
      while (iVar3 != 0) {
        uVar1 = FUN_00484ee0();
        *puVar6 = uVar1;
        uVar2 = FUN_00484f10();
        *(undefined2 *)(puVar6 + 2) = uVar2;
        FUN_00484f48();
        puVar6 = puVar6 + 0x30;
        iVar3 = FUN_00484ebc();
      }
    }
    iVar3 = FUN_004418ec();
    if (iVar3 == 0) {
      FUN_004419c8();
    }
    else {
      memcpy();
      memcpy();
      FUN_004419c8();
      FUN_0047b660();
      FUN_004419c8();
    }
  }
  return;
}

