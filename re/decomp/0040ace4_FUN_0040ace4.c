// FUN_0040ace4 @ 0040ace4 size=161 sig=undefined FUN_0040ace4() cc=unknown
// callers: FUN_0040f4fc,FUN_0040b994,FUN_0040f2e0
// callees: 

int FUN_0040ace4(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int local_c;
  int local_8;
  
  local_8 = 0;
  iVar2 = 0;
  piVar1 = (int *)(param_1 + 0x44);
  do {
    if (*piVar1 != 0) {
      local_8 = local_8 + 1;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 0x10);
  local_c = 1;
  piVar1 = (int *)(param_1 + 0x88);
  do {
    if (*piVar1 != 0) {
      iVar2 = 0;
      piVar3 = (int *)(&DAT_00522504 + *(short *)(param_1 + 10) * 0x2648 + *piVar1 * 0xc4);
      do {
        if ((*piVar3 != 0) && ((&DAT_004faf8d)[*(char *)(*piVar3 + 6) * 0x24] == '\x01')) {
          local_8 = local_8 + 1;
        }
        iVar2 = iVar2 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar2 < 0x10);
    }
    local_c = local_c + 1;
    piVar1 = piVar1 + 1;
  } while (local_c < 0x10);
  return local_8;
}

