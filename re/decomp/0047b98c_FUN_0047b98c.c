// FUN_0047b98c @ 0047b98c size=295 sig=undefined FUN_0047b98c() cc=unknown
// callers: FUN_0047b4ac
// callees: memset,FUN_0047b660,memcpy

void FUN_0047b98c(undefined4 param_1)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  int *piVar4;
  undefined1 local_c948 [56];
  int local_c910 [11243];
  undefined4 uStack_1964;
  undefined4 uStack_1960;
  undefined1 *puStack_195c;
  undefined2 *puStack_1958;
  undefined4 uStack_1954;
  char *local_8;
  
  iVar1 = 0xc;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  iVar1 = 0;
  piVar4 = local_c910;
  local_8 = &DAT_00645376;
  do {
    if (*local_8 == '\0') {
      uStack_1954 = 0x5c;
      puStack_1958 = (undefined2 *)0x0;
      puStack_195c = local_c948 + iVar1 * 0x5c;
      uStack_1960 = 0x47b9df;
      memset();
    }
    else {
      uStack_1954 = 0x5c;
      puStack_1958 = &DAT_00645370 + iVar1 * 0x2e;
      puStack_195c = local_c948 + iVar1 * 0x5c;
      uStack_1960 = 0x47ba14;
      memcpy();
      if (*piVar4 != 0) {
        *piVar4 = (int)*(short *)(*piVar4 + 0x1a);
      }
      if (piVar4[1] != 0) {
        piVar4[1] = (int)*(short *)(piVar4[1] + 0x1a);
      }
      if (piVar4[2] != 0) {
        piVar4[2] = (int)*(short *)(piVar4[2] + 0x1a);
      }
      if (piVar4[3] != 0) {
        piVar4[3] = (int)*(short *)(piVar4[3] + 0x1a);
      }
      if ((ushort *)piVar4[7] != (ushort *)0x0) {
        piVar4[7] = (uint)*(ushort *)piVar4[7];
      }
      if ((ushort *)piVar4[8] != (ushort *)0x0) {
        piVar4[8] = (uint)*(ushort *)piVar4[8];
      }
      iVar3 = 0;
      puVar2 = (uint *)(piVar4 + 4);
      do {
        if ((ushort *)*puVar2 != (ushort *)0x0) {
          *puVar2 = (uint)*(ushort *)*puVar2;
        }
        iVar3 = iVar3 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar3 < 3);
    }
    iVar1 = iVar1 + 1;
    piVar4 = piVar4 + 0x17;
    local_8 = local_8 + 0x5c;
  } while (iVar1 < 0x230);
  uStack_1954 = 0xc940;
  puStack_1958 = (undefined2 *)local_c948;
  puStack_195c = (undefined1 *)0x4;
  uStack_1960 = param_1;
  uStack_1964 = 0x47baab;
  FUN_0047b660();
  return;
}

