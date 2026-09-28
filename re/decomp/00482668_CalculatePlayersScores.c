// CalculatePlayersScores @ 00482668 size=726 sig=undefined CalculatePlayersScores() cc=unknown
// callers: WinMain
// callees: DebugMessage
// strings: \"Invalid numerator or denominator in CalculatePlayersScores()\"

/* auto-named from string evidence: CalculatePlayersScores */

undefined4 CalculatePlayersScores(void)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  short *psVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  short *local_28;
  int *local_24;
  int *local_20;
  char *local_1c;
  char *local_18;
  int *local_14;
  
  local_14 = &DAT_0059f434;
  local_18 = &DAT_005a0548;
  local_1c = &DAT_00657df8;
  local_20 = &DAT_0065e3cc;
  local_24 = &DAT_0065e3e8;
  local_28 = &DAT_0065e43a;
  for (local_3c = 0; local_3c < DAT_004d5aec; local_3c = local_3c + 1) {
    local_38 = 0;
    if ((DAT_0065e428 != 0) && (*local_28 != 0)) {
      local_38 = (int)(500 / (longlong)DAT_0065e428);
    }
    puVar2 = &DAT_005a4eac;
    iVar3 = 0;
    local_34 = 0;
    iVar7 = 0;
    for (iVar6 = 1; iVar6 <= DAT_004d5b18; iVar6 = iVar6 + 1) {
      if (((*(char *)(puVar2 + 8) == local_3c) && (*(char *)((int)puVar2 + 0x7e) != '\0')) &&
         ((*(byte *)((int)puVar2 + 0x1d) & 1) == 0)) {
        if (0 < *(short *)(puVar2 + 0xc)) {
          iVar7 = iVar7 + 0x14;
          local_34 = local_34 + (int)*(short *)(puVar2 + 0xc) / 100;
        }
        iVar8 = 1;
        piVar1 = (int *)((int)puVar2 + 0x3e);
        do {
          iVar3 = iVar3 + *piVar1;
          iVar8 = iVar8 + 1;
          piVar1 = piVar1 + 1;
        } while (iVar8 < 0xb);
      }
      puVar2 = puVar2 + 0x2b7;
    }
    iVar6 = 1;
    iVar8 = 0;
    psVar4 = &DAT_004fbbde;
    do {
      if ((1 << ((byte)local_3c & 0x1f) & (int)*psVar4) != 0) {
        iVar8 = iVar8 + psVar4[0x10] * 10;
      }
      iVar6 = iVar6 + 1;
      psVar4 = psVar4 + 0x19;
    } while (iVar6 < 0x30);
    local_38 = local_38 + (*local_24 + *local_20) * 0x32 + iVar3 + iVar7 + local_34 + iVar8 +
               DAT_0059f154 * -3 + *local_1c * -100;
    local_30 = 0;
    if (local_38 < 0) {
      piVar1 = &local_30;
    }
    else {
      piVar1 = &local_38;
    }
    local_38 = *piVar1;
    local_2c = *(int *)(s_Mini_Ter_004dce30 + DAT_004d5aec * 8 + 4);
    iVar3 = *(int *)(s_Mini_Ter_004dce30 + DAT_004d5aec * 8 + 8);
    if (DAT_004d5b3c == 1) {
      iVar3 = iVar3 * 5;
      local_2c = local_2c << 2;
    }
    if (DAT_004d5b08 != 0) {
      iVar3 = iVar3 * 2;
    }
    iVar7 = 0;
    pcVar5 = &DAT_005a0548;
    for (iVar6 = 0; iVar6 < DAT_004d5aec; iVar6 = iVar6 + 1) {
      iVar7 = iVar7 + (*(int *)(&DAT_004dce74 + *pcVar5 * 8) * 1000) /
                      *(int *)(&DAT_004dce78 + *pcVar5 * 8);
      pcVar5 = pcVar5 + 1;
    }
    local_2c = (iVar7 / DAT_004d5aec) * local_2c;
    iVar3 = iVar3 * ((*(int *)(&DAT_004dce74 + *local_18 * 8) * 1000) /
                    *(int *)(&DAT_004dce78 + *local_18 * 8));
    if ((local_2c < 0) || (iVar3 < 1)) {
      DebugMessage(s_Invalid_numerator_or_denominator_004dce9c);
      local_1c[-0xffffffff00000004] = '\0';
      local_1c[-0xffffffff00000003] = '\0';
      local_1c[-0xffffffff00000002] = '\0';
      local_1c[-0xffffffff00000001] = '\0';
    }
    else {
      local_38 = (local_38 * local_2c) / iVar3;
      if (*local_14 != 0) {
        local_38 = 0;
      }
      *(int *)(local_1c + -4) = local_38;
    }
    local_14 = local_14 + 0xb6;
    local_18 = local_18 + 1;
    local_1c = local_1c + 6;
    local_20 = local_20 + 1;
    local_24 = local_24 + 1;
    local_28 = local_28 + 1;
  }
  return 1;
}

