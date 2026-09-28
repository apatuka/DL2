// FUN_0040b1b8 @ 0040b1b8 size=282 sig=undefined FUN_0040b1b8() cc=unknown
// callers: FUN_0040b788,FUN_0040b644,FUN_0040ba64
// callees: 

bool FUN_0040b1b8(int param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int local_c;
  int local_8;
  
  local_8 = 0;
  iVar4 = 0;
  piVar3 = (int *)(param_1 + 0x44);
  do {
    iVar2 = *piVar3;
    if (iVar2 != 0) {
      if (*(char *)(iVar2 + 6) == '\x1a') {
        return false;
      }
      cVar1 = (&DAT_004faf87)[*(char *)(iVar2 + 6) * 0x24];
      if (((cVar1 == '\x01') || (cVar1 == '\a')) || (cVar1 == '\x06')) {
        local_8 = local_8 + 1;
      }
    }
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar4 < 0x10);
  local_c = 1;
  piVar3 = (int *)(param_1 + 0x88);
  do {
    if (*piVar3 != 0) {
      iVar4 = 0;
      piVar5 = (int *)(&DAT_00522504 + *(short *)(param_1 + 10) * 0x2648 + *piVar3 * 0xc4);
      do {
        iVar2 = *piVar5;
        if (iVar2 != 0) {
          if (*(char *)(iVar2 + 6) == '\x1a') {
            return false;
          }
          cVar1 = (&DAT_004faf87)[*(char *)(iVar2 + 6) * 0x24];
          if (((cVar1 == '\x01') || (cVar1 == '\a')) || (cVar1 == '\x06')) {
            local_8 = local_8 + 1;
          }
        }
        iVar4 = iVar4 + 1;
        piVar5 = piVar5 + 1;
      } while (iVar4 < 0x10);
    }
    local_c = local_c + 1;
    piVar3 = piVar3 + 1;
  } while (local_c < 0x10);
  return 5 < local_8;
}

