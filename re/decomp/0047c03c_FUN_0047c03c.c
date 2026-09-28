// FUN_0047c03c @ 0047c03c size=236 sig=undefined FUN_0047c03c() cc=unknown
// callers: FUN_0047c53c
// callees: FUN_0047510c,FUN_00445710,memcpy

void FUN_0047c03c(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int local_8;
  
  memcpy(&DAT_00645370,param_1,0xc940);
  local_8 = 0;
  piVar3 = &DAT_006453c4;
  do {
    if (*piVar3 != 0) {
      iVar1 = FUN_0047510c(*piVar3);
      *piVar3 = iVar1;
    }
    if (piVar3[1] != 0) {
      iVar1 = FUN_0047510c(piVar3[1]);
      piVar3[1] = iVar1;
    }
    if (piVar3[-7] != 0) {
      piVar3[-7] = (int)(&DAT_005a43d0 + piVar3[-7] * 0xadc);
    }
    if (piVar3[-6] != 0) {
      piVar3[-6] = (int)(&DAT_005a43d0 + piVar3[-6] * 0xadc);
    }
    if (piVar3[-5] != 0) {
      piVar3[-5] = (int)(&DAT_005a43d0 + piVar3[-5] * 0xadc);
    }
    if (piVar3[-4] != 0) {
      piVar3[-4] = (int)(&DAT_005a43d0 + piVar3[-4] * 0xadc);
    }
    iVar1 = 0;
    piVar4 = piVar3 + -3;
    do {
      if (*piVar4 != 0) {
        iVar2 = FUN_0047510c(*piVar4);
        *piVar4 = iVar2;
      }
      iVar1 = iVar1 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar1 < 3);
    *(undefined2 *)((int)piVar3 + -0x1e) = 0;
    local_8 = local_8 + 1;
    piVar3 = piVar3 + 0x17;
  } while (local_8 < 0x230);
  FUN_00445710();
  return;
}

