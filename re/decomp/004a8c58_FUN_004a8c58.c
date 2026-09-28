// FUN_004a8c58 @ 004a8c58 size=994 sig=undefined FUN_004a8c58() cc=unknown
// callers: Local_unwind
// callees: free,FUN_004b0284,FUN_004a881e,FUN_004a8ab8,FUN_004a7826,__assertfail,FUN_004a8bdc
// strings: \"XX.CPP\"|\"dttPtr->dttFlags & (DTCVF_PTRVAL|DTCVF_RETVAL)\"|\"dttPtr->dttType->tpMask & TM_IS_PTR\"|\"dttPtr->dttType->tpPtr.tppBaseType->tpClass.tpcFlags & CF_HAS_DTOR\"|\"IS_CLASS(dttPtr->dttType->tpMask) && (dttPtr->dttType->tpClass.tpcFlags & CF_HAS_DTOR)\"|\"varType->tpClass.tpcFlags & CF_HAS_DTOR\"|\"elemType->tpClass.tpcFlags & CF_HAS_DTOR\"|\"varType->tpMask & TM_IS_PTR\"|\"dtCnt >= 0\"

undefined4 FUN_004a8c58(int *param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int local_24;
  int *local_20;
  int local_1c;
  int *local_18;
  int local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  local_10 = 0;
  if (param_1 == (int *)0x0) {
    uVar4 = 0;
  }
  else {
    local_8 = *(uint *)(param_3 + 0x1c);
    local_c = local_8 - param_2;
    if ((*(byte *)(param_1 + 1) & 0x20) != 0) {
      if ((*(byte *)(param_1 + 1) & 0x11) == 0) {
        __assertfail(s_dttPtr_>dttFlags____DTCVF_PTRVAL_0051f81b,s_XX_CPP_0051f84a,0xe00);
      }
      if ((*(byte *)(*param_1 + 4) & 0x10) == 0) {
        __assertfail(s_dttPtr_>dttType_>tpMask___TM_IS__0051f851,s_XX_CPP_0051f875,0xe04);
      }
      if ((*(byte *)(*(int *)(*param_1 + 8) + 0xc) & 2) == 0) {
        __assertfail(s_dttPtr_>dttType_>tpPtr_tppBaseTy_0051f87c,s_XX_CPP_0051f8bf,0xe05);
      }
      local_c = *(uint *)(*(int *)(*param_1 + 8) + 0x20);
    }
    if ((*(byte *)((int)param_1 + 5) & 1) == 0) {
      piVar5 = param_1;
      if (((int)local_c < 1) && ((*(byte *)((int)param_1 + 5) & 4) == 0)) {
        if ((param_1[1] & 3U) != 3) {
          return 0;
        }
        local_10 = local_10 + 1;
      }
      else {
        for (; *piVar5 != 0; piVar5 = piVar5 + 3) {
          local_14 = *piVar5;
          iVar7 = 1;
          if (((((*(byte *)(local_14 + 4) & 0x10) != 0) &&
               (local_14 = *(int *)(local_14 + 8), (*(byte *)(local_14 + 4) & 2) != 0)) &&
              ((*(byte *)(local_14 + 0xc) & 0x20) != 0)) && ((*(byte *)(piVar5 + 1) & 8) != 0)) {
            if ((*(byte *)(local_14 + 0xc) & 2) == 0) {
              __assertfail(s_varType_>tpClass_tpcFlags___CF_H_0051f924,s_XX_CPP_0051f94c,0xe6e);
            }
            if ((*(byte *)(piVar5 + 1) & 4) == 0) {
              local_18 = (int *)piVar5[2];
            }
            else {
              local_18 = (int *)(param_4 + piVar5[2]);
            }
            local_18 = (int *)*local_18;
            if ((*(byte *)(piVar5 + 1) & 0x40) != 0) {
              local_18 = (int *)((int)local_18 + 4);
            }
            local_18 = (int *)FUN_004a8bdc(local_18,&local_14);
          }
          iVar6 = local_14;
          if ((*(byte *)(local_14 + 5) & 4) != 0) {
            iVar7 = *(int *)(local_14 + 0xc);
            iVar6 = *(int *)(local_14 + 8);
          }
          if ((*(byte *)(iVar6 + 0xc) & 2) == 0) {
            __assertfail(s_elemType_>tpClass_tpcFlags___CF__0051f953,s_XX_CPP_0051f97c,0xe92);
          }
          uVar8 = iVar7 * *(int *)(iVar6 + 0x20);
          if (local_c <= uVar8) goto LAB_004a8e5a;
          local_c = local_c - uVar8;
        }
        piVar5 = piVar5 + -3;
      }
LAB_004a8e5a:
      do {
        local_1c = *piVar5;
        uVar8 = piVar5[1];
        if ((uVar8 & 4) == 0) {
          local_20 = (int *)piVar5[2];
        }
        else {
          local_20 = (int *)(param_4 + piVar5[2]);
        }
        if ((uVar8 & 0x11) != 0) {
          if ((*(byte *)(local_1c + 4) & 0x10) == 0) {
            __assertfail(s_varType_>tpMask___TM_IS_PTR_0051f983,s_XX_CPP_0051f99f,0xec2);
          }
          local_1c = *(int *)(local_1c + 8);
          local_24 = *local_20;
          local_20 = (int *)local_24;
          if ((uVar8 & 0x48) == 0x40) {
            local_20 = (int *)(local_24 + 4);
          }
          if ((((*(byte *)(local_1c + 4) & 2) != 0) && ((*(byte *)(local_1c + 0xc) & 0x20) != 0)) &&
             ((uVar8 & 8) != 0)) {
            local_20 = (int *)FUN_004a8bdc(local_20,&local_1c);
          }
        }
        uVar3 = local_8;
        uVar2 = local_c;
        if (local_10 == 0) {
          if ((uVar8 & 0x400) == 0) {
            uVar4 = 0;
          }
          else {
            if ((int)(local_c - local_8) < 0) {
              __assertfail(s_dtCnt_>__0_0051f9a6,s_XX_CPP_0051f9b1,0xee8);
            }
            uVar4 = 2;
            if (uVar2 != uVar3) {
              uVar4 = 1;
            }
          }
          if ((*(byte *)(local_1c + 5) & 4) == 0) {
            FUN_004a881e(local_20,local_1c,uVar4,local_c,1,param_4,param_3);
          }
          else {
            FUN_004a8ab8(local_20,local_1c,local_c,param_4,param_3);
          }
          if ((((uVar8 & 0x400) != 0) && ((*(byte *)(param_3 + 0x20) & 1) != 0)) &&
             (*(char *)(param_3 + 0x20) != -1)) {
            (**(code **)(*local_20 + -8))();
          }
        }
        if ((uVar8 & 3) == 3) {
          if ((uVar8 & 0x48) == 0x48) {
            local_24 = local_24 + -4;
          }
          if ((*(byte *)(local_1c + 5) & 4) == 0) {
            if (*(int *)(local_1c + 0x14) == 0) {
              free(local_24);
            }
            else {
              FUN_004a7826(local_24,*(undefined4 *)(local_1c + 0x14),
                           *(undefined2 *)(local_1c + 0x18));
            }
          }
          else {
            local_1c = *(int *)(local_1c + 8);
            if (*(int *)(local_1c + 0x1c) == 0) {
              FUN_004b0284(local_24);
            }
            else {
              FUN_004a7826(local_24,*(undefined4 *)(local_1c + 0x1c),
                           *(undefined2 *)(local_1c + 0x1a));
            }
          }
        }
        local_c = 0;
        bVar1 = param_1 < piVar5;
        piVar5 = piVar5 + -3;
      } while (bVar1);
      uVar4 = 0;
    }
    else {
      if (((*(byte *)(*param_1 + 4) & 2) == 0) || ((*(byte *)(*param_1 + 0xc) & 2) == 0)) {
        __assertfail(s_IS_CLASS_dttPtr_>dttType_>tpMask_0051f8c6,s_XX_CPP_0051f91d,0xe13);
      }
      uVar4 = *(undefined4 *)(*param_1 + 0x24);
    }
  }
  return uVar4;
}

