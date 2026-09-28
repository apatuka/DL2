// FUN_0043a568 @ 0043a568 size=78 sig=undefined FUN_0043a568() cc=unknown
// callers: FUN_0043cd98
// callees: FUN_0043a33c,CheckTechDet,FUN_0043a394,FUN_0043a348

/* WARNING: Removing unreachable block (ram,0x0043a5ad) */

undefined4 FUN_0043a568(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0043a394(param_1,param_2,param_3,param_4);
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    FUN_0043a348();
    FUN_0043a33c();
    do {
      iVar1 = CheckTechDet();
    } while (iVar1 != 5);
    uVar2 = 1;
  }
  return uVar2;
}

