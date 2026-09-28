// FUN_004a881e @ 004a881e size=666 sig=undefined FUN_004a881e() cc=unknown
// callers: FUN_004a8c58,FUN_004a881e,FUN_004a87d3,FUN_004a8ab8
// callees: FUN_004a881e,FUN_004a87d3,FUN_004a8ab8,FUN_004a86dc,__assertfail
// strings: \"XX.CPP\"|\"varType->tpClass.tpcFlags & CF_HAS_DTOR\"|\"dtorCnt < varCount\"|\"IS_STRUC(blType->tpMask)\"|\"memType\"|\"memType->tpClass.tpcFlags & CF_HAS_DTOR\"

void FUN_004a881e(int param_1,int param_2,undefined4 param_3,uint param_4,int param_5,
                 undefined4 param_6,undefined4 param_7)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  uint local_1c;
  int *local_14;
  int *local_c;
  
  if ((*(byte *)(param_2 + 0xc) & 2) == 0) {
    __assertfail(s_varType_>tpClass_tpcFlags___CF_H_0051f645,s_XX_CPP_0051f66d,0xc49);
  }
  if (param_5 == 0) {
    uVar2 = *(uint *)(param_2 + 0x24);
  }
  else {
    uVar2 = *(uint *)(param_2 + 0x20);
  }
  if ((param_4 == 0) || (uVar2 <= param_4)) {
    FUN_004a86dc(param_1,param_2,param_3,param_5,param_7);
  }
  else {
    if (uVar2 <= param_4) {
      __assertfail(s_dtorCnt_<_varCount_0051f674,s_XX_CPP_0051f687,0xc89);
    }
    piVar3 = (int *)((uint)*(ushort *)(param_2 + 0x12) + param_2);
    local_14 = piVar3;
    if (param_5 != 0) {
      for (; iVar4 = *local_14, iVar4 != 0; local_14 = local_14 + 3) {
        if ((*(byte *)(iVar4 + 4) & 1) == 0) {
          __assertfail(s_IS_STRUC_blType_>tpMask__0051f68e,s_XX_CPP_0051f6a7,0xcb4);
        }
        if ((*(byte *)(iVar4 + 0xc) & 2) != 0) {
          if (param_4 <= *(uint *)(iVar4 + 0x24)) {
            FUN_004a87d3(param_1,param_3,local_14 + 3,piVar3,param_4,1,param_6,param_7);
            return;
          }
          param_4 = param_4 - *(uint *)(iVar4 + 0x24);
        }
      }
    }
    piVar1 = (int *)((uint)*(ushort *)(param_2 + 0x10) + param_2);
    for (local_c = piVar1; iVar4 = *local_c, iVar4 != 0; local_c = local_c + 3) {
      if ((*(byte *)(iVar4 + 4) & 1) == 0) {
        __assertfail(s_IS_STRUC_blType_>tpMask__0051f6ae,s_XX_CPP_0051f6c7,0xcdb);
      }
      if ((*(byte *)(iVar4 + 0xc) & 2) != 0) {
        if (param_4 <= *(uint *)(iVar4 + 0x24)) {
          FUN_004a87d3(param_1,param_3,local_c + 3,piVar1,param_4,0,param_6,param_7);
          if (param_5 == 0) {
            return;
          }
          FUN_004a87d3(param_1,param_3,local_14,piVar3,0,1,param_6,param_7);
          return;
        }
        param_4 = param_4 - *(uint *)(iVar4 + 0x24);
      }
    }
    piVar5 = (int *)((uint)*(ushort *)(param_2 + 0x2e) + param_2);
    piVar6 = piVar5;
    while( true ) {
      iVar4 = *piVar6;
      if (iVar4 == 0) {
        __assertfail(s_memType_0051f6ce,s_XX_CPP_0051f6d6,0xd01);
      }
      local_1c = 1;
      if ((*(byte *)(iVar4 + 5) & 4) != 0) {
        local_1c = *(uint *)(iVar4 + 0xc);
        iVar4 = *(int *)(iVar4 + 8);
      }
      if ((*(byte *)(iVar4 + 0xc) & 2) == 0) {
        __assertfail(s_memType_>tpClass_tpcFlags___CF_H_0051f6dd,s_XX_CPP_0051f705,0xd0f);
      }
      uVar2 = local_1c * *(int *)(iVar4 + 0x20);
      if (param_4 <= uVar2) break;
      param_4 = param_4 - uVar2;
      piVar6 = piVar6 + 2;
    }
    do {
      if (local_1c < 2) {
        FUN_004a881e(piVar6[1] + param_1,*piVar6,0,param_4,1,param_6,param_7);
      }
      else {
        FUN_004a8ab8(piVar6[1] + param_1,*piVar6,param_4,param_6,param_7);
      }
      param_4 = 0;
      piVar6 = piVar6 + -2;
    } while (piVar5 <= piVar6);
    FUN_004a87d3(param_1,param_3,local_c,piVar1,0,0,param_6,param_7);
    if (param_5 != 0) {
      FUN_004a87d3(param_1,param_3,local_14,piVar3,0,1,param_6,param_7);
    }
  }
  return;
}

