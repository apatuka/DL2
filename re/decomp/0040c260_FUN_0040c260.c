// FUN_0040c260 @ 0040c260 size=341 sig=undefined FUN_0040c260() cc=unknown
// callers: FUN_0040c3b8
// callees: 

void FUN_0040c260(int *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
                 undefined4 *param_5)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int local_8;
  
  *param_2 = 0;
  *param_3 = 0;
  *param_4 = 0;
  *param_5 = 0;
  iVar3 = 0;
  piVar4 = param_1 + 0x11;
  do {
    iVar2 = *piVar4;
    if ((iVar2 != 0) &&
       ((*param_1 != 9 || ((&DAT_004faf8d)[*(char *)(iVar2 + 6) * 0x24] != '\x01')))) {
      cVar1 = *(char *)(iVar2 + 6);
      if (cVar1 == '\x0f') {
        *param_3 = 1;
      }
      else if (cVar1 == '\x1a') {
        *param_2 = 1;
      }
      else if (cVar1 == '\x1c') {
        *param_4 = 1;
      }
      else if (cVar1 == '!') {
        *param_5 = 1;
      }
    }
    iVar3 = iVar3 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar3 < 0x10);
  local_8 = 1;
  piVar4 = param_1 + 0x22;
  do {
    if (*piVar4 != 0) {
      iVar3 = 0;
      piVar5 = (int *)(&DAT_00522504 + *(short *)((int)param_1 + 10) * 0x2648 + *piVar4 * 0xc4);
      do {
        if ((*piVar5 != 0) &&
           (cVar1 = *(char *)(*piVar5 + 6), (&DAT_004faf8d)[cVar1 * 0x24] == '\x01')) {
          if (cVar1 == '\x0f') {
            *param_3 = 1;
          }
          else if (cVar1 == '\x1a') {
            *param_2 = 1;
          }
          else if (cVar1 == '\x1c') {
            *param_4 = 1;
          }
          else if (cVar1 == '!') {
            *param_5 = 1;
          }
        }
        iVar3 = iVar3 + 1;
        piVar5 = piVar5 + 1;
      } while (iVar3 < 0x10);
    }
    local_8 = local_8 + 1;
    piVar4 = piVar4 + 1;
  } while (local_8 < 0x10);
  return;
}

