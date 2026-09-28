// FUN_0044a2fc @ 0044a2fc size=43 sig=undefined FUN_0044a2fc() cc=unknown
// callers: @BackWndProc$qqspvuiuil
// callees: FUN_004442dc,FUN_0044a000

void FUN_0044a2fc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_004442dc(param_1,param_2,DAT_004d5c28);
  if (iVar1 != 0) {
    DAT_004d5974 = param_1;
    FUN_0044a000();
  }
  return;
}

