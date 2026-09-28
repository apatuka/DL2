// FUN_00469250 @ 00469250 size=43 sig=undefined FUN_00469250() cc=unknown
// callers: @IntroWndProc$qqspvuiuil
// callees: FUN_004691f8,FUN_004442dc

void FUN_00469250(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_004442dc(param_1,param_2,DAT_004d5c28);
  if (iVar1 != 0) {
    DAT_004d5978 = param_1;
    FUN_004691f8();
  }
  return;
}

