// FUN_00413b3c @ 00413b3c size=139 sig=undefined FUN_00413b3c() cc=unknown
// callers: FUN_00413bc8,FUN_00413eb4
// callees: FUN_00413980,FUN_0049eb44

void FUN_00413b3c(void)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 auStack_20 [5];
  
  uVar2 = (int)*(short *)(DAT_006534c0 + 2) & 0xff;
  puVar3 = &DAT_004b703c;
  puVar4 = auStack_20;
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  if (uVar2 < 5) {
    iVar1 = FUN_0049eb44(DAT_004b7028,0x11,1,0xc,0,0);
    if (iVar1 == 0) {
      *(undefined1 *)(DAT_006534c0 + 4) = 0;
    }
    else {
      *(undefined1 *)(DAT_006534c0 + 4) = *(undefined1 *)(auStack_20 + uVar2);
    }
    FUN_00413980(uVar2);
  }
  else {
    *(undefined1 *)(DAT_006534c0 + 4) = 0;
    FUN_0049eb44(DAT_004b7028,0x13,1,0xb,1,0);
  }
  return;
}

