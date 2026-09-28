// FUN_0041d2bc @ 0041d2bc size=342 sig=undefined FUN_0041d2bc() cc=unknown
// callers: CheckBuilding,FUN_0041d414
// callees: FUN_0041c814,FUN_004761b0,FUN_0041c378,FUN_004762a8,MoveLaborToHousing,FUN_0044eb4c,FUN_0041c36c,FUN_0049eb44

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041d2bc(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  undefined4 local_1c [5];
  
  bVar5 = DAT_0053b33c == 0;
  DAT_0053b33c = (uint)bVar5;
  if (bVar5) {
    *(ushort *)(DAT_0053b850 + 2) = *(ushort *)(DAT_0053b850 + 2) | 4;
  }
  else {
    *(ushort *)(DAT_0053b850 + 2) = *(ushort *)(DAT_0053b850 + 2) & 0xfffb;
  }
  if (DAT_0053b33c == 0) {
    FUN_0049eb44(DAT_004b7758,0x1a,1,0xb,0,0);
  }
  else {
    FUN_0049eb44(DAT_004b7758,0x1a,1,0xb,1,0);
  }
  puVar2 = local_1c;
  FUN_0041c814();
  if (DAT_0053b33c == 0) {
    iVar3 = 0;
    do {
      *(ushort *)(DAT_0053b850 + 2) =
           *(ushort *)(DAT_0053b850 + 2) & ~(0x100 << ((byte)iVar3 & 0x1f));
      iVar4 = *(int *)(DAT_0053b850 + 0x18 + iVar3 * 4);
      if (0 < iVar4) {
        for (; iVar4 != 0; iVar4 = iVar4 + -1) {
          MoveLaborToHousing(DAT_0053b84c,DAT_0053b850,iVar3);
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 5);
  }
  else {
    _DAT_0053b848 = (int)*(char *)(DAT_0053b850 + 7);
    DAT_0053b84c = &DAT_005a43d0 + *(short *)(DAT_0053b850 + 8) * 0xadc;
    FUN_0044eb4c(PTR_DAT_004d5988,DAT_0053b84c,_DAT_0053b848,&DAT_0053b854,0);
  }
  iVar3 = 0;
  puVar1 = (undefined4 *)(DAT_0053b850 + 0x18);
  do {
    *puVar2 = *puVar1;
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar3 < 5);
  FUN_004761b0(DAT_0053b84c,DAT_0053b850,local_1c,
               CONCAT31((int3)((uint)puVar2 >> 8),DAT_0053b84c[0x9ae]));
  FUN_004762a8(DAT_0053b84c,DAT_0053b850);
  FUN_0041c378();
  FUN_0041c36c();
  return;
}

