// FUN_00446440 @ 00446440 size=936 sig=undefined FUN_00446440() cc=unknown
// callers: FUN_00446b94,FUN_00446440,FUN_00446b3c
// callees: FUN_00446440,FUN_004412d4,FUN_00445b94,FUN_0044d1e4

void FUN_00446440(int param_1,int param_2,int param_3,int param_4,int param_5,uint param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined *puVar6;
  ushort *local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  ushort local_a;
  int local_8;
  
  iVar2 = param_5;
  iVar1 = param_4;
  DAT_004c5294 = DAT_004c5294 + 1;
  if (DAT_00564218 < DAT_004c5294) {
    DAT_00564218 = DAT_004c5294;
  }
  if (param_2 <= param_3) {
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | param_6;
    *(undefined2 *)(param_1 + 0xa70 + param_5 * 2) = (undefined2)param_2;
  }
  if (param_1 == DAT_004c528c) {
    if (DAT_004c5290 < param_2) {
      piVar4 = &DAT_004c5290;
    }
    else {
      piVar4 = &param_2;
    }
    DAT_004c5290 = *piVar4;
  }
  else if ((param_2 < DAT_004c5290) && (param_2 < param_3)) {
    local_8 = 0;
    local_24 = (ushort *)(param_1 + 0x890);
    do {
      local_a = *local_24;
      for (local_10 = 0; (local_a != 0 && (local_10 < 0x10)); local_10 = local_10 + 1) {
        if ((local_a & 1) != 0) {
          iVar5 = (local_8 * 0x10 + local_10) * 0xadc;
          puVar6 = &DAT_005a43d0 + iVar5;
          local_14 = 0;
          if ((*(byte *)((int)&DAT_005a43ec + iVar5 + 1) & 1) == 0) {
            if (DAT_004d5aa0 == '\0') {
              if ((&DAT_005a43f1)[iVar5] == '\0') {
                if (((iVar1 == 2) || (iVar1 == 3)) || (iVar1 == 6)) {
                  local_14 = 1;
                }
                else if (((iVar1 == 5) && (*(char *)(param_1 + 0x21) != '\0')) &&
                        ((iVar2 == (char)(&DAT_005a43f0)[iVar5] &&
                         (iVar3 = FUN_00445b94(puVar6,0x17), iVar3 != 0)))) {
                  local_14 = 1;
                }
              }
              else if (*(char *)(param_1 + 0x21) == '\0') {
                if (((((iVar1 == 3) || (iVar1 == 6)) ||
                     ((iVar1 == 1 && ((&DAT_005a43f1)[iVar5] != '\0')))) ||
                    (((iVar1 == 4 && ((&DAT_005a43f1)[iVar5] != '\0')) ||
                     ((iVar1 == 5 && ((&DAT_005a43f1)[iVar5] != '\0')))))) ||
                   ((iVar1 == 2 && ((&DAT_005a43f1)[iVar5] == '\0')))) {
                  local_14 = 1;
                }
              }
              else if (iVar1 != 2) {
                local_14 = 1;
              }
            }
            else {
              local_14 = 1;
            }
            if ((iVar2 != (char)(&DAT_005a43f0)[iVar5]) &&
               (iVar3 = FUN_004412d4(iVar2,(int)(char)(&DAT_005a43f0)[iVar5],1), iVar3 != 0)) {
              local_14 = 0;
            }
            if ((((iVar2 != (char)(&DAT_005a43f0)[iVar5]) &&
                 (iVar3 = FUN_004412d4(iVar2,(int)(char)(&DAT_005a43f0)[iVar5],2), iVar3 != 0)) &&
                (iVar3 = FUN_004412d4(iVar2,(int)(char)(&DAT_005a43f0)[iVar5],0x10), iVar3 == 0)) &&
               (iVar3 = FUN_0044d1e4(puVar6,9,0), iVar3 != -1)) {
              local_14 = 0;
            }
            if (local_14 != 0) {
              if (DAT_004d5aa0 == '\0') {
                if ((iVar1 == 3) ||
                   ((((iVar2 == (char)(&DAT_005a43f0)[iVar5] ||
                      ((iVar2 != (char)(&DAT_005a43f0)[iVar5] &&
                       (iVar3 = FUN_004412d4(iVar2,(int)(char)(&DAT_005a43f0)[iVar5],2), iVar3 != 0)
                       ))) && ((iVar2 == *(char *)(param_1 + 0x20) ||
                               ((iVar2 != *(char *)(param_1 + 0x20) &&
                                (iVar3 = FUN_004412d4(iVar2,(int)*(char *)(param_1 + 0x20),2),
                                iVar3 != 0)))))) &&
                    (((iVar1 == 2 || (iVar1 == 6)) ||
                     (((&DAT_005a43f1)[iVar5] != '\0' && (*(char *)(param_1 + 0x21) != '\0'))))))))
                {
                  local_18 = param_2 + 1;
                }
                else if (((iVar2 == *(char *)(param_1 + 0x20)) || (param_1 == DAT_00564214)) ||
                        ((iVar2 != *(char *)(param_1 + 0x20) &&
                         (iVar3 = FUN_004412d4(iVar2,(int)*(char *)(param_1 + 0x20),2), iVar3 != 0))
                        )) {
                  local_18 = param_2 + 2;
                }
                else if (*(char *)(param_1 + 0x20) == -1) {
                  local_18 = param_2 + 5;
                }
                else {
                  local_18 = param_2 + 100;
                }
              }
              else {
                local_18 = param_2;
              }
              if ((iVar2 == (char)(&DAT_005a43f0)[iVar5]) &&
                 (((iVar1 == 6 || (iVar1 == 1)) && (iVar3 = FUN_0044d1e4(puVar6,0xc,0), iVar3 != -1)
                  ))) {
                local_1c = local_18 + -1;
                local_20 = 0;
                if (local_18 + -1 < 0) {
                  piVar4 = &local_20;
                }
                else {
                  piVar4 = &local_1c;
                }
                local_18 = *piVar4;
              }
              if (((local_18 <= param_3) && (local_18 < DAT_004c5290)) &&
                 (local_18 < *(short *)(&DAT_005a4e40 + iVar2 * 2 + iVar5))) {
                FUN_00446440(puVar6,local_18,param_3,iVar1,iVar2,param_6);
              }
            }
          }
        }
        local_a = (short)local_a >> 1;
      }
      local_8 = local_8 + 1;
      local_24 = local_24 + 1;
    } while (local_8 < 7);
  }
  DAT_004c5294 = DAT_004c5294 + -1;
  return;
}

