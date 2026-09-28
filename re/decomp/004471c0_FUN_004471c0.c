// FUN_004471c0 @ 004471c0 size=750 sig=undefined FUN_004471c0() cc=unknown
// callers: FUN_0046e730,FUN_00446084,FUN_00445d30,FUN_00417d54
// callees: ReLinkArmy,SyncCreateUnit,DeleteUnit,FUN_00446c34,FUN_00423690,FUN_00446e30,FUN_0046e56c,FUN_00447190,FUN_00447158,FUN_00446bf0,CheckDiscovery,FUN_0046e6b8

void FUN_004471c0(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar3 = FUN_00446c34(param_1);
  if ((iVar3 != 0) || (*(char *)(param_1 + 0x20) == -1)) {
    iVar3 = *(int *)(param_1 + 0x76);
    while (iVar3 != 0) {
      iVar1 = *(int *)(iVar3 + 0x54);
      iVar4 = FUN_00446bf0(iVar3);
      if (iVar4 == 0) {
        DeleteUnit(iVar3);
        iVar3 = iVar1;
      }
      else {
        ReLinkArmy(iVar3,param_1,param_1 + 0x76,param_1 + 0x7a);
        iVar3 = iVar1;
      }
    }
  }
  iVar3 = *(int *)(param_1 + 0x7a);
  while (iVar1 = iVar3, iVar1 != 0) {
    iVar3 = *(int *)(iVar1 + 0x54);
    CheckDiscovery(param_1,(int)*(char *)(iVar1 + 8),(int)*(char *)(iVar1 + 6));
    iVar4 = FUN_00446bf0(iVar1);
    if ((iVar4 == 0) &&
       ((((*(char *)(iVar1 + 7) == '\x03' &&
          (*(char *)(iVar1 + 6) < *(char *)(param_1 + 0x6d + (int)*(char *)(iVar1 + 8)))) ||
         ((*(char *)(iVar1 + 7) == '\r' &&
          ('\n' < *(char *)(param_1 + 0x6d + (int)*(char *)(iVar1 + 8)))))) &&
        (DAT_004d5aa0 == '\0')))) {
      FUN_00423690((int)*(char *)(iVar1 + 8),0x20,iVar1 + 0xb,param_1,0,0);
      DeleteUnit(iVar1);
    }
    else if ((*(char *)(iVar1 + 8) == *(char *)(param_1 + 0x20)) ||
            (iVar4 = FUN_00446e30(param_1,(int)*(char *)(iVar1 + 8)), iVar4 != 0)) {
      ReLinkArmy(iVar1,param_1,param_1 + 0x7a,param_1 + 0x76);
      if (*(char *)(iVar1 + 8) != *(char *)(param_1 + 0x20)) {
        FUN_0046e56c(param_1,(int)*(char *)(iVar1 + 8));
        if ((*(uint *)(param_1 + 0x8a8) != 0) &&
           ((1 << (*(byte *)(param_1 + 0x20) & 0x1f) & *(uint *)(param_1 + 0x8a8)) == 0)) {
          *(undefined4 *)(param_1 + 0x8a8) = 0;
        }
      }
    }
  }
  iVar3 = *(int *)(param_1 + 0x76);
  while (iVar1 = iVar3, iVar1 != 0) {
    iVar3 = *(int *)(iVar1 + 0x54);
    CheckDiscovery(param_1,(int)*(char *)(iVar1 + 8),(int)*(char *)(iVar1 + 6));
    if (((*(char *)(iVar1 + 7) == '\x03') &&
        (*(char *)(iVar1 + 6) < *(char *)(param_1 + 0x6d + (int)*(char *)(iVar1 + 8)))) ||
       ((*(char *)(iVar1 + 7) == '\r' &&
        ('\n' < *(char *)(param_1 + 0x6d + (int)*(char *)(iVar1 + 8)))))) {
      if (DAT_004d5aa0 == '\0') {
        FUN_00423690((int)*(char *)(iVar1 + 8),0x20,iVar1 + 0xb,param_1,0,0);
        DeleteUnit(iVar1);
      }
    }
    else if ((((*(char *)(iVar1 + 7) == '\x03') || (*(char *)(iVar1 + 7) == '\r')) &&
             (iVar4 = FUN_00446e30(param_1,(int)*(char *)(iVar1 + 8)), iVar4 == 0)) &&
            ((*(short *)(param_1 + 0x30) == 0 || (*(char *)(param_1 + 0x20) != *(char *)(iVar1 + 8))
             ))) {
      ReLinkArmy(iVar1,param_1,param_1 + 0x76,param_1 + 0x7a);
    }
    else {
      iVar4 = FUN_00446bf0(iVar1);
      if ((iVar4 != 0) &&
         ((*(char *)(param_1 + 0x20) != *(char *)(iVar1 + 8) &&
          (iVar4 = FUN_00446e30(param_1,(int)*(char *)(iVar1 + 8)), iVar4 == 0)))) {
        ReLinkArmy(iVar1,param_1,param_1 + 0x76,param_1 + 0x7a);
      }
    }
  }
  if (DAT_004d5aa0 != '\0') {
    FUN_0046e6b8(param_1);
  }
  for (puVar5 = (undefined4 *)&DAT_00645370; puVar5 < &DAT_00651cb0; puVar5 = puVar5 + 0x17) {
    *(ushort *)((int)puVar5 + 2) = *(ushort *)((int)puVar5 + 2) & 0xfffe;
    iVar3 = FUN_00446bf0(puVar5);
    if (iVar3 != 0) {
      *(ushort *)((int)puVar5 + 2) = *(ushort *)((int)puVar5 + 2) | 1;
    }
    uVar2 = FUN_00447190(puVar5);
    *(undefined1 *)((int)puVar5 + 10) = uVar2;
    puVar5[0x10] = puVar5[0xf];
    puVar5[0xe] = puVar5[0xf];
    if (((*(char *)((int)puVar5 + 6) == '#') && (puVar5[0x12] == 0)) &&
       (iVar3 = SyncCreateUnit(puVar5[0xf],(int)*(char *)(puVar5 + 2),0x24), iVar3 != 0)) {
      *(undefined4 **)(iVar3 + 0x48) = puVar5;
      puVar5[0x12] = iVar3;
    }
    if ((*(short *)(puVar5 + 0xb) != 0) && (iVar3 = FUN_00446bf0(puVar5), iVar3 == 0)) {
      *(undefined1 *)((int)puVar5 + 0x25) = 0xb;
    }
    if ((*(char *)((int)puVar5 + 6) != '\0') && (*(char *)((int)puVar5 + 0x25) == '\0')) {
      FUN_00447158(puVar5);
    }
  }
  if (*(short *)(param_1 + 0x30) != 0) {
    if (*(char *)(param_1 + 0x21) == '\0') {
      CheckDiscovery(param_1,(int)*(char *)(param_1 + 0x20),0x1e);
    }
    else {
      CheckDiscovery(param_1,(int)*(char *)(param_1 + 0x20),0x19);
    }
  }
  return;
}

