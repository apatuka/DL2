// FUN_00435e34 @ 00435e34 size=47 sig=undefined FUN_00435e34() cc=unknown
// callers: FUN_0044930c,FUN_00435ed0
// callees: CheckSubUnit,CheckSubRes,CheckSubInfo,CheckSubTech

undefined4 FUN_00435e34(void)

{
  undefined4 uVar1;
  
  if (DAT_00558d58 == 0) {
    uVar1 = CheckSubRes();
    return uVar1;
  }
  if (DAT_00558d58 == 1) {
    uVar1 = CheckSubInfo();
    return uVar1;
  }
  if (DAT_00558d58 == 2) {
    uVar1 = CheckSubTech();
    return uVar1;
  }
  if (DAT_00558d58 != 3) {
    return 0;
  }
  uVar1 = CheckSubUnit();
  return uVar1;
}

