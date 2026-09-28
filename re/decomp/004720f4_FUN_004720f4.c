// FUN_004720f4 @ 004720f4 size=465 sig=undefined FUN_004720f4() cc=unknown
// callers: FUN_0044f110,ProduceUnits,FUN_004722e0
// callees: FUN_00471cc0,FUN_00472974,FUN_00471bec,DebugMessage,FUN_00472018,FUN_004589a0,FUN_00471fec
// strings: \"Collect Req. Res\"|\"Illegal Request for Material\"

uint FUN_004720f4(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *local_2c;
  int *local_28;
  int *local_24;
  int *local_20;
  int *local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined1 local_c [4];
  uint local_8;
  
  local_8 = 0;
  FUN_004589a0(s_Collect_Req__Res_004d6395);
  FUN_00471bec();
  local_10 = 1;
  local_24 = (int *)(param_1 + 0x3e);
  local_1c = (int *)(param_2 + 8);
  local_20 = param_3;
  do {
    local_20 = local_20 + 1;
    if (*local_20 < *local_1c) {
      switch(local_10) {
      default:
        local_14 = *local_1c - *local_20;
        iVar5 = (*local_1c - *local_20) - *local_24;
        if (0 < iVar5) {
          FUN_00472974(param_1,(int)*(char *)(param_1 + 0x20),local_10,iVar5,1,local_c,local_c);
        }
        piVar3 = (int *)(local_10 * 4 + param_1 + 0x3a);
        if (local_14 <= *piVar3) {
          piVar3 = &local_14;
        }
        iVar5 = *piVar3;
        *local_24 = *local_24 - iVar5;
        *local_20 = *local_20 + iVar5;
        local_14 = local_14 - iVar5;
        if (local_14 != 0) {
          local_8 = local_8 | 1 << ((byte)local_10 & 0x1f);
        }
        break;
      case 4:
        iVar5 = FUN_00471cc0(param_3);
        iVar5 = *(int *)(param_2 + 0x14) - iVar5;
        iVar4 = FUN_00471fec(param_1);
        if (iVar4 < iVar5) {
          FUN_00472018(param_1,iVar5 - iVar4,1);
        }
        iVar4 = FUN_00471fec(param_1);
        local_18 = 0;
        local_2c = &DAT_004d6344;
        local_28 = &DAT_004d6334;
        do {
          iVar1 = *local_28;
          iVar2 = *local_2c;
          piVar3 = (int *)(param_1 + 0x3a + iVar1 * 4);
          iVar6 = iVar4;
          while (((iVar4 = iVar6, 0 < iVar5 && (0 < iVar4)) && (*piVar3 != 0))) {
            iVar6 = iVar4 - *piVar3 * iVar2;
            if ((iVar2 <= iVar5) || (iVar6 < iVar5)) {
              *piVar3 = *piVar3 + -1;
              param_3[iVar1] = param_3[iVar1] + 1;
              iVar5 = iVar5 - iVar2;
              iVar6 = iVar4 - iVar2;
            }
          }
          local_18 = local_18 + 1;
          local_2c = local_2c + 1;
          local_28 = local_28 + 1;
        } while (local_18 < 4);
        if (0 < iVar5) {
          local_8 = local_8 | 0x10;
        }
        break;
      case 5:
      case 6:
      case 7:
      case 10:
        DebugMessage(s_Illegal_Request_for_Material_004d63a6);
      }
    }
    local_10 = local_10 + 1;
    local_24 = local_24 + 1;
    local_1c = local_1c + 1;
  } while (local_10 < 0xb);
  return local_8;
}

