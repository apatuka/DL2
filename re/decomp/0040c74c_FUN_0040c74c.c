// FUN_0040c74c @ 0040c74c size=85 sig=undefined FUN_0040c74c() cc=unknown
// callers: FUN_00409b58,FUN_0040a898,FUN_0040aaa4
// callees: 

undefined * FUN_0040c74c(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(&DAT_00522584 + param_1 * 0x2648);
  do {
    if (param_2 == *piVar2) {
      return &DAT_00522584 + param_1 * 0x2648 + iVar1 * 0xc4;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 0x31;
  } while (iVar1 < 0x32);
  return (undefined *)0x0;
}

