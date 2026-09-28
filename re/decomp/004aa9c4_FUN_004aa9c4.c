// FUN_004aa9c4 @ 004aa9c4 size=1909 sig=undefined FUN_004aa9c4() cc=unknown
// callers: FUN_004ab4e8,FUN_004ab4c4,FUN_004aa380
// callees: memset,thunk_FUN_004ae2f0,FUN_004ab1a0,thunk_FUN_004ae2f0,FUN_004ad944

int FUN_004aa9c4(code *param_1,code *param_2,undefined4 param_3,byte *param_4,undefined4 *param_5)

{
  byte bVar1;
  byte *pbVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  longlong lVar7;
  byte local_64 [32];
  byte local_44 [2];
  byte local_42 [2];
  byte *local_40;
  int local_3c;
  int local_38;
  undefined1 local_34 [12];
  undefined8 local_28;
  byte local_1d;
  uint local_1c;
  undefined4 local_18;
  uint local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  lVar7 = CONCAT44(local_28._4_4_,(undefined4)local_28);
LAB_004aa9da:
  do {
    local_1d = *param_4;
    if (local_1d == 0) {
      return local_8;
    }
    pbVar2 = param_4 + 1;
    local_28 = lVar7;
    if (local_1d == 0x25) {
      local_1d = param_4[1];
      param_4 = param_4 + 2;
      pbVar2 = param_4;
      if (local_1d != 0x25) {
        local_14 = 0xffffffff;
        uVar5 = 0x20;
        local_3c = 0;
LAB_004aaaf6:
        if ((local_1d & 0x80) == 0) {
          iVar4 = (int)(char)(&DAT_005206f0)[(int)(char)local_1d & 0x7f];
        }
        else {
          iVar4 = 2;
        }
        switch(iVar4) {
        default:
          goto switchD_004aab1c_caseD_0;
        case 2:
          goto switchD_004aab1c_caseD_2;
        case 4:
          uVar5 = uVar5 | 1;
          local_1d = *param_4;
          param_4 = param_4 + 1;
          goto LAB_004aaaf6;
        case 5:
          if ((int)local_14 < 0) {
            iVar4 = (int)(char)local_1d;
          }
          else {
            iVar4 = local_14 * 10 + (int)(char)local_1d;
          }
          local_14 = iVar4 - 0x30;
          local_1d = *param_4;
          param_4 = param_4 + 1;
          goto LAB_004aaaf6;
        case 6:
        case 7:
          if ((uVar5 & 4) == 0) {
            if ((uVar5 & 2) == 0) {
              if (iVar4 == 7) {
                local_3c = 1;
              }
            }
            else {
              local_3c = 0;
            }
          }
          else {
            local_3c = 1;
          }
          if ((uVar5 & 1) == 0) {
            if (local_3c == 0) {
              local_40 = (byte *)*param_5;
              param_5 = param_5 + 1;
            }
            else {
              local_40 = (byte *)*param_5;
              param_5 = param_5 + 1;
            }
          }
          if ((int)local_14 < 0) {
            local_14 = 1;
          }
          if (local_14 == 0) goto LAB_004ab02b;
          goto LAB_004aafd3;
        case 8:
        case 9:
          local_18 = 10;
          goto switchD_004aab1c_caseD_0;
        case 10:
          local_18 = 0;
          goto switchD_004aab1c_caseD_0;
        case 0xb:
          thunk_FUN_004ae2f0(local_34,param_1,param_2,param_3,local_14 & 0x7fff,&local_c,&local_10);
          if (local_10 < 0) goto LAB_004ab17c;
          if (local_10 == 0) goto switchD_004aab1c_caseD_2;
          lVar7 = local_28;
          if ((uVar5 & 1) == 0) {
            thunk_FUN_004ae2f0(local_34,*param_5,uVar5);
            local_8 = local_8 + 1;
            param_5 = param_5 + 1;
            lVar7 = local_28;
          }
          goto LAB_004aa9da;
        case 0xc:
          uVar5 = uVar5 | 8;
          local_1d = *param_4;
          param_4 = param_4 + 1;
          goto LAB_004aaaf6;
        case 0xd:
          uVar5 = uVar5 | 2;
          local_1d = *param_4;
          param_4 = param_4 + 1;
          goto LAB_004aaaf6;
        case 0xe:
          uVar5 = uVar5 | 4;
          local_1d = *param_4;
          param_4 = param_4 + 1;
          goto LAB_004aaaf6;
        case 0xf:
          local_18 = 8;
          goto switchD_004aab1c_caseD_0;
        case 0x10:
        case 0x11:
          if ((uVar5 & 4) == 0) {
            if ((uVar5 & 2) == 0) {
              if (iVar4 == 0x11) {
                local_3c = 1;
              }
            }
            else {
              local_3c = 0;
            }
          }
          else {
            local_3c = 1;
          }
          goto LAB_004aae54;
        case 0x12:
          memset(local_64,0,0x20);
          local_1c = 0;
          bVar3 = *param_4;
          pbVar2 = param_4 + 1;
          if (bVar3 == 0x5e) {
            local_1c = 1;
            bVar3 = param_4[1];
            pbVar2 = param_4 + 2;
          }
          goto LAB_004ab066;
        case 0x13:
          lVar7 = (longlong)local_c;
          goto LAB_004aacd1;
        case 0x14:
          goto switchD_004aab1c_caseD_14;
        case 0x15:
          lVar7 = FUN_004ab1a0(param_1,param_2,param_3,0x10,8,&local_c,&local_10);
          if (local_10 < 1) goto switchD_004aab1c_caseD_2;
          if ((uVar5 & 1) == 0) {
            *(int *)*param_5 = (int)lVar7;
            local_8 = local_8 + 1;
            param_5 = param_5 + 1;
          }
          goto LAB_004aa9da;
        case 0x16:
          uVar5 = uVar5 & 0xffffffdf;
          local_1d = *param_4;
          param_4 = param_4 + 1;
          goto LAB_004aaaf6;
        case 0x17:
          uVar5 = uVar5 | 0x20;
          local_1d = *param_4;
          param_4 = param_4 + 1;
          goto LAB_004aaaf6;
        case 0x18:
          if ((*param_4 == 0x36) && (param_4[1] == 0x34)) {
            uVar5 = uVar5 & 0xfffffff9 | 8;
            param_4 = param_4 + 2;
          }
          else if ((*param_4 == 0x33) && (param_4[1] == 0x32)) {
            uVar5 = uVar5 & 0xfffffff5 | 4;
            param_4 = param_4 + 2;
          }
          else if ((*param_4 == 0x31) && (param_4[1] == 0x36)) {
            uVar5 = uVar5 & 0xfffffff3 | 2;
            param_4 = param_4 + 2;
          }
          else if (*param_4 == 0x38) {
            uVar5 = uVar5 & 0xfffffff1;
            param_4 = param_4 + 1;
          }
          local_1d = *param_4;
          param_4 = param_4 + 1;
          goto LAB_004aaaf6;
        }
      }
    }
    param_4 = pbVar2;
    local_c = local_c + 1;
    bVar3 = (*param_1)(param_3);
    if (bVar3 == 0xff) goto LAB_004ab17c;
    if (((local_1d & 0x80) != 0) || ((&DAT_005206f0)[(int)(char)local_1d & 0x7f] != '\x01')) {
      if (bVar3 != local_1d) {
        (*param_2)((int)(char)bVar3,param_3);
        goto switchD_004aab1c_caseD_2;
      }
      lVar7 = local_28;
      if ((((&DAT_0069f56d)[bVar3] & 4) != 0) && (*param_4 != 0)) {
        local_1d = (*param_1)(param_3);
        if (local_1d == 0xff) goto LAB_004ab17c;
        bVar1 = *param_4;
        param_4 = param_4 + 1;
        if (bVar1 != local_1d) {
          (*param_2)((int)(char)local_1d,param_3);
          (*param_2)((int)(char)bVar3,param_3);
          goto switchD_004aab1c_caseD_2;
        }
        local_c = local_c + 1;
        lVar7 = local_28;
      }
      goto LAB_004aa9da;
    }
    while (((bVar3 & 0x80) == 0 && ((&DAT_005206f0)[(int)(char)bVar3 & 0x7f] == '\x01'))) {
      local_c = local_c + 1;
      bVar3 = (*param_1)(param_3);
      if (bVar3 == 0xff) goto LAB_004ab17c;
    }
    (*param_2)((int)(char)bVar3,param_3);
    local_c = local_c + -1;
    lVar7 = local_28;
  } while( true );
switchD_004aab1c_caseD_14:
  local_18 = 0x10;
switchD_004aab1c_caseD_0:
  lVar7 = FUN_004ab1a0(param_1,param_2,param_3,local_18,local_14 & 0x7fff,&local_c,&local_10);
  local_28 = lVar7;
  if (local_10 < 0) goto LAB_004ab17c;
  if (local_10 == 0) goto switchD_004aab1c_caseD_2;
LAB_004aacd1:
  local_28._0_4_ = (undefined4)lVar7;
  if ((('@' < (char)local_1d) && ((char)local_1d < '[')) && (local_1d != 0x58)) {
    uVar5 = uVar5 | 4;
  }
  if ((uVar5 & 1) == 0) {
    if ((uVar5 & 8) == 0) {
      if ((uVar5 & 4) == 0) {
        if ((uVar5 & 2) == 0) {
          *(undefined4 *)*param_5 = (undefined4)local_28;
        }
        else {
          *(short *)*param_5 = (short)lVar7;
        }
      }
      else {
        *(undefined4 *)*param_5 = (undefined4)local_28;
      }
    }
    else {
      *(longlong *)*param_5 = lVar7;
    }
    param_5 = param_5 + 1;
    if (local_1d != 0x6e) {
      local_8 = local_8 + 1;
    }
  }
  goto LAB_004aa9da;
LAB_004ab066:
  pbVar6 = pbVar2;
  local_1d = bVar3;
  if (bVar3 == 0) goto switchD_004aab1c_caseD_2;
  local_64[(int)(char)bVar3 >> 3 & 0x1f] =
       local_64[(int)(char)bVar3 >> 3 & 0x1f] | '\x01' << (bVar3 & 7);
  bVar3 = *pbVar6;
  param_4 = pbVar6 + 1;
  if (bVar3 != 0x5d) {
    pbVar2 = param_4;
    if (((bVar3 == 0x2d) && ((char)local_1d < (char)*param_4)) && (*param_4 != 0x5d)) {
      bVar3 = *param_4;
      while( true ) {
        local_1d = local_1d + 1;
        pbVar2 = pbVar6 + 2;
        if ((char)bVar3 <= (char)local_1d) break;
        local_64[(int)(char)local_1d >> 3 & 0x1f] =
             local_64[(int)(char)local_1d >> 3 & 0x1f] | '\x01' << (local_1d & 7);
      }
    }
    goto LAB_004ab066;
  }
  if (local_14 == 0xffffffff) {
    local_14 = 0x7fff;
  }
  if ((uVar5 & 1) == 0) {
    local_40 = (byte *)*param_5;
    param_5 = param_5 + 1;
  }
  local_38 = 0;
  bVar3 = 0x5d;
  while (local_14 = local_14 - 1, -1 < (int)local_14) {
    local_c = local_c + 1;
    bVar3 = (*param_1)(param_3);
    if ((bVar3 == 0xff) ||
       (((1 << (bVar3 & 7) & (int)(char)local_64[(int)(char)bVar3 >> 3 & 0x1f]) != 0) == local_1c))
    break;
    local_38 = local_38 + 1;
    if ((uVar5 & 1) == 0) {
      *local_40 = bVar3;
      local_40 = local_40 + 1;
    }
  }
  lVar7 = local_28;
  if (-1 < (int)local_14) {
    (*param_2)((int)(char)bVar3,param_3);
    local_c = local_c + -1;
    lVar7 = local_28;
  }
  if ((local_38 != 0) && ((uVar5 & 1) == 0)) {
    *local_40 = 0;
    local_8 = local_8 + 1;
    local_40 = local_40 + 1;
  }
  local_28 = lVar7;
  if (bVar3 == 0xff) {
LAB_004ab17c:
    (*param_2)(0xffffffff,param_3);
    if (local_8 == 0) {
      local_8 = -1;
    }
    else {
switchD_004aab1c_caseD_2:
    }
    return local_8;
  }
  goto LAB_004aa9da;
  while (((bVar3 & 0x80) == 0 &&
         (lVar7 = local_28, (&DAT_005206f0)[(int)(char)bVar3 & 0x7f] == '\x01'))) {
LAB_004aae54:
    local_c = local_c + 1;
    local_28 = lVar7;
    bVar3 = (*param_1)(param_3);
    if (bVar3 == 0xff) goto LAB_004ab17c;
  }
  if ((uVar5 & 1) == 0) {
    if (local_3c == 0) {
      local_40 = (byte *)*param_5;
    }
    else {
      local_40 = (byte *)*param_5;
    }
    param_5 = param_5 + 1;
    local_8 = local_8 + 1;
  }
  if (local_14 == 0xffffffff) {
    local_14 = 0x7fff;
  }
  do {
    if ((uVar5 & 1) == 0) {
      if (local_3c == 0) {
        *local_40 = bVar3;
        local_40 = local_40 + 1;
      }
      else {
        iVar4 = FUN_004ad944(local_42,local_40,1);
        if (iVar4 < 1) {
          local_c = local_c + -1;
        }
        else {
          *local_40 = local_42[0];
          local_40 = local_40 + 1;
        }
      }
    }
    local_c = local_c + 1;
    bVar3 = (*param_1)(param_3);
  } while ((((bVar3 != 0xff) && (bVar3 != 0)) &&
           (((bVar3 & 0x80) != 0 || ((&DAT_005206f0)[(int)(char)bVar3 & 0x7f] != '\x01')))) &&
          (local_14 = local_14 - 1, 0 < (int)local_14));
  (*param_2)((int)(char)bVar3,param_3);
  local_c = local_c + -1;
  lVar7 = local_28;
  if ((uVar5 & 1) == 0) {
    if (local_3c == 0) {
      *local_40 = 0;
    }
    else {
      local_40[0] = 0;
      local_40[1] = 0;
    }
  }
  goto LAB_004aa9da;
  while( true ) {
    lVar7 = local_28;
    if ((uVar5 & 1) == 0) {
      if (local_3c == 0) {
        *local_40 = bVar3;
        local_40 = local_40 + 1;
      }
      else {
        iVar4 = FUN_004ad944(local_44,local_40,1);
        lVar7 = local_28;
        if (0 < iVar4) {
          *local_40 = local_44[0];
          local_40 = local_40 + 1;
        }
      }
    }
    local_14 = local_14 - 1;
    if ((int)local_14 < 1) break;
LAB_004aafd3:
    local_c = local_c + 1;
    local_28 = lVar7;
    bVar3 = (*param_1)(param_3);
    if (bVar3 == 0xff) goto LAB_004ab17c;
  }
LAB_004ab02b:
  if ((uVar5 & 1) == 0) {
    local_8 = local_8 + 1;
  }
  goto LAB_004aa9da;
}

