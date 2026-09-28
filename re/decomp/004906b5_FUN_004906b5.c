// FUN_004906b5 @ 004906b5 size=46 sig=undefined FUN_004906b5() cc=unknown
// callers: FUN_00490ce4
// callees: FUN_00488a09,FUN_00490603

undefined4 FUN_004906b5(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_00490603(param_1);
  if ((iVar1 != 0) && (*(int *)(iVar1 + 6) != -1)) {
    FUN_00488a09(*(undefined4 *)(iVar1 + 6));
    *(undefined4 *)(iVar1 + 6) = 0xffffffff;
  }
  return 0;
}

