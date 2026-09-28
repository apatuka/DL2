// FUN_004a91de @ 004a91de size=343 sig=undefined FUN_004a91de() cc=unknown
// callers: FUN_004a91de,FUN_004a9335
// callees: FUN_004a9103,FUN_004a91de,__assertfail
// strings: \"XXTYPE.CPP\"|\"IS_STRUC(base->tpMask)\"|\"IS_STRUC(derv->tpMask)\"|\"derv->tpClass.tpcFlags & CF_HAS_BASES\"

undefined4 FUN_004a91de(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  if ((*(byte *)(param_2 + 4) & 1) == 0) {
    __assertfail(s_IS_STRUC_base_>tpMask__0051fa2f,s_XXTYPE_CPP_0051fa46,0x13a);
  }
  if ((*(byte *)(param_1 + 4) & 1) == 0) {
    __assertfail(s_IS_STRUC_derv_>tpMask__0051fa51,s_XXTYPE_CPP_0051fa68,0x13b);
  }
  if ((*(byte *)(param_1 + 0xc) & 4) == 0) {
    __assertfail(s_derv_>tpClass_tpcFlags___CF_HAS__0051fa73,s_XXTYPE_CPP_0051fa99,0x13d);
  }
  piVar4 = (int *)((uint)*(ushort *)(param_1 + 0x12) + param_1);
  do {
    iVar2 = *piVar4;
    if (iVar2 == 0) {
      piVar4 = (int *)((uint)*(ushort *)(param_1 + 0x10) + param_1);
      while( true ) {
        iVar2 = *piVar4;
        if (iVar2 == 0) {
          return 0;
        }
        if ((param_4 == 0) || ((piVar4[2] & 3U) != 3)) {
          iVar3 = 0;
        }
        else {
          iVar3 = 1;
        }
        iVar1 = FUN_004a9103(param_2,iVar2);
        if ((iVar1 != 0) && (iVar3 != 0)) break;
        if (((*(byte *)(iVar2 + 0xc) & 4) != 0) &&
           (iVar2 = FUN_004a91de(iVar2,param_2,param_3,iVar3), iVar2 != 0)) {
          return 1;
        }
        piVar4 = piVar4 + 3;
      }
      return 1;
    }
    if ((*(byte *)(piVar4 + 2) & 8) == 0) {
      if ((param_4 == 0) || ((piVar4[2] & 3U) != 3)) {
        iVar3 = 0;
      }
      else {
        iVar3 = 1;
      }
      iVar1 = FUN_004a9103(param_2,iVar2);
      if ((iVar1 != 0) && (iVar3 != 0)) {
        return 1;
      }
      if (((*(byte *)(iVar2 + 0xc) & 4) != 0) &&
         (iVar2 = FUN_004a91de(iVar2,param_2,param_3,iVar3), iVar2 != 0)) {
        return 1;
      }
    }
    piVar4 = piVar4 + 3;
  } while( true );
}

