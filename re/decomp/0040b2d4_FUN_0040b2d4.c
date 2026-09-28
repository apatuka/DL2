// FUN_0040b2d4 @ 0040b2d4 size=252 sig=undefined FUN_0040b2d4() cc=unknown
// callers: FUN_0040b788,FUN_0040b644,FUN_0040ba64
// callees: 

bool FUN_0040b2d4(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int local_c;
  int local_8;
  
  iVar2 = 0;
  local_8 = 0;
  piVar3 = (int *)(param_1 + 0x44);
  do {
    iVar1 = *piVar3;
    if (iVar1 != 0) {
      if (*(char *)(iVar1 + 6) == '\x0f') {
        return false;
      }
      if (((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] == '\x01') ||
         ((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] == '\x06')) {
        local_8 = local_8 + 1;
      }
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 0x10);
  local_c = 1;
  piVar3 = (int *)(param_1 + 0x88);
  do {
    if (*piVar3 != 0) {
      iVar2 = 0;
      piVar4 = (int *)(&DAT_00522504 + *(short *)(param_1 + 10) * 0x2648 + *piVar3 * 0xc4);
      do {
        iVar1 = *piVar4;
        if (iVar1 != 0) {
          if (*(char *)(iVar1 + 6) == '\x0f') {
            return false;
          }
          if (((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] == '\x01') ||
             ((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] == '\x06')) {
            local_8 = local_8 + 1;
          }
        }
        iVar2 = iVar2 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar2 < 0x10);
    }
    local_c = local_c + 1;
    piVar3 = piVar3 + 1;
  } while (local_c < 0x10);
  return 5 < local_8;
}

