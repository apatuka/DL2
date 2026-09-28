// FUN_00446084 @ 00446084 size=952 sig=undefined FUN_00446084() cc=unknown
// callers: NetMoveUnit,FUN_00457624,FUN_0045727c,FUN_0045539c,FUN_004757c0
// callees: FUN_00446b94,ReLinkArmy,FUN_004471c0,FUN_00445b94,FUN_00445a74,FUN_00445a04,sprintf,DebugMessage,FUN_0042836c,FUN_00445aac,FUN_00447190
// strings: \"A siege cruiser can either move or launch missiles but not both in a turn.\"|\"Oolan's Advice\"|\"_MoveUnit: %s in %s without transport.\\nFound while moving %s to %s.\"

undefined4 FUN_00446084(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined1 local_110 [256];
  int local_10;
  int local_c;
  int local_8;
  
  iVar6 = (int)(char)(&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24];
  if (iVar6 == 1) {
    iVar6 = 5;
  }
  iVar2 = 0x2000 << (*(byte *)(param_1 + 8) & 0x1f);
  iVar5 = (int)*(char *)(param_1 + 8);
  iVar3 = iVar6;
  cVar1 = FUN_00447190(param_1);
  FUN_00446b94(*(undefined4 *)(param_1 + 0x38),param_2,(int)cVar1,iVar3,iVar5,iVar2);
  local_8 = (int)*(short *)(param_2 + 0xa70 + *(char *)(param_1 + 8) * 2);
  local_c = *(int *)(param_1 + 0x3c);
  if (*(char *)(param_1 + 8) == *(char *)(local_c + 0x20)) {
    local_c = local_c + 0x76;
  }
  else {
    local_c = local_c + 0x7a;
  }
  cVar1 = FUN_00447190(param_1);
  if (cVar1 < local_8) {
    uVar4 = 0;
  }
  else {
    if (*(char *)(param_2 + 0x20) == *(char *)(param_1 + 8)) {
      iVar3 = FUN_00445b94(param_2,(int)*(char *)(param_1 + 6));
      if (iVar3 == 0) {
        return 0;
      }
      local_10 = param_2 + 0x76;
    }
    else {
      if (((*(char *)(param_2 + 0x21) == '\0') && (iVar6 == 5)) ||
         ((*(char *)(param_2 + 0x21) != '\0' && (iVar6 == 2)))) {
        return 0;
      }
      local_10 = param_2 + 0x7a;
    }
    if (*(char *)(param_1 + 6) == '$') {
      iVar3 = *(int *)(param_1 + 0x48);
      if ((iVar3 != 0) && (*(int *)(iVar3 + 0x38) != *(int *)(iVar3 + 0x3c))) {
        if ((char)(&DAT_0059f161)[*(char *)(param_1 + 8) * 0x2d8] < '\x03') {
          FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,
                       PTR_s_A_siege_cruiser_can_either_move_o_005095e0,4,0,9);
        }
        return 0;
      }
    }
    else if (((*(char *)(param_1 + 6) == '#') && (*(int *)(param_1 + 0x48) != 0)) &&
            (*(int *)(*(int *)(param_1 + 0x48) + 0x3c) != *(int *)(param_1 + 0x3c))) {
      if ((char)(&DAT_0059f161)[*(char *)(param_1 + 8) * 0x2d8] < '\x03') {
        FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_A_siege_cruiser_can_either_move_o_005095e0,
                     4,0,9);
      }
      return 0;
    }
    ReLinkArmy(param_1,param_2,local_c,local_10);
    if ((*(char *)(param_1 + 0x25) == '\v') ||
       ((*(char *)(param_1 + 0x25) == '\r' && (*(char *)(param_2 + 0x20) != *(char *)(param_1 + 8)))
       )) {
      *(undefined1 *)(param_1 + 0x25) = 0;
    }
    if ((*(char *)(param_1 + 6) == '\f') || (*(char *)(param_1 + 6) == '#')) {
      FUN_00445aac(param_1,param_2,local_c,local_10);
    }
    else if (iVar6 == 5) {
      if ((*(char *)(param_2 + 0x21) != '\0') && (*(int *)(param_1 + 0x48) != 0)) {
        FUN_00445a74(param_1);
      }
      if (*(char *)(param_2 + 0x21) == '\0') {
        FUN_00445a04(param_1);
      }
    }
    cVar1 = FUN_00447190(param_1);
    *(char *)(param_1 + 10) = cVar1 - (char)local_8;
    if (param_3 == 0) {
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x3c);
    }
    else {
      *(int *)(param_1 + 0x40) = param_3;
    }
    if (DAT_004d5aa0 != '\0') {
      FUN_004471c0(*(undefined4 *)(param_1 + 0x38));
      FUN_004471c0(param_2);
    }
    if (*(char *)(param_2 + 0x21) == '\0') {
      for (iVar6 = *(int *)(param_2 + 0x76); iVar6 != 0; iVar6 = *(int *)(iVar6 + 0x54)) {
        if (((&DAT_004faf8d)[*(char *)(iVar6 + 6) * 0x24] == '\x01') &&
           (*(int *)(iVar6 + 0x48) == 0)) {
          sprintf(local_110,s__MoveUnit___s_in__s_without_tran_004c537f,iVar6 + 0xb,param_2,
                  param_1 + 0xb,param_2);
          DebugMessage(local_110);
        }
      }
      for (iVar6 = *(int *)(param_2 + 0x7a); iVar6 != 0; iVar6 = *(int *)(iVar6 + 0x54)) {
        if (((&DAT_004faf8d)[*(char *)(iVar6 + 6) * 0x24] == '\x01') &&
           (*(int *)(iVar6 + 0x48) == 0)) {
          sprintf(local_110,s__MoveUnit___s_in__s_without_tran_004c537f,iVar6 + 0xb,param_2,
                  param_1 + 0xb,param_2);
          DebugMessage(local_110);
        }
      }
    }
    if (*(char *)(*(int *)(param_1 + 0x38) + 0x21) == '\0') {
      for (iVar6 = *(int *)(*(int *)(param_1 + 0x38) + 0x76); iVar6 != 0;
          iVar6 = *(int *)(iVar6 + 0x54)) {
        if (((&DAT_004faf8d)[*(char *)(iVar6 + 6) * 0x24] == '\x01') &&
           (*(int *)(iVar6 + 0x48) == 0)) {
          sprintf(local_110,s__MoveUnit___s_in__s_without_tran_004c537f,iVar6 + 0xb,
                  *(undefined4 *)(param_1 + 0x38),param_1 + 0xb,param_2);
          DebugMessage(local_110);
        }
      }
      for (iVar6 = *(int *)(*(int *)(param_1 + 0x38) + 0x7a); iVar6 != 0;
          iVar6 = *(int *)(iVar6 + 0x54)) {
        if (((&DAT_004faf8d)[*(char *)(iVar6 + 6) * 0x24] == '\x01') &&
           (*(int *)(iVar6 + 0x48) == 0)) {
          sprintf(local_110,s__MoveUnit___s_in__s_without_tran_004c537f,iVar6 + 0xb,
                  *(undefined4 *)(param_1 + 0x38),param_1 + 0xb,param_2);
          DebugMessage(local_110);
        }
      }
    }
    uVar4 = 1;
  }
  return uVar4;
}

