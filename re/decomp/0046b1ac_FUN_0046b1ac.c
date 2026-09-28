// FUN_0046b1ac @ 0046b1ac size=510 sig=undefined FUN_0046b1ac() cc=unknown
// callers: FUN_0046c7d4
// callees: FUN_0044fe1c,FUN_0044c9a0,FUN_0046b074,FUN_0046b0e4,FUN_004237d0

void FUN_0046b1ac(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int local_c;
  int local_8;
  
  puVar5 = &DAT_005a4eac;
  for (iVar7 = 1; iVar7 <= DAT_004d5b18; iVar7 = iVar7 + 1) {
    if (((*(char *)(puVar5 + 8) != -1) && (*(short *)(puVar5 + 0xc) != 0)) &&
       ((*(char *)(puVar5 + 8) != DAT_0058f1f4 || (iVar1 = FUN_0044fe1c(10), iVar1 == 0)))) {
      local_c = FUN_0046b0e4(puVar5);
      iVar6 = (int)*(short *)(puVar5 + 0xc);
      iVar1 = local_c;
      if (iVar6 <= local_c) {
        iVar1 = *(int *)(&DAT_004d5808 + *(char *)((int)puVar5 + 0x21) * 4);
        iVar2 = FUN_0046b0e4(puVar5);
        uVar3 = (*(short *)(puVar5 + 0xc) * 100) / iVar2;
        iVar2 = (int)uVar3 >> 1;
        if (iVar2 < 0) {
          iVar2 = iVar2 + (uint)((uVar3 & 1) != 0);
        }
        if (*(char *)((int)puVar5 + 0x29) == '\0') {
          iVar1 = (iVar1 * (100 - iVar2) *
                  (int)*(short *)(&DAT_00559f5e +
                                 (char)(&DAT_0059f162)[*(char *)(puVar5 + 8) * 0x2d8] * 2)) / 10000;
        }
        else {
          iVar1 = -10;
        }
        if (DAT_004d5b08 != 0) {
          iVar1 = iVar1 * 2;
        }
        local_8 = (iVar6 * iVar1) / 100 + iVar6;
        if ((0 < iVar1) && (local_8 < 100)) {
          local_8 = local_8 + 0x14;
        }
        if (iVar6 == local_8) {
          local_8 = local_8 + 0x19;
        }
        if (local_8 < local_c) {
          piVar4 = &local_8;
        }
        else {
          piVar4 = &local_c;
        }
        iVar1 = *piVar4;
      }
      local_8 = iVar1;
      if (param_1 != 0) {
        *(undefined2 *)(puVar5 + 0xc) = (undefined2)local_8;
        iVar1 = local_8 / 100 - (iVar6 + -100);
        if (0 < iVar1) {
          FUN_0044c9a0(puVar5,iVar1,0,0,0);
        }
        if ((iVar6 == local_8) || (iVar1 = FUN_0046b074(puVar5), local_8 < iVar1)) {
          if ((iVar6 != local_8) && (iVar1 = FUN_0046b0e4(puVar5), iVar1 <= local_8)) {
            FUN_004237d0((int)*(char *)(puVar5 + 8),0x35,puVar5,0,0,0,
                         (int)*(short *)((int)puVar5 + 0x1a),0);
          }
        }
        else {
          FUN_004237d0((int)*(char *)(puVar5 + 8),0x34,puVar5,0,0,0,
                       (int)*(short *)((int)puVar5 + 0x1a),0);
        }
      }
      *(short *)((int)puVar5 + 0x32) = (short)(((local_8 - iVar6) * 100) / iVar6);
    }
    puVar5 = puVar5 + 0x2b7;
  }
  return;
}

