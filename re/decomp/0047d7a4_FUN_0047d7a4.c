// FUN_0047d7a4 @ 0047d7a4 size=330 sig=undefined FUN_0047d7a4() cc=unknown
// callers: FUN_0047db84
// callees: 

void FUN_0047d7a4(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  short sVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short *local_20;
  short *local_1c;
  int local_18;
  char *local_c;
  
  sVar1 = (&DAT_005a0558)[param_3 * 5 + param_4 * 200];
  local_18 = 0;
  pcVar2 = &DAT_005a0550 + param_4 * 400 + param_3 * 10;
  while (sVar1 != 0) {
    iVar5 = 0;
    local_20 = &DAT_004dcbe0;
    local_1c = &DAT_004dcbd8;
    local_c = pcVar2;
    do {
      iVar4 = (int)*pcVar2 + (int)*local_1c;
      iVar3 = (int)pcVar2[1] + (int)*local_20;
      if ((((-1 < iVar4) && (-1 < iVar3)) && (iVar4 < DAT_004d5b1a)) &&
         (((iVar3 < DAT_004d5b1b &&
           ((char)(&DAT_005a43f0)[(short)(&DAT_005a0552)[iVar4 * 5 + iVar3 * 200] * 0xadc] ==
            DAT_0058f1f4)) && ((short)(&DAT_005a0558)[iVar4 * 5 + iVar3 * 200] < sVar1)))) {
        sVar1 = (&DAT_005a0558)[iVar4 * 5 + iVar3 * 200];
        local_18 = iVar5;
        local_c = &DAT_005a0550 + iVar3 * 400 + iVar4 * 10;
      }
      iVar5 = iVar5 + 1;
      local_20 = local_20 + 1;
      local_1c = local_1c + 1;
    } while (iVar5 < 4);
    if (local_c[6] != '\0') {
      sVar1 = 0;
    }
    pcVar2[6] = pcVar2[6] | (&DAT_004dcbc8)[local_18 * 2];
    local_c[6] = local_c[6] | (&DAT_004dcbd0)[local_18 * 2];
    pcVar2 = local_c;
  }
  return;
}

