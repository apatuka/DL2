// FUN_0047ded8 @ 0047ded8 size=257 sig=undefined FUN_0047ded8() cc=unknown
// callers: FUN_0047dfdc
// callees: 

void FUN_0047ded8(int param_1,int param_2)

{
  short sVar1;
  short sVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short *local_18;
  short *local_14;
  int local_10;
  char *local_8;
  
  iVar4 = param_2 * 0x34 + param_1;
  sVar1 = *(short *)(iVar4 + 0x152);
  pcVar3 = (char *)(iVar4 + 0x140);
  while( true ) {
    if (sVar1 == 0) {
      return;
    }
    local_10 = -1;
    local_18 = &DAT_004dcbe0;
    local_14 = &DAT_004dcbd8;
    iVar4 = 0;
    local_8 = pcVar3;
    do {
      iVar5 = (int)*pcVar3 + (int)*local_14;
      iVar6 = (int)pcVar3[1] + (int)*local_18;
      if ((((-1 < iVar5) && (-1 < iVar6)) && (iVar5 < 6)) && (iVar6 < 6)) {
        iVar5 = (iVar5 + iVar6 * 6) * 0x34 + param_1;
        sVar2 = *(short *)(iVar5 + 0x152);
        if (sVar2 < sVar1) {
          local_10 = iVar4;
          local_8 = (char *)(iVar5 + 0x140);
          sVar1 = sVar2;
        }
      }
      iVar4 = iVar4 + 1;
      local_18 = local_18 + 1;
      local_14 = local_14 + 1;
    } while (iVar4 < 4);
    if (local_10 == -1) break;
    if (local_8[0x10] != '\0') {
      sVar1 = 0;
    }
    pcVar3[0x10] = pcVar3[0x10] | (&DAT_004dcbc8)[local_10 * 2];
    local_8[0x10] = local_8[0x10] | (&DAT_004dcbd0)[local_10 * 2];
    pcVar3 = local_8;
  }
  return;
}

