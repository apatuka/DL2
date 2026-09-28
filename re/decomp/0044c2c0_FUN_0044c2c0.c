// FUN_0044c2c0 @ 0044c2c0 size=94 sig=undefined FUN_0044c2c0() cc=unknown
// callers: FUN_00475ba4,NetReassignLabor
// callees: FUN_0044ba40,FUN_0044bddc,FUN_0044c284,FUN_0044ba18,FUN_0044c248

undefined4 FUN_0044c2c0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0044c248(param_2);
  if ((iVar1 == 0) && (iVar1 = FUN_0044c284(param_3), iVar1 == 0)) {
    iVar1 = FUN_0044ba18(param_3);
    iVar2 = FUN_0044ba40(param_3);
    if (iVar1 < iVar2) {
      iVar1 = FUN_0044bddc(param_2,0xffffffff);
      if ((iVar1 != 0) && (iVar1 = FUN_0044bddc(param_3,1), iVar1 != 0)) {
        return 1;
      }
      return 0;
    }
  }
  return 0;
}

