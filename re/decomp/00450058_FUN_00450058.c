// FUN_00450058 @ 00450058 size=60 sig=undefined FUN_00450058() cc=unknown
// callers: FUN_00486d30
// callees: FUN_0044fe1c,FUN_00450000,FUN_0044febc

undefined4 FUN_00450058(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0044fe1c(1);
  if (((iVar1 != 0) && (iVar1 = FUN_00450000(1,param_1), iVar1 != 0)) &&
     (iVar1 = FUN_0044febc(1), iVar1 == 0)) {
    return 0;
  }
  return 1;
}

