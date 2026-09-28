// FUN_004a8ab8 @ 004a8ab8 size=292 sig=undefined FUN_004a8ab8() cc=unknown
// callers: FUN_004a8c58,FUN_004a881e
// callees: FUN_004a881e,__assertfail
// strings: \"XX.CPP\"|\"varType->tpMask & TM_IS_ARRAY\"|\"varType->tpArr.tpaElemType->tpClass.tpcFlags & CF_HAS_DTOR\"|\"vdtCount\"|\"etdCount <= elemCount || elemCount == 0\"|\"dtrCount <= vdtCount\"

void FUN_004a8ab8(int param_1,int param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  uint local_c;
  
  if ((*(byte *)(param_2 + 5) & 4) == 0) {
    __assertfail(s_varType_>tpMask___TM_IS_ARRAY_0051f70c,s_XX_CPP_0051f72a,0xd5e);
  }
  if ((*(byte *)(*(int *)(param_2 + 8) + 0xc) & 2) == 0) {
    __assertfail(s_varType_>tpArr_tpaElemType_>tpCl_0051f731,s_XX_CPP_0051f76c,0xd5f);
  }
  uVar1 = *(uint *)(param_2 + 0xc);
  piVar2 = *(int **)(param_2 + 8);
  uVar3 = piVar2[8];
  if (uVar3 == 0) {
    __assertfail(s_vdtCount_0051f773,s_XX_CPP_0051f77c,0xd68);
  }
  if (param_3 == 0) {
    param_3 = uVar3 * uVar1;
  }
  local_c = param_3 / uVar3;
  if ((uVar1 < local_c) && (uVar1 != 0)) {
    __assertfail(s_etdCount_<__elemCount____elemCou_0051f783,s_XX_CPP_0051f7ab,0xd71);
  }
  param_3 = param_3 - local_c * uVar3;
  if (uVar3 < param_3) {
    __assertfail(s_dtrCount_<__vdtCount_0051f7b2,s_XX_CPP_0051f7c7,0xd72);
  }
  param_1 = param_1 + local_c * *piVar2;
  if (param_3 != 0) {
    FUN_004a881e(param_1,piVar2,0,param_3,1,param_4,param_5);
  }
  while (local_c != 0) {
    param_1 = param_1 - *piVar2;
    FUN_004a881e(param_1,piVar2,0,uVar3,1,param_4,param_5);
    local_c = local_c - 1;
  }
  return;
}

