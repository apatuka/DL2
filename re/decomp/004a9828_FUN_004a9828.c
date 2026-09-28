// FUN_004a9828 @ 004a9828 size=232 sig=undefined FUN_004a9828() cc=unknown
// callers: 
// callees: FUN_004a95c1,FUN_004a9103,FUN_004a7b5d,__assertfail
// strings: \"XXTYPE.CPP\"|\"((unsigned __far *)vtablePtr)[-1] == 0\"

int FUN_004a9828(int param_1,int param_2,undefined4 param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int local_c;
  undefined4 local_8;
  
  local_8 = param_3;
  if (param_1 != 0) {
    iVar3 = param_1 - *(int *)(param_2 + -8);
    param_2 = param_2 - *(int *)(param_2 + -4);
    if (*(int *)(param_2 + -4) != 0) {
      __assertfail(s___unsigned___far___vtablePtr___1_0051fc12,s_XXTYPE_CPP_0051fc39,0x3a3);
    }
    uVar1 = *(undefined4 *)(param_2 + -0xc);
    if (param_4 == 0) {
      return iVar3;
    }
    iVar2 = FUN_004a9103(param_4,uVar1);
    if (iVar2 != 0) {
      return iVar3;
    }
    iVar2 = FUN_004a9103(local_8,uVar1);
    if ((iVar2 == 0) &&
       (iVar2 = FUN_004a95c1(iVar3,uVar1,0,param_4,param_1,local_8,&local_c,1,0), iVar2 != 0)) {
      return iVar2;
    }
    iVar3 = FUN_004a95c1(iVar3,uVar1,0,param_4,0,0,&local_c,1,0);
    if ((iVar3 != 0) && (local_c != 0)) {
      return iVar3;
    }
  }
  if (param_5 != 0) {
    FUN_004a7b5d(&DAT_004a9aa5,&DAT_0069f3b5,0,0,0,0,0,0,0);
  }
  return 0;
}

