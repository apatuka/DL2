// FUN_00471170 @ 00471170 size=1220 sig=undefined FUN_00471170() cc=unknown
// callers: FUN_00468394,GetNetGameOptions
// callees: FUN_00471028,FUN_00470fc0
// strings: \"Players\"|\"Scenario Options\"|\"Victory Condition\"|\"manifest_destiny\"|\"conquest\"|\"Win Cities\"|\"Win Shrines\"|\"Win Turns\"|\"AI Skill Level\"|\"Random Events\"|\"Allow Alliances\"|\"Fast Production\"|\"World Resources\"|\"Last Player Timer\"|\"Last Player Clock\"|\"Auto Timer\"|\"Auto Timer Clock\"|\"Racial Abilities\"|\"standard_ability\"|\"best_ability\"

int FUN_00471170(undefined4 param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  char *pcVar6;
  undefined **ppuVar7;
  bool bVar8;
  bool bVar9;
  char local_20 [20];
  int local_c;
  int local_8;
  
  iVar2 = FUN_00471028(PTR_s_Scenario_Options_004d5f60,PTR_s_Players_004d5f7c,param_2 + 0xc,param_1)
  ;
  bVar9 = false;
  if (iVar2 != 0) {
    if ((*(int *)(param_2 + 0xc) < 2) || (7 < *(int *)(param_2 + 0xc))) {
      bVar9 = false;
    }
    else {
      bVar9 = true;
    }
  }
  iVar2 = 0;
  if (bVar9) {
    iVar2 = FUN_00470fc0(PTR_s_Scenario_Options_004d5f60,PTR_s_Victory_Condition_004d5f80,local_20,
                         0x14,param_1);
  }
  bVar9 = false;
  if (iVar2 != 0) {
    bVar9 = false;
    local_8 = 0;
    ppuVar7 = &PTR_s_manifest_destiny_004d6010;
    do {
      pcVar3 = local_20;
      pcVar6 = *ppuVar7;
      do {
        if (*pcVar3 != *pcVar6) goto LAB_0047120e;
        bVar8 = true;
        if (*pcVar3 == '\0') break;
        pcVar1 = pcVar3 + 1;
        if (*pcVar1 != pcVar6[1]) goto LAB_0047120e;
        pcVar3 = pcVar3 + 2;
        pcVar6 = pcVar6 + 2;
        bVar8 = *pcVar1 == '\0';
      } while (!bVar8);
      if (bVar8) {
        bVar9 = true;
        break;
      }
LAB_0047120e:
      local_8 = local_8 + 1;
      ppuVar7 = ppuVar7 + 1;
    } while (local_8 < 3);
    if (bVar9) {
      *(undefined1 *)(param_2 + 0x1c) = (undefined1)local_8;
    }
  }
  iVar2 = 0;
  if (bVar9) {
    iVar2 = FUN_00471028(PTR_s_Scenario_Options_004d5f60,PTR_s_Win_Cities_004d5f84,param_2 + 0x10,
                         param_1);
  }
  bVar9 = false;
  if (iVar2 != 0) {
    bVar9 = false;
    iVar2 = 0;
    piVar4 = &DAT_004c425c;
    do {
      if (*piVar4 == *(int *)(param_2 + 0x10)) {
        bVar9 = true;
        break;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar2 < 5);
  }
  iVar2 = 0;
  if (bVar9) {
    iVar2 = FUN_00471028(PTR_s_Scenario_Options_004d5f60,PTR_s_Win_Shrines_004d5f88,param_2 + 0x14,
                         param_1);
  }
  bVar9 = false;
  if (iVar2 != 0) {
    bVar9 = false;
    iVar2 = 0;
    piVar4 = &DAT_004c4274;
    do {
      if (*piVar4 == *(int *)(param_2 + 0x14)) {
        bVar9 = true;
        break;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar2 < 3);
  }
  iVar2 = 0;
  if (bVar9) {
    iVar2 = FUN_00471028(PTR_s_Scenario_Options_004d5f60,PTR_s_Win_Turns_004d5f8c,param_2 + 0x18,
                         param_1);
  }
  bVar9 = false;
  if (iVar2 != 0) {
    bVar9 = false;
    iVar2 = 0;
    piVar4 = &DAT_004c4280;
    do {
      if (*piVar4 == *(int *)(param_2 + 0x18)) {
        bVar9 = true;
        break;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar2 < 3);
  }
  iVar2 = 0;
  if (bVar9) {
    iVar2 = FUN_00471028(PTR_s_Scenario_Options_004d5f60,PTR_s_AI_Skill_Level_004d5f90,
                         param_2 + 0x26,param_1);
  }
  *(int *)(param_2 + 0x26) = *(int *)(param_2 + 0x26) + 2;
  bVar9 = false;
  if (iVar2 != 0) {
    if ((*(int *)(param_2 + 0x26) < 0) || (5 < *(int *)(param_2 + 0x26))) {
      bVar9 = false;
    }
    else {
      bVar9 = true;
    }
  }
  iVar2 = 0;
  if (bVar9) {
    iVar2 = FUN_00470fc0(PTR_s_Scenario_Options_004d5f60,PTR_s_Random_Events_004d5f94,local_20,0x14,
                         param_1);
  }
  if (iVar2 != 0) {
    pcVar3 = local_20;
    pcVar6 = PTR_DAT_004d6020;
    do {
      bVar9 = *pcVar3 == *pcVar6;
      if ((!bVar9) || (bVar9 = true, *pcVar3 == '\0')) break;
      pcVar1 = pcVar3 + 1;
      bVar9 = *pcVar1 == pcVar6[1];
      if (!bVar9) break;
      pcVar3 = pcVar3 + 2;
      pcVar6 = pcVar6 + 2;
      bVar9 = *pcVar1 == '\0';
    } while (!bVar9);
    *(uint *)(param_2 + 0x22) = (uint)bVar9;
  }
  iVar5 = 0;
  if (iVar2 != 0) {
    iVar5 = FUN_00470fc0(PTR_s_Scenario_Options_004d5f60,PTR_s_Allow_Alliances_004d5f98,local_20,
                         0x14,param_1);
  }
  if (iVar5 != 0) {
    pcVar3 = local_20;
    pcVar6 = PTR_DAT_004d6020;
    do {
      bVar9 = *pcVar3 == *pcVar6;
      if ((!bVar9) || (bVar9 = true, *pcVar3 == '\0')) break;
      pcVar1 = pcVar3 + 1;
      bVar9 = *pcVar1 == pcVar6[1];
      if (!bVar9) break;
      pcVar3 = pcVar3 + 2;
      pcVar6 = pcVar6 + 2;
      bVar9 = *pcVar1 == '\0';
    } while (!bVar9);
    *(uint *)(param_2 + 0xa8) = (uint)bVar9;
  }
  iVar2 = 0;
  if (iVar5 != 0) {
    iVar2 = FUN_00470fc0(PTR_s_Scenario_Options_004d5f60,PTR_s_Fast_Production_004d5f9c,local_20,
                         0x14,param_1);
  }
  if (iVar2 != 0) {
    pcVar3 = local_20;
    pcVar6 = PTR_DAT_004d6020;
    do {
      bVar9 = *pcVar3 == *pcVar6;
      if ((!bVar9) || (bVar9 = true, *pcVar3 == '\0')) break;
      pcVar1 = pcVar3 + 1;
      bVar9 = *pcVar1 == pcVar6[1];
      if (!bVar9) break;
      pcVar3 = pcVar3 + 2;
      pcVar6 = pcVar6 + 2;
      bVar9 = *pcVar1 == '\0';
    } while (!bVar9);
    *(uint *)(param_2 + 0x1e) = (uint)bVar9;
  }
  iVar5 = 0;
  if (iVar2 != 0) {
    iVar5 = FUN_00470fc0(PTR_s_Scenario_Options_004d5f60,PTR_s_World_Resources_004d5fa0,local_20,
                         0x14,param_1);
  }
  if (iVar5 != 0) {
    pcVar3 = local_20;
    pcVar6 = PTR_DAT_004d6020;
    do {
      bVar9 = *pcVar3 == *pcVar6;
      if ((!bVar9) || (bVar9 = true, *pcVar3 == '\0')) break;
      pcVar1 = pcVar3 + 1;
      bVar9 = *pcVar1 == pcVar6[1];
      if (!bVar9) break;
      pcVar3 = pcVar3 + 2;
      pcVar6 = pcVar6 + 2;
      bVar9 = *pcVar1 == '\0';
    } while (!bVar9);
    *(uint *)(param_2 + 0x74) = (uint)bVar9;
  }
  iVar2 = 0;
  if (iVar5 != 0) {
    iVar2 = FUN_00470fc0(PTR_s_Scenario_Options_004d5f60,PTR_s_Last_Player_Timer_004d5fa4,local_20,
                         0x14,param_1);
  }
  if (iVar2 != 0) {
    pcVar3 = local_20;
    pcVar6 = PTR_DAT_004d6020;
    do {
      bVar9 = *pcVar3 == *pcVar6;
      if ((!bVar9) || (bVar9 = true, *pcVar3 == '\0')) break;
      pcVar1 = pcVar3 + 1;
      bVar9 = *pcVar1 == pcVar6[1];
      if (!bVar9) break;
      pcVar3 = pcVar3 + 2;
      pcVar6 = pcVar6 + 2;
      bVar9 = *pcVar1 == '\0';
    } while (!bVar9);
    *(uint *)(param_2 + 0x56) = (uint)bVar9;
  }
  iVar5 = 0;
  if (iVar2 != 0) {
    iVar5 = FUN_00471028(PTR_s_Scenario_Options_004d5f60,PTR_s_Last_Player_Clock_004d5fa8,
                         param_2 + 0x5a,param_1);
  }
  bVar9 = false;
  if (iVar5 != 0) {
    if ((*(int *)(param_2 + 0x5a) < 3) || (0x3c0 < *(int *)(param_2 + 0x5a))) {
      bVar9 = false;
    }
    else {
      bVar9 = true;
    }
  }
  iVar2 = 0;
  if (bVar9) {
    iVar2 = FUN_00470fc0(PTR_s_Scenario_Options_004d5f60,PTR_s_Auto_Timer_004d5fac,local_20,0x14,
                         param_1);
  }
  if (iVar2 != 0) {
    pcVar3 = local_20;
    pcVar6 = PTR_DAT_004d6020;
    do {
      bVar9 = *pcVar3 == *pcVar6;
      if ((!bVar9) || (bVar9 = true, *pcVar3 == '\0')) break;
      pcVar1 = pcVar3 + 1;
      bVar9 = *pcVar1 == pcVar6[1];
      if (!bVar9) break;
      pcVar3 = pcVar3 + 2;
      pcVar6 = pcVar6 + 2;
      bVar9 = *pcVar1 == '\0';
    } while (!bVar9);
    *(uint *)(param_2 + 0x4a) = (uint)bVar9;
  }
  if (*(int *)(param_2 + 0x56) != 0) {
    *(undefined4 *)(param_2 + 0x4a) = 0;
  }
  iVar5 = 0;
  if (iVar2 != 0) {
    iVar5 = FUN_00471028(PTR_s_Scenario_Options_004d5f60,PTR_s_Auto_Timer_Clock_004d5fb0,
                         param_2 + 0x52,param_1);
  }
  bVar9 = false;
  if (iVar5 != 0) {
    if ((*(int *)(param_2 + 0x52) < 3) || (0x3c0 < *(int *)(param_2 + 0x52))) {
      bVar9 = false;
    }
    else {
      bVar9 = true;
    }
  }
  iVar2 = 0;
  if (bVar9) {
    iVar2 = FUN_00470fc0(PTR_s_Scenario_Options_004d5f60,PTR_s_Racial_Abilities_004d5fb4,local_20,
                         0x14,param_1);
  }
  iVar5 = 0;
  if (iVar2 != 0) {
    iVar5 = 0;
    local_c = 0;
    ppuVar7 = &PTR_s_standard_ability_004d6024;
    do {
      pcVar3 = local_20;
      pcVar6 = *ppuVar7;
      do {
        if (*pcVar3 != *pcVar6) goto LAB_00471611;
        bVar9 = true;
        if (*pcVar3 == '\0') break;
        pcVar1 = pcVar3 + 1;
        if (*pcVar1 != pcVar6[1]) goto LAB_00471611;
        pcVar3 = pcVar3 + 2;
        pcVar6 = pcVar6 + 2;
        bVar9 = *pcVar1 == '\0';
      } while (!bVar9);
      if (bVar9) {
        iVar5 = 1;
        break;
      }
LAB_00471611:
      local_c = local_c + 1;
      ppuVar7 = ppuVar7 + 1;
    } while (local_c < 3);
    if (iVar5 != 0) {
      *(int *)(param_2 + 0x5e) = local_c;
    }
  }
  return iVar5;
}

