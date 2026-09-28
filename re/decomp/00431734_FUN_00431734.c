// FUN_00431734 @ 00431734 size=1735 sig=undefined FUN_00431734() cc=unknown
// callers: FUN_0043242c,CheckSubUnit,FUN_00431dfc
// callees: memset,FUN_0049eb44,lstrcpyA,wsprintfA,FUN_00447b54,sprintf,lstrcatA,FUN_0044ddf4
// strings: \"%d Cr.\"|\"%d Labor\"|\"tons of food\"|\"KW of energy\"|\"%d %s\"|\"Ultra Slow\"|\" round/sec.\"|\" rounds/sec.\"|\"Does Not Move\"|\"point\"|\"points\"|\"credit\"|\"credits\"

void FUN_00431734(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  undefined *puVar7;
  int iVar8;
  undefined4 *puVar9;
  char *pcVar10;
  int iVar11;
  char *pcVar12;
  CHAR local_158 [20];
  char local_144 [20];
  CHAR local_130 [20];
  undefined1 local_11c [6];
  undefined1 local_116;
  undefined1 local_114;
  undefined4 local_c0 [2];
  int local_b8 [11];
  undefined1 local_8c [100];
  undefined **local_28;
  int *local_24;
  int local_20 [3];
  int local_14 [3];
  int local_8;
  
  if (param_1 < 0) {
    sprintf(local_8c,&DAT_004c45a6);
    FUN_0049eb44(DAT_004c42e0,0xf,1,0xf,0,local_8c);
    FUN_0049eb44(DAT_004c42e0,0x25,1,0xf,0,local_8c);
    FUN_0049eb44(DAT_004c42e0,0x23,1,0xf,0,local_8c);
    FUN_0049eb44(DAT_004c42e0,0x1f,1,0xf,0,local_8c);
    FUN_0049eb44(DAT_004c42e0,0x21,1,0xf,0,local_8c);
    FUN_0049eb44(DAT_004c42e0,0x23,1,0xf,0,local_8c);
    FUN_0049eb44(DAT_004c42e0,0x25,1,0xf,0,local_8c);
  }
  else {
    local_8 = *(int *)(&DAT_004c42f8 + (&DAT_00558cd4)[param_1 * 2] * 0xe);
    uVar2 = (&DAT_00558cd8)[param_1 * 2];
    memset(local_11c,0,0x5c);
    iVar8 = local_8;
    local_116 = (undefined1)local_8;
    local_114 = (undefined1)DAT_0058f1f4;
    sprintf(local_8c,&DAT_004c458a,(&PTR_s_No_Unit_004faf7c)[local_8 * 9]);
    FUN_0049eb44(DAT_004c42e0,0xf,1,0xf,0,local_8c);
    FUN_0049eb44(DAT_004c42e0,0x19,1,0xf,0,local_8c);
    sprintf(local_8c,s__d_Cr__004c4599,uVar2);
    FUN_0049eb44(DAT_004c42e0,0x11,1,0xf,0,local_8c);
    sprintf(local_8c,&DAT_004c458d,(int)(char)(&DAT_004faf8f)[iVar8 * 0x24]);
    FUN_0049eb44(DAT_004c42e0,0x1b,1,0xf,0,local_8c);
    sprintf(local_8c,&DAT_004c458d,(int)(char)(&DAT_004faf90)[iVar8 * 0x24]);
    FUN_0049eb44(DAT_004c42e0,0x1d,1,0xf,0,local_8c);
    sprintf(local_8c,&DAT_004c458d,
            (int)*(short *)(&DAT_004c42fc + (&DAT_00558cd4)[param_1 * 2] * 0xe));
    FUN_0049eb44(DAT_004c42e0,0x18,1,0xf,0,local_8c);
    sprintf(local_8c,&DAT_004c4589);
    FUN_0049eb44(DAT_004c42e0,0x13,1,0xf,0,local_8c);
    FUN_0049eb44(DAT_004c42e0,0x14,1,0xf,0,local_8c);
    FUN_0049eb44(DAT_004c42e0,0x15,1,0xf,0,local_8c);
    FUN_0049eb44(DAT_004c42e0,0x16,1,0xf,0,local_8c);
    FUN_0044ddf4(PTR_DAT_004d5988,local_8,local_c0);
    sprintf(local_8c,PTR_s__d_Labor_00509b54,local_c0[0]);
    FUN_0049eb44(DAT_004c42e0,0x13,1,0xf,0,local_8c);
    iVar8 = 0;
    puVar9 = &DAT_00558e68;
    do {
      iVar8 = iVar8 + 1;
      *puVar9 = 0;
      puVar9 = puVar9 + 1;
    } while (iVar8 < 5);
    iVar11 = 1;
    iVar8 = 1;
    local_28 = &PTR_s_tons_of_food_005090f4;
    local_24 = &DAT_00558e6c;
    piVar4 = local_b8;
    do {
      iVar3 = *piVar4;
      if (iVar3 != 0) {
        *local_24 = iVar8;
        sprintf(local_8c,s__d__s_004c45a0,iVar3,*local_28);
        if (iVar11 == 1) {
          iVar11 = 2;
          FUN_0049eb44(DAT_004c42e0,0x14,1,0xf,0,local_8c);
        }
        else if (iVar11 == 2) {
          iVar11 = 3;
          FUN_0049eb44(DAT_004c42e0,0x15,1,0xf,0,local_8c);
        }
        else if (iVar11 == 3) {
          iVar11 = 4;
          FUN_0049eb44(DAT_004c42e0,0x16,1,0xf,0,local_8c);
        }
      }
      local_28 = local_28 + 1;
      local_24 = local_24 + 1;
      iVar8 = iVar8 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar8 < 0xb);
    iVar8 = FUN_00447b54(local_11c);
    local_14[2] = iVar8 + 1;
    local_14[1] = 7;
    if (iVar8 + 1 < 8) {
      piVar4 = local_14 + 2;
    }
    else {
      piVar4 = local_14 + 1;
    }
    local_14[0] = 0;
    if (*piVar4 < 0) {
      piVar4 = local_14;
    }
    lstrcpyA(local_130,(&PTR_s_Does_Not_Move_00509a64)[*piVar4]);
    FUN_0049eb44(DAT_004c42e0,0x1f,1,0xf,0,local_130);
    local_20[2] = (char)(&DAT_004faf92)[local_8 * 0x24] + 1;
    local_20[1] = 9;
    if ((char)(&DAT_004faf92)[local_8 * 0x24] + 1 < 10) {
      piVar4 = local_20 + 2;
    }
    else {
      piVar4 = local_20 + 1;
    }
    local_20[0] = 0;
    if (*piVar4 < 0) {
      piVar4 = local_20;
    }
    iVar8 = *piVar4;
    uVar5 = 0xffffffff;
    pcVar10 = (&PTR_s_Does_Not_Shoot_00509a84)[iVar8];
    do {
      pcVar12 = pcVar10;
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      pcVar12 = pcVar10 + 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar12;
    } while (cVar1 != '\0');
    uVar5 = ~uVar5;
    pcVar10 = pcVar12 + -uVar5;
    pcVar12 = local_144;
    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pcVar12 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar12 = pcVar12 + 4;
    }
    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
      *pcVar12 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar12 = pcVar12 + 1;
    }
    if (iVar8 == 1) {
      lstrcatA(local_144,PTR_s_round_sec__00509aac);
    }
    if (1 < iVar8) {
      lstrcatA(local_144,PTR_s_rounds_sec__00509ab0);
    }
    FUN_0049eb44(DAT_004c42e0,0x21,1,0xf,0,local_144);
    iVar8 = (int)(char)(&DAT_004faf8c)[local_8 * 0x24];
    if (iVar8 == 0) {
      wsprintfA(local_158,PTR_s_Does_Not_Move_00509ac8);
    }
    else {
      if ((1 << ((byte)DAT_0058f1f4 & 0x1f) & (int)DAT_004fc4a8) != 0) {
        iVar8 = iVar8 + 1;
      }
      puVar7 = PTR_s_points_00509ad0;
      if (iVar8 == 1) {
        puVar7 = PTR_s_point_00509acc;
      }
      wsprintfA(local_158,s__d__s_004c45a0,iVar8,puVar7);
    }
    FUN_0049eb44(DAT_004c42e0,0x23,1,0xf,0,local_158);
    iVar8 = (int)(char)(&DAT_004faf8a)[local_8 * 0x24];
    if (iVar8 == 0) {
      sprintf(local_8c,PTR_DAT_00509ad4);
    }
    else {
      puVar7 = PTR_s_credits_00509adc;
      if (iVar8 == 1) {
        puVar7 = PTR_s_credit_00509ad8;
      }
      sprintf(local_8c,s__d__s_004c45a0,iVar8,puVar7);
    }
    FUN_0049eb44(DAT_004c42e0,0x25,1,0xf,0,local_8c);
    sprintf(local_8c,s__d_Cr__004c4599,(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6]);
    FUN_0049eb44(DAT_004c42e0,3,1,0xf,0,local_8c);
  }
  sprintf(local_8c,s__d_Cr__004c4599,(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6]);
  FUN_0049eb44(DAT_004c42e0,3,1,0xf,0,local_8c);
  return;
}

