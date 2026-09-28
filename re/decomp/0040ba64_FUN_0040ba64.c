// FUN_0040ba64 @ 0040ba64 size=279 sig=undefined FUN_0040ba64() cc=unknown
// callers: FUN_0040febc
// callees: FUN_0040b2d4,memset,FUN_0040b1b8,FUN_0044ff80,FUN_0040b3d0,FUN_0040b4d0

int FUN_0040ba64(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int local_68 [21];
  undefined *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  memset(local_68,0,0x54);
  iVar2 = 0;
  piVar3 = param_1 + 0x11;
  do {
    if (*piVar3 != 0) {
      local_68[(char)(&DAT_004faf87)[*(char *)(*piVar3 + 6) * 0x24]] =
           local_68[(char)(&DAT_004faf87)[*(char *)(*piVar3 + 6) * 0x24]] + 1;
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 0x10);
  local_8 = -1;
  local_c = 0;
  local_10 = 1;
  local_14 = &DAT_004b6644;
  while( true ) {
    iVar4 = -1;
    iVar2 = *(int *)(local_14 + *param_1 * 0x40);
    if (iVar2 == 0) {
      return local_c;
    }
    iVar1 = FUN_0044ff80(iVar2);
    if (iVar1 != 0) break;
    if ((((iVar2 == 0xb) || (iVar2 == 6)) || (iVar2 == 0xd)) || (iVar2 == 0x11)) {
      if ((((local_68[iVar2] == 0) && (iVar2 == 0xb)) && (iVar1 = FUN_0040b1b8(param_1), iVar1 != 0)
          ) || (((iVar2 == 6 && (iVar1 = FUN_0040b2d4(param_1), iVar1 != 0)) ||
                (((iVar2 == 0xd && (iVar1 = FUN_0040b3d0(param_1), iVar1 != 0)) ||
                 ((iVar2 == 0x11 && (iVar1 = FUN_0040b4d0(param_1), iVar1 != 0)))))))) {
        iVar4 = 10000;
      }
    }
    else {
      iVar4 = 0x10 - local_68[iVar2];
    }
    if (local_8 < iVar4) {
      local_c = iVar2;
      local_8 = iVar4;
    }
    local_10 = local_10 + 1;
    local_14 = local_14 + 4;
    if (0xf < local_10) {
      return local_c;
    }
  }
  return local_c;
}

