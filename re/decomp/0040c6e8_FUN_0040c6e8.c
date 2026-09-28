// FUN_0040c6e8 @ 0040c6e8 size=97 sig=undefined FUN_0040c6e8() cc=unknown
// callers: FUN_0040a710
// callees: 

undefined * FUN_0040c6e8(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(&DAT_00522584 + param_1 * 0x2648);
  while ((param_2 != *piVar1 || (param_3 != (short)piVar1[2]))) {
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 0x31;
    if (0x31 < iVar2) {
      return (undefined *)0x0;
    }
  }
  return &DAT_00522584 + param_1 * 0x2648 + iVar2 * 0xc4;
}

