// FUN_004474b0 @ 004474b0 size=1422 sig=undefined FUN_004474b0() cc=unknown
// callers: FUN_0046e730
// callees: ReLinkArmy,FUN_004412d4,DeleteUnit,FUN_00447a40,FUN_0045951c,FUN_004594b8,FUN_00423690,FUN_00446bf0,FUN_0046f89c

void FUN_004474b0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined2 *puVar4;
  int *piVar5;
  int *piVar6;
  int local_9c [4];
  int local_8c [4];
  int local_7c [4];
  int *local_6c;
  int *local_68;
  int *local_64;
  int *local_60;
  int *local_5c;
  int *local_58;
  int *local_54;
  int *local_50;
  int *local_4c;
  int *local_48;
  int *local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  int local_8;
  
  iVar2 = *(int *)(param_1 + 0x7a);
  while (iVar3 = iVar2, iVar3 != 0) {
    local_8 = *(int *)(iVar3 + 0x54);
    iVar2 = local_8;
    if (((((*(char *)(iVar3 + 7) != '\x03') &&
          (iVar1 = FUN_00446bf0(iVar3), iVar2 = local_8, iVar1 == 0)) &&
         (*(char *)(iVar3 + 7) != '\r')) &&
        ((*(char *)(param_1 + 0x20) != -1 && (*(char *)(iVar3 + 8) != *(char *)(param_1 + 0x20)))))
       && ((iVar1 = FUN_004412d4((int)*(char *)(iVar3 + 8),(int)*(char *)(param_1 + 0x20),2),
           iVar2 = local_8, iVar1 == 0 && (iVar3 != 0)))) {
      DeleteUnit(iVar3);
      iVar2 = local_8;
    }
  }
  iVar2 = *(int *)(param_1 + 0x76);
  while (iVar3 = iVar2, iVar3 != 0) {
    local_8 = *(int *)(iVar3 + 0x54);
    iVar2 = local_8;
    if (*(char *)(iVar3 + 8) != *(char *)(param_1 + 0x20)) {
      iVar2 = FUN_00446bf0(iVar3);
      if ((iVar2 == 0) &&
         (iVar2 = FUN_004412d4((int)*(char *)(iVar3 + 8),(int)*(char *)(param_1 + 0x20),2),
         iVar2 == 0)) {
        iVar2 = local_8;
        if (iVar3 != 0) {
          DeleteUnit(iVar3);
          iVar2 = local_8;
        }
      }
      else {
        ReLinkArmy(iVar3,param_1,param_1 + 0x76,param_1 + 0x7a);
        iVar2 = local_8;
      }
    }
  }
  if (*(char *)(param_1 + 0x21) == '\0') {
    piVar6 = &DAT_004c5298;
    piVar5 = local_7c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar5 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar5 = piVar5 + 1;
    }
    for (iVar2 = *(int *)(param_1 + 0x76); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
      iVar3 = FUN_004594b8(iVar2);
      local_7c[iVar3] = local_7c[iVar3] + 1;
    }
    local_50 = local_7c;
    local_10 = 0;
    local_4c = &DAT_004faf6c;
    do {
      local_48 = local_4c;
      local_44 = local_50;
      while (*local_48 < *local_44) {
        puVar4 = (undefined2 *)0x0;
        local_14 = 0;
        FUN_0046f89c();
        piVar6 = &DAT_005904dc;
        local_18 = 0;
        do {
          iVar2 = *piVar6;
          iVar3 = iVar2 * 0x5c;
          if (((((&DAT_00645376)[iVar3] != '\0') &&
               (iVar1 = FUN_004594b8(&DAT_00645370 + iVar2 * 0x2e), iVar1 == local_10)) &&
              ((&DAT_006453ac)[iVar2 * 0x17] == param_1)) &&
             (((&DAT_00645378)[iVar3] == *(char *)(param_1 + 0x20) &&
              ((((iVar1 = FUN_00447a40((int)*(short *)(&DAT_00645398 + iVar3)),
                 puVar4 == (undefined2 *)0x0 || (iVar1 < local_14)) ||
                ((iVar1 == local_14 && ((char)(&DAT_00645376)[iVar3] < *(char *)(puVar4 + 3))))) ||
               (((iVar1 == local_14 && ((&DAT_00645376)[iVar3] == *(char *)(puVar4 + 3))) &&
                (*(short *)(&DAT_00645398 + iVar3) < (short)puVar4[0x14])))))))) {
            puVar4 = &DAT_00645370 + iVar2 * 0x2e;
            local_14 = iVar1;
          }
          local_18 = local_18 + 1;
          piVar6 = piVar6 + 1;
        } while (local_18 < 0x230);
        if (puVar4 != (undefined2 *)0x0) {
          *local_44 = *local_44 + -1;
          FUN_00423690((int)*(char *)(puVar4 + 4),0x21,(int)puVar4 + 0xb,param_1,0,0);
          DeleteUnit(puVar4);
        }
      }
      local_10 = local_10 + 1;
      local_50 = local_50 + 1;
      local_4c = local_4c + 1;
    } while (local_10 < 4);
    iVar2 = *(int *)(param_1 + 0x76);
    if (*(int *)(param_1 + 0x76) != 0) {
      do {
        piVar6 = (int *)(iVar2 + 0x54);
        if (((&DAT_004faf8d)[*(char *)(iVar2 + 6) * 0x24] == '\x01') &&
           (local_1c = *(int *)(iVar2 + 0x48), local_1c != 0)) {
          local_20 = 0;
          local_24 = 0;
          local_54 = (int *)(local_1c + 0x48);
          do {
            if (iVar2 == *local_54) {
              local_20 = 1;
              break;
            }
            local_24 = local_24 + 1;
            local_54 = local_54 + 1;
          } while (local_24 < 3);
        }
        iVar2 = *piVar6;
      } while (*piVar6 != 0);
      local_c = 0;
    }
  }
  else {
    piVar6 = &DAT_004c52a8;
    piVar5 = local_8c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar5 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar5 = piVar5 + 1;
    }
    for (iVar2 = *(int *)(param_1 + 0x76); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
      iVar3 = FUN_0045951c(iVar2);
      local_8c[iVar3] = local_8c[iVar3] + 1;
    }
    local_4c = local_8c;
    local_28 = 0;
    local_50 = &DAT_004faf5c;
    do {
      local_5c = local_50;
      local_58 = local_4c;
      while (*local_5c < *local_58) {
        puVar4 = (undefined2 *)0x0;
        local_2c = 0;
        FUN_0046f89c();
        piVar6 = &DAT_005904dc;
        local_30 = 0;
        do {
          iVar2 = *piVar6;
          iVar3 = iVar2 * 0x5c;
          if ((((((&DAT_00645376)[iVar3] != '\0') &&
                (iVar1 = FUN_0045951c(&DAT_00645370 + iVar2 * 0x2e), iVar1 == local_28)) &&
               ((&DAT_006453ac)[iVar2 * 0x17] == param_1)) &&
              ((&DAT_00645378)[iVar3] == *(char *)(param_1 + 0x20))) &&
             ((((iVar1 = FUN_00447a40((int)*(short *)(&DAT_00645398 + iVar3)),
                puVar4 == (undefined2 *)0x0 || (iVar1 < local_2c)) ||
               ((iVar1 == local_2c && ((char)(&DAT_00645376)[iVar3] < *(char *)(puVar4 + 3))))) ||
              (((iVar1 == local_2c && ((&DAT_00645376)[iVar3] == *(char *)(puVar4 + 3))) &&
               (*(short *)(&DAT_00645398 + iVar3) < (short)puVar4[0x14])))))) {
            puVar4 = &DAT_00645370 + iVar2 * 0x2e;
            local_2c = iVar1;
          }
          local_30 = local_30 + 1;
          piVar6 = piVar6 + 1;
        } while (local_30 < 0x230);
        if (puVar4 != (undefined2 *)0x0) {
          *local_58 = *local_58 + -1;
          FUN_00423690((int)*(char *)(puVar4 + 4),0x21,(int)puVar4 + 0xb,param_1,0,0);
          DeleteUnit(puVar4);
        }
      }
      local_28 = local_28 + 1;
      local_4c = local_4c + 1;
      local_50 = local_50 + 1;
    } while (local_28 < 4);
  }
  local_34 = 0;
  do {
    piVar6 = &DAT_004c52b8;
    piVar5 = local_9c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar5 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar5 = piVar5 + 1;
    }
    for (iVar2 = *(int *)(param_1 + 0x7a); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
      if (*(char *)(iVar2 + 8) == local_34) {
        iVar3 = FUN_0045951c(iVar2);
        local_9c[iVar3] = local_9c[iVar3] + 1;
      }
    }
    local_6c = local_9c;
    local_38 = 0;
    local_68 = &DAT_004faf5c;
    do {
      local_64 = local_68;
      local_60 = local_6c;
      while (*local_64 < *local_60) {
        puVar4 = (undefined2 *)0x0;
        local_3c = 0;
        FUN_0046f89c();
        piVar6 = &DAT_005904dc;
        local_40 = 0;
        do {
          iVar2 = *piVar6;
          iVar3 = iVar2 * 0x5c;
          if ((((((&DAT_00645376)[iVar3] != '\0') && ((char)(&DAT_00645378)[iVar3] == local_34)) &&
               (iVar1 = FUN_0045951c(&DAT_00645370 + iVar2 * 0x2e), iVar1 == local_38)) &&
              ((&DAT_006453ac)[iVar2 * 0x17] == param_1)) &&
             ((((iVar1 = FUN_00447a40((int)*(short *)(&DAT_00645398 + iVar3)),
                puVar4 == (undefined2 *)0x0 || (iVar1 < local_3c)) ||
               ((iVar1 == local_3c && ((char)(&DAT_00645376)[iVar3] < *(char *)(puVar4 + 3))))) ||
              (((iVar1 == local_3c && ((&DAT_00645376)[iVar3] == *(char *)(puVar4 + 3))) &&
               (*(short *)(&DAT_00645398 + iVar3) < (short)puVar4[0x14])))))) {
            puVar4 = &DAT_00645370 + iVar2 * 0x2e;
            local_3c = iVar1;
          }
          local_40 = local_40 + 1;
          piVar6 = piVar6 + 1;
        } while (local_40 < 0x230);
        if (puVar4 != (undefined2 *)0x0) {
          *local_60 = *local_60 + -1;
          FUN_00423690((int)*(char *)(puVar4 + 4),0x21,(int)puVar4 + 0xb,param_1,0,0);
          DeleteUnit(puVar4);
        }
      }
      local_38 = local_38 + 1;
      local_6c = local_6c + 1;
      local_68 = local_68 + 1;
    } while (local_38 < 4);
    local_34 = local_34 + 1;
  } while (local_34 < 7);
  return;
}

