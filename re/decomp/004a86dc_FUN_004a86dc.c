// FUN_004a86dc @ 004a86dc size=215 sig=undefined FUN_004a86dc() cc=unknown
// callers: FUN_004a881e
// callees: FUN_004a9090,FUN_004a76d2,__assertfail
// strings: \"XX.CPP\"|\"varType->tpClass.tpcFlags & CF_HAS_DTOR\"|\"varType->tpClass.tpcDtorAddr\"|\"(errPtr->ERRcInitDtc >= varType->tpClass.tpcDtorCount) || flags\"

void FUN_004a86dc(undefined4 param_1,int param_2,uint param_3,int param_4,int param_5)

{
  undefined4 *puVar1;
  int iVar2;
  undefined2 in_FS;
  undefined4 local_28;
  
  FUN_004a9090();
  if ((*(byte *)(param_2 + 0xc) & 2) == 0) {
    __assertfail(s_varType_>tpClass_tpcFlags___CF_H_0051f5ab,s_XX_CPP_0051f5d3,0xbb2);
  }
  if (*(int *)(param_2 + 0x28) == 0) {
    __assertfail(s_varType_>tpClass_tpcDtorAddr_0051f5da,s_XX_CPP_0051f5f7,0xbb3);
  }
  if ((*(uint *)(param_5 + 0x1c) < *(uint *)(param_2 + 0x20)) && (param_3 == 0)) {
    __assertfail(s__errPtr_>ERRcInitDtc_>__varType__0051f5fe,s_XX_CPP_0051f63e,0xbbe);
  }
  if ((param_3 & 2) == 0) {
    if (param_4 == 0) {
      iVar2 = *(int *)(param_2 + 0x24);
    }
    else {
      iVar2 = *(int *)(param_2 + 0x20);
    }
    *(int *)(param_5 + 0x1c) = *(int *)(param_5 + 0x1c) - iVar2;
  }
  FUN_004a76d2(param_1,param_2,param_3,*(undefined4 *)(param_2 + 0x28),
               *(undefined2 *)(param_2 + 0x2c),param_4);
  puVar1 = (undefined4 *)segment(in_FS,0);
  *puVar1 = local_28;
  return;
}

