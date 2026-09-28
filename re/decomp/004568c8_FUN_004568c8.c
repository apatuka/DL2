// FUN_004568c8 @ 004568c8 size=838 sig=undefined FUN_004568c8() cc=unknown
// callers: FUN_00456c10
// callees: FUN_00456214,FUN_00450fa8,FUN_004526b0,FUN_00456150,FUN_00446bf0,FUN_00456618,FUN_00452250,FUN_004412d4,FUN_004522c0,FUN_00451b68,FUN_00451410,memset,FUN_00451de4,FUN_0044d230

void FUN_004568c8(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  int *piVar6;
  bool bVar7;
  int local_48 [7];
  int *local_2c;
  int *local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  memset(local_48,0,0x1c);
  local_8 = 1;
  local_c = -1;
  local_10 = -1;
  local_14 = -1;
  for (iVar3 = *(int *)(param_1 + 0x7a); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x54)) {
    if ((*(char *)(param_1 + 0x20) != *(char *)(iVar3 + 8)) &&
       (iVar2 = FUN_00446bf0(iVar3), iVar2 == 0)) {
      cVar1 = *(char *)(iVar3 + 8);
      local_48[cVar1] = local_48[cVar1] + 1;
      iVar2 = FUN_004412d4((int)cVar1,(int)*(char *)(param_1 + 0x20),2);
      if (iVar2 == 0) {
        iVar2 = FUN_00450fa8(iVar3);
        if ((iVar2 == 0) || (*(int *)(iVar3 + 0x48) != 0)) {
          if ((&DAT_004faf8d)[*(char *)(iVar3 + 6) * 0x24] != '\x03') {
            local_8 = 0;
          }
          local_10 = (int)*(char *)(iVar3 + 8);
        }
        else {
          local_c = (int)*(char *)(iVar3 + 8);
        }
      }
    }
  }
  if ((local_10 != -1) || (local_10 = local_c, local_c != -1)) {
    if ((*(int *)(param_1 + 0x76) == 0) ||
       (iVar3 = FUN_004412d4(local_10,(int)*(char *)(*(int *)(param_1 + 0x76) + 8),2), iVar3 != 0))
    {
      if ((*(short *)(param_1 + 0x30) == 0) ||
         (iVar3 = FUN_004412d4(local_10,(int)*(char *)(param_1 + 0x20),2), iVar3 != 0)) {
        iVar3 = 0;
        local_28 = local_48;
        do {
          if (*local_28 != 0) {
            iVar2 = 0;
            local_2c = local_48;
            do {
              if (((iVar2 != iVar3) && (*local_2c != 0)) &&
                 (iVar4 = FUN_004412d4(iVar3,iVar2,2), iVar4 == 0)) {
                local_14 = iVar2;
                local_10 = iVar3;
              }
              iVar2 = iVar2 + 1;
              local_2c = local_2c + 1;
            } while (iVar2 < 7);
          }
          iVar3 = iVar3 + 1;
          local_28 = local_28 + 1;
        } while (iVar3 < 7);
      }
      else {
        local_14 = (int)*(char *)(param_1 + 0x20);
      }
    }
    else {
      local_14 = (int)*(char *)(*(int *)(param_1 + 0x76) + 8);
    }
    local_18 = 1;
    local_1c = -1;
    iVar3 = 0;
    do {
      if ((1 << ((byte)iVar3 & 0x1f) & *(uint *)(param_1 + 0x8a8)) != 0) {
        local_1c = iVar3;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 7);
    if (local_1c != -1) {
      for (iVar3 = *(int *)(param_1 + 0x7a); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x54)) {
        iVar2 = FUN_00446bf0(iVar3);
        if (((iVar2 == 0) && (*(char *)(iVar3 + 8) != local_1c)) &&
           (iVar2 = FUN_004412d4(local_1c,(int)*(char *)(iVar3 + 8),2), iVar2 == 0)) {
          local_18 = 0;
        }
      }
    }
    if (((local_14 != -1) || (local_c != -1)) || ((local_8 == 0 && (local_18 == 0)))) {
      bVar7 = *(char *)(param_1 + 0x21) != '\0';
      local_20 = 1;
      FUN_00456618(param_1);
      FUN_00456150(param_1,(int)*(char *)(param_1 + 0x20),local_10,local_20);
      for (puVar5 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),0xffffffff);
          puVar5 != (undefined2 *)0x0;
          puVar5 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x7a),*puVar5)) {
        if ((bVar7) || ((&DAT_004faf8d)[*(char *)(puVar5 + 3) * 0x24] != '\x01')) {
          FUN_00451b68(puVar5);
        }
      }
      if (local_20 != 0) {
        piVar6 = (int *)(param_1 + 0x154);
        local_24 = 0;
        do {
          if (*piVar6 != 0) {
            FUN_00451de4(*piVar6);
          }
          local_24 = local_24 + 1;
          piVar6 = piVar6 + 0xd;
        } while (local_24 < 0x24);
      }
      for (puVar5 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x76),0xffffffff);
          puVar5 != (undefined2 *)0x0;
          puVar5 = (undefined2 *)FUN_00456214(*(undefined4 *)(param_1 + 0x76),*puVar5)) {
        if ((bVar7) || ((&DAT_004faf8d)[*(char *)(puVar5 + 3) * 0x24] != '\x01')) {
          FUN_00451b68(puVar5);
        }
      }
      if (bVar7) {
        iVar3 = FUN_0044d230(param_1,0x13,0);
        if (iVar3 == -1) {
          DAT_005649c8 = 0;
          for (iVar3 = DAT_0057cdf8[0x1f]; iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x16)) {
            FUN_004522c0(iVar3);
          }
        }
        else {
          DAT_005649c8 = (int)*(short *)(param_1 + 0x30);
        }
      }
      else {
        DAT_005649c8 = 0;
      }
      if (local_1c != -1) {
        FUN_00452250(local_1c,param_1);
      }
      *DAT_0057cdf8 = DAT_0057e240;
      if (local_20 != 0) {
        FUN_00451410();
      }
      FUN_004526b0();
    }
  }
  return;
}

