// FUN_004a99f8 @ 004a99f8 size=122 sig=undefined FUN_004a99f8() cc=unknown
// callers: FUN_004a7df4
// callees: FUN_004a9956,__assertfail
// strings: \"Can't adjust class address (no base class entry found)\"|\"XXTYPE.CPP\"|\"!\\\"Can't adjust class address (no base class entry found)\\\"\"

int FUN_004a99f8(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = param_3;
  iVar3 = param_2;
  if (((param_1 != 0) &&
      (iVar2 = FUN_004a9956((uint)*(ushort *)(param_2 + 0x10) + param_2,0,param_3,&param_1),
      iVar2 == 0)) &&
     (iVar3 = FUN_004a9956((uint)*(ushort *)(iVar3 + 0x12) + iVar3,1,uVar1,&param_1), iVar3 == 0)) {
    __assertfail(s___Can_t_adjust_class_address__no_0051fc8b,s_XXTYPE_CPP_0051fcc5,0x4d3);
    param_1 = 0;
  }
  return param_1;
}

