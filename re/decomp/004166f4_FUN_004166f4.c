// FUN_004166f4 @ 004166f4 size=83 sig=undefined FUN_004166f4() cc=unknown
// callers: FUN_00473324
// callees: FUN_00416518,FUN_00416630,FUN_004748dc,FUN_0041665c,FUN_00416578

int FUN_004166f4(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  if ((DAT_004d5aa0 != '\0') && (iVar1 = FUN_004748dc(), iVar1 != 0)) {
    return 6;
  }
  iVar1 = FUN_00416578(param_1,param_2);
  if (iVar1 == 0) {
    iVar1 = 6;
  }
  else {
    FUN_00416518();
    do {
      iVar1 = FUN_0041665c();
    } while (iVar1 == 0);
    FUN_00416630();
  }
  return iVar1;
}

