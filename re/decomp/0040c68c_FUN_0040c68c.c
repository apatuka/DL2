// FUN_0040c68c @ 0040c68c size=92 sig=undefined FUN_0040c68c() cc=unknown
// callers: FUN_00409544,FUN_004096a8,FUN_0040a898,FUN_00403f5c,FUN_0040a524,FUN_0040f540,FUN_0040effc,FUN_0040f2e0,FUN_0040f974,FUN_0040a710
// callees: 

undefined * FUN_0040c68c(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(&DAT_00522584 + param_1 * 0x2648);
  while ((param_2 != *piVar1 || (param_3 != piVar1[4]))) {
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 0x31;
    if (0x31 < iVar2) {
      return (undefined *)0x0;
    }
  }
  return &DAT_00522584 + param_1 * 0x2648 + iVar2 * 0xc4;
}

