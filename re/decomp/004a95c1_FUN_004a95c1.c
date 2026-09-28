// FUN_004a95c1 @ 004a95c1 size=613 sig=undefined FUN_004a95c1() cc=unknown
// callers: FUN_004a95c1,FUN_004a9828
// callees: FUN_004a95c1,FUN_004a9103,__assertfail
// strings: \"XXTYPE.CPP\"|\"topTypPtr != 0 && IS_STRUC(topTypPtr->tpMask)\"|\"tgtTypPtr != 0 && IS_STRUC(tgtTypPtr->tpMask)\"|\"srcTypPtr == 0 || IS_STRUC(srcTypPtr->tpMask)\"|\"__isSameTypeID(srcTypPtr, tgtTypPtr) == 0\"|\"tgtTypPtr != 0 && __isSameTypeID(topTypPtr, tgtTypPtr) == 0\"|\"srcTypPtr\"

undefined4 *
FUN_004a95c1(int param_1,int param_2,undefined4 *param_3,int param_4,int param_5,int param_6,
            uint *param_7,int param_8,int param_9)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int local_1c;
  uint local_18;
  int local_14;
  undefined4 *local_10;
  uint local_c;
  
  local_c = 0;
  local_10 = (undefined4 *)0x0;
  local_14 = 0;
  if ((param_2 == 0) || ((*(byte *)(param_2 + 4) & 1) == 0)) {
    __assertfail(s_topTypPtr____0____IS_STRUC_topTy_0051fad6,s_XXTYPE_CPP_0051fb04,0x2a7);
  }
  if ((param_4 == 0) || ((*(byte *)(param_4 + 4) & 1) == 0)) {
    __assertfail(s_tgtTypPtr____0____IS_STRUC_tgtTy_0051fb0f,s_XXTYPE_CPP_0051fb3d,0x2a8);
  }
  if ((param_6 != 0) && ((*(byte *)(param_6 + 4) & 1) == 0)) {
    __assertfail(s_srcTypPtr____0____IS_STRUC_srcTy_0051fb48,s_XXTYPE_CPP_0051fb76,0x2a9);
  }
  if (param_6 != 0) {
    iVar2 = FUN_004a9103(param_6,param_4);
    if (iVar2 != 0) {
      __assertfail(s___isSameTypeID_srcTypPtr__tgtTyp_0051fb81,s_XXTYPE_CPP_0051fbab,0x2ad);
    }
    iVar2 = FUN_004a9103(param_6,param_2);
    if (iVar2 != 0) {
      return (undefined4 *)0x0;
    }
  }
  if ((param_4 == 0) || (iVar2 = FUN_004a9103(param_2,param_4), iVar2 != 0)) {
    __assertfail(s_tgtTypPtr____0______isSameTypeID_0051fbb6,s_XXTYPE_CPP_0051fbf2,0x2b3);
  }
  if ((*(byte *)(param_2 + 0xc) & 4) == 0) {
    return (undefined4 *)0x0;
  }
  bVar1 = false;
  piVar4 = (int *)((uint)*(ushort *)(param_2 + 0x12) + param_2);
  do {
    while (iVar2 = *piVar4, iVar2 == 0) {
      if (bVar1) {
        *param_7 = local_c;
        if (local_14 == 1) {
          return local_10;
        }
        return (undefined4 *)0x0;
      }
      bVar1 = true;
      piVar4 = (int *)((uint)*(ushort *)(param_2 + 0x10) + param_2);
    }
    if ((*(byte *)(piVar4 + 2) & 8) == 0) {
      if ((param_8 == 0) || ((piVar4[2] & 3U) != 3)) {
        local_18 = 0;
      }
      else {
        local_18 = 1;
      }
      puVar5 = (undefined4 *)(param_1 + piVar4[1]);
      local_1c = param_9;
      if ((*(byte *)(piVar4 + 2) & 4) != 0) {
        puVar5 = (undefined4 *)*puVar5;
        local_1c = iVar2;
      }
      iVar3 = FUN_004a9103(param_4,iVar2);
      if (iVar3 == 0) {
        if (((*(byte *)(iVar2 + 0xc) & 4) != 0) &&
           (puVar5 = (undefined4 *)
                     FUN_004a95c1(puVar5,iVar2,param_3,param_4,param_5,param_6,param_7,local_18,
                                  local_1c), puVar5 != (undefined4 *)0x0)) {
          local_18 = *param_7;
          goto LAB_004a97cc;
        }
      }
      else if (param_3 == (undefined4 *)0x0) {
        if (param_5 != 0) {
          if (param_6 == 0) {
            __assertfail(s_srcTypPtr_0051fbfd,s_XXTYPE_CPP_0051fc07,0x328);
          }
          iVar2 = FUN_004a95c1(puVar5,iVar2,param_5,param_6,0,0,param_7,0,0);
          if (iVar2 == 0) goto LAB_004a97eb;
        }
LAB_004a97cc:
        if ((local_14 == 0) || (puVar5 != local_10)) {
          local_14 = local_14 + 1;
          local_c = local_18;
          local_10 = puVar5;
        }
        else {
          local_c = local_c | local_18;
        }
      }
      else if (puVar5 == param_3) {
        return puVar5;
      }
    }
LAB_004a97eb:
    piVar4 = piVar4 + 3;
  } while( true );
}

