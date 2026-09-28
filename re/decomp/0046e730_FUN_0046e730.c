// FUN_0046e730 @ 0046e730 size=570 sig=undefined FUN_0046e730() cc=unknown
// callers: FUN_004618e8,WinMain
// callees: FUN_0046c3fc,FUN_0046e338,FUN_0045ac80,FUN_004837fc,FUN_0046c780,FUN_0046e6b8,FUN_004474b0,FUN_00447090,memset,FUN_0047dd24,FUN_004471c0

void FUN_0046e730(int param_1)

{
  ushort uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  int local_10;
  undefined4 *local_c;
  int local_8;
  
  local_c = &DAT_005a4eac;
  DAT_0053b8cc = 1;
  DAT_004d59b8 = 0;
  FUN_00447090();
  for (local_8 = 0; local_8 <= DAT_004d5b18; local_8 = local_8 + 1) {
    local_10 = 0;
    do {
      iVar3 = local_c[local_10 * 0xd + 0x55];
      if (iVar3 == 0) {
        uVar1 = *(ushort *)((int)local_c + local_10 * 0x34 + 0x142);
        if ((((int)(short)uVar1 & 0xf000U) == 0x4000) && ((uVar1 & 0x100) == 0)) {
          iVar3 = local_c[local_10 * 0xd + 0x96];
          iVar5 = 0;
          *(undefined1 *)((int)local_c + local_10 * 0x34 + 0x15a) = *(undefined1 *)(iVar3 + 4);
          *(undefined1 *)((int)local_c + local_10 * 0x34 + 0x159) = *(undefined1 *)(iVar3 + 6);
          puVar2 = (undefined4 *)((int)local_c + local_10 * 0x34 + 0x15e);
          *(undefined1 *)((int)local_c + local_10 * 0x34 + 0x15b) = *(undefined1 *)(iVar3 + 0x14);
          puVar4 = (undefined4 *)(iVar3 + 0x18);
          do {
            *puVar2 = *puVar4;
            iVar5 = iVar5 + 1;
            puVar2 = puVar2 + 1;
            puVar4 = puVar4 + 1;
          } while (iVar5 < 5);
        }
        else if (((int)*(short *)((int)local_c + local_10 * 0x34 + 0x142) & 0xf000U) == 0x6000) {
          iVar3 = local_c[local_10 * 0xd + 0x18d];
          iVar5 = 0;
          *(undefined1 *)((int)local_c + local_10 * 0x34 + 0x15a) = *(undefined1 *)(iVar3 + 4);
          *(undefined1 *)((int)local_c + local_10 * 0x34 + 0x159) = *(undefined1 *)(iVar3 + 6);
          puVar2 = (undefined4 *)((int)local_c + local_10 * 0x34 + 0x15e);
          *(undefined1 *)((int)local_c + local_10 * 0x34 + 0x15b) = *(undefined1 *)(iVar3 + 0x14);
          puVar4 = (undefined4 *)(iVar3 + 0x18);
          do {
            *puVar2 = *puVar4;
            iVar5 = iVar5 + 1;
            puVar2 = puVar2 + 1;
            puVar4 = puVar4 + 1;
          } while (iVar5 < 5);
        }
        else {
          *(undefined1 *)((int)local_c + local_10 * 0x34 + 0x15a) = 0;
          iVar3 = 0;
          puVar2 = (undefined4 *)((int)local_c + local_10 * 0x34 + 0x15e);
          do {
            iVar3 = iVar3 + 1;
            *puVar2 = 0;
            puVar2 = puVar2 + 1;
          } while (iVar3 < 5);
        }
      }
      else if ((&DAT_004f9dc5)[*(char *)(iVar3 + 4) * 0x32] == '\x01') {
        iVar5 = 0;
        *(undefined1 *)((int)local_c + local_10 * 0x34 + 0x15a) = *(undefined1 *)(iVar3 + 4);
        *(undefined1 *)((int)local_c + local_10 * 0x34 + 0x159) = *(undefined1 *)(iVar3 + 6);
        puVar2 = (undefined4 *)((int)local_c + local_10 * 0x34 + 0x15e);
        *(undefined1 *)((int)local_c + local_10 * 0x34 + 0x15b) = *(undefined1 *)(iVar3 + 0x14);
        puVar4 = (undefined4 *)(iVar3 + 0x18);
        do {
          *puVar2 = *puVar4;
          iVar5 = iVar5 + 1;
          puVar2 = puVar2 + 1;
          puVar4 = puVar4 + 1;
        } while (iVar5 < 5);
      }
      *(undefined1 *)(local_c + local_10 * 0xd + 0x57) =
           *(undefined1 *)(local_c + local_10 * 0xd + 0x54);
      *(undefined2 *)((int)local_c + local_10 * 0x34 + 0x172) =
           *(undefined2 *)((int)local_c + local_10 * 0x34 + 0x142);
      local_10 = local_10 + 1;
    } while (local_10 < 0x24);
    FUN_0046c3fc(local_c,local_14,local_18);
    *(undefined1 *)((int)local_c + 0x36) = local_18[0];
    local_c[7] = local_c[7] & 0xffffffbf;
    *(undefined2 *)(local_c + 0xe) = *(undefined2 *)(local_c + 0xc);
    if (param_1 == 0) {
      FUN_004471c0(local_c);
      FUN_0046e6b8(local_c);
      FUN_004474b0(local_c);
    }
    local_c = local_c + 0x2b7;
  }
  memset(&DAT_0059f104,0,0x50);
  DAT_004d5a9c = 0;
  FUN_0046e338();
  FUN_0047dd24();
  FUN_0046c780();
  if ((param_1 == 0) && (1 < DAT_0059f154)) {
    FUN_004837fc();
  }
  if (((DAT_004d59b4 == 1) && (DAT_00657de0 != 0)) &&
     (*(char *)(DAT_00657de0 + 0x66 + DAT_0058f1f4) < '\x03')) {
    FUN_0045ac80();
  }
  return;
}

