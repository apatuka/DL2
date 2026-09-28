// FUN_00492d67 @ 00492d67 size=929 sig=undefined FUN_00492d67() cc=unknown
// callers: FUN_0049e47a,FUN_00493108,FUN_004897ea
// callees: FUN_00492578,FUN_00491f94,FUN_00493149,FUN_00499b9f,FUN_00492b0c,FUN_00491efa,FUN_00491e02,FUN_00492aac,FUN_00492307,FUN_00491a2b,FUN_00491ace,FUN_0049a760,FUN_00492b47,FUN_00491df3,FUN_00491b5e,FUN_00491f47,FUN_004935fc

char * FUN_00492d67(int *param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int local_58 [2];
  int local_50;
  undefined1 local_48 [4];
  short local_44;
  short local_42;
  short local_3e;
  uint local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  int local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if ((param_1 == (int *)0x0) || (*param_1 == 0)) {
    pcVar2 = (char *)0x0;
  }
  else {
    FUN_00491a2b(0);
    if ((*(byte *)(param_1 + 5) & 4) != 0) {
      FUN_00491df3(1);
      FUN_00491f47(0xf7);
      FUN_00491f94(1);
    }
    FUN_00491b5e(local_48);
    iVar5 = param_1[2];
    iVar1 = param_1[1];
    local_8 = param_1[4];
    iVar3 = param_1[3];
    if ((*(byte *)(param_1 + 5) & 0x10) == 0) {
      local_30 = 0;
      local_2c = 0;
    }
    else {
      if (param_1[6] < param_1[7]) {
        local_2c = param_1[6];
      }
      else {
        local_2c = param_1[7];
      }
      if (param_1[6] < param_1[7]) {
        local_30 = param_1[7];
      }
      else {
        local_30 = param_1[6];
      }
    }
    if ((*(byte *)(param_1 + 5) & 2) != 0) {
      FUN_004935fc(iVar1,iVar5,iVar3,local_8,DAT_0065ec14);
    }
    FUN_00491efa(0xff);
    local_c = iVar3 - iVar1;
    pcVar2 = (char *)*param_1;
    if ((*(byte *)(param_1 + 5) & 8) == 0) {
      local_10 = iVar5 + local_44;
    }
    else {
      iVar3 = FUN_00493149(pcVar2,local_c,0,0);
      uVar4 = (local_8 - iVar5) - iVar3 * ((int)local_44 + (int)local_42 + (int)local_3e);
      iVar3 = (int)uVar4 >> 1;
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((uVar4 & 1) != 0);
      }
      local_10 = iVar3 + iVar5;
      if (iVar3 + iVar5 < iVar5) {
        local_10 = iVar5;
      }
      local_10 = local_10 + local_44;
    }
    local_24 = 0;
    local_20 = 0;
    local_28 = FUN_0049a760(*(int *)(DAT_0051bddc + 0xc) << 0x10 | 8);
    iVar5 = 0;
    while (*pcVar2 != '\0') {
      FUN_00492b47(pcVar2,local_c,0xffffffff,&local_14,&local_18,0,&local_20);
      if ((*(byte *)(param_1 + 5) & 1) == 0) {
        if ((*(byte *)(param_1 + 5) & 0x20) == 0) {
          FUN_00492aac(local_20 + iVar1,local_10);
        }
        else {
          FUN_00492aac((local_c + iVar1 + local_20) - local_18,local_10);
        }
      }
      else {
        FUN_00492aac(((local_c - local_20) - local_18 >> 1) + iVar1 + local_20,local_10);
      }
      local_3c = (uint)*(byte *)(DAT_0051dc24 + 8 + DAT_0065ec1c * 4) << 0x10 |
                 (uint)*(byte *)(DAT_0051dc24 + 9 + DAT_0065ec1c * 4) << 8 |
                 (uint)*(byte *)(DAT_0051dc24 + 10 + DAT_0065ec1c * 4);
      local_3c = FUN_00499b9f(DAT_0051bddc,local_3c);
      for (local_1c = 0; (*pcVar2 != '\0' && (local_1c < local_14)); local_1c = local_1c + 1) {
        if ((iVar5 < local_2c) || (local_30 <= iVar5)) {
          if (*pcVar2 == '\t') {
            DAT_0065ec40 = ((DAT_0065ec40 - iVar1) / DAT_0051dc18) * DAT_0051dc18 + DAT_0051dc18 +
                           iVar1;
          }
          else {
            FUN_00492578(*pcVar2);
          }
        }
        else {
          if (*pcVar2 == '\t') {
            local_58[0] = 0;
            local_50 = (((DAT_0065ec40 - iVar1) / DAT_0051dc18) * DAT_0051dc18 + DAT_0051dc18) -
                       DAT_0065ec40;
          }
          else {
            FUN_00492307(*pcVar2,local_58);
          }
          FUN_004935fc(DAT_0065ec40 + local_58[0],DAT_0065ec3c - (DAT_0065ebfc + 1),
                       DAT_0065ec40 + local_50,DAT_0065ec00 + DAT_0065ec3c + 1,local_3c);
          local_34 = DAT_0065ec10;
          local_38 = DAT_0065ec14;
          FUN_00491e02(DAT_0065ec18);
          FUN_00491efa(DAT_0065ec1c);
          if (*pcVar2 == '\t') {
            DAT_0065ec40 = DAT_0065ec40 + local_50;
          }
          else {
            FUN_00492578(*pcVar2);
          }
          FUN_00491e02(local_34);
          FUN_00491efa(local_38);
        }
        pcVar2 = pcVar2 + 1;
        iVar5 = iVar5 + 1;
      }
      pcVar2 = (char *)FUN_00492b0c(pcVar2);
      iVar5 = (int)pcVar2 - *param_1;
      if ((*pcVar2 == '\0') ||
         (local_10 = local_10 + (int)local_44 + (int)local_42 + (int)local_3e, local_8 <= local_10))
      break;
      local_20 = local_24;
    }
    FUN_0049a760(local_28);
    FUN_00491ace();
  }
  return pcVar2;
}

