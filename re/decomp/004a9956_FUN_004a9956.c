// FUN_004a9956 @ 004a9956 size=162 sig=undefined FUN_004a9956() cc=unknown
// callers: FUN_004a99f8,FUN_004a9956
// callees: FUN_004a9103,FUN_004a9956,__assertfail
// strings: \"XXTYPE.CPP\"

undefined4 FUN_004a9956(int *param_1,int param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int *local_8;
  
  if (*param_4 == 0) {
    __assertfail(&DAT_0051fc44,s_XXTYPE_CPP_0051fc49,0x46a);
  }
  while( true ) {
    iVar2 = *param_1;
    if (iVar2 == 0) {
      return 0;
    }
    local_8 = (int *)(*param_4 + param_1[1]);
    if (param_2 != 0) {
      local_8 = (int *)*local_8;
    }
    iVar1 = FUN_004a9103(iVar2,param_3);
    if (iVar1 != 0) break;
    if ((((*(byte *)(iVar2 + 4) & 2) != 0) &&
        (iVar2 = (uint)*(ushort *)(iVar2 + 0x10) + iVar2, iVar2 != 0)) &&
       (iVar2 = FUN_004a9956(iVar2,0,param_3,&local_8), iVar2 != 0)) {
      *param_4 = (int)local_8;
      return 1;
    }
    param_1 = param_1 + 3;
  }
  *param_4 = (int)local_8;
  return 1;
}

