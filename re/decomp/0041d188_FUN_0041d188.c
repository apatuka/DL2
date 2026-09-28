// FUN_0041d188 @ 0041d188 size=299 sig=undefined FUN_0041d188() cc=unknown
// callers: FUN_0041d2b4
// callees: FUN_004761b0,FUN_0044a000,FUN_004762a8,FUN_004493dc,FUN_00482d3c,FUN_0046f0e0,FUN_0044bea8,FUN_004a4025

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041d188(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_18 [5];
  
  if (DAT_004b7758 != 0) {
    FUN_004a4025(DAT_004b7758);
    DAT_004b7758 = 0;
  }
  _DAT_004c5550 = 0;
  _DAT_004c5570 = 0;
  _DAT_004c5590 = 0;
  _DAT_004c55b0 = 0;
  _DAT_004c55d0 = 0;
  DAT_004c5490 = 0;
  _DAT_004c54b0 = 0;
  _DAT_004c54d0 = 0;
  _DAT_004c54f0 = 0;
  _DAT_004c5510 = 0;
  _DAT_004c5530 = 0;
  DAT_004c5450 = DAT_0053b874;
  DAT_004d59b4 = DAT_0053b344;
  FUN_004493dc(0);
  puVar3 = local_18;
  FUN_00482d3c();
  if (DAT_0053b33c == 0) {
    *(ushort *)(DAT_0053b850 + 2) = *(ushort *)(DAT_0053b850 + 2) & 0xfffb;
  }
  else {
    *(ushort *)(DAT_0053b850 + 2) = *(ushort *)(DAT_0053b850 + 2) | 4;
  }
  if (*(char *)(DAT_0053b850 + 5) == '\x10') {
    FUN_0046f0e0(0);
  }
  FUN_0044bea8(DAT_0053b84c);
  iVar2 = 0;
  puVar1 = (undefined4 *)(DAT_0053b850 + 0x18);
  do {
    *puVar3 = *puVar1;
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar2 < 5);
  FUN_004761b0(DAT_0053b84c,DAT_0053b850,local_18,
               CONCAT31((int3)((uint)puVar3 >> 8),*(undefined1 *)(DAT_0053b84c + 0x9ae)));
  FUN_004762a8(DAT_0053b84c,DAT_0053b850);
  FUN_0044a000();
  return;
}

