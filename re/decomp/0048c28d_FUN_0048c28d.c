// FUN_0048c28d @ 0048c28d size=56 sig=undefined FUN_0048c28d() cc=unknown
// callers: FUN_00494346,FUN_004590f0,FUN_00425f58,FUN_004942d0,FUN_004811c8,InitCYGame,FUN_00459230,FUN_00411808,FUN_0048d205,FUN_004a52db,FUN_00463bcc
// callees: FUN_00498ba9,FUN_0048bf93,FUN_004989cf

int FUN_0048c28d(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00498ba9(0xb0);
  if (iVar1 != 0) {
    iVar2 = FUN_0048bf93(iVar1,param_1,param_2,param_3);
    if (iVar2 != 0) {
      return iVar1;
    }
    FUN_004989cf(iVar1);
  }
  return 0;
}

