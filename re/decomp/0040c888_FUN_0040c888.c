// FUN_0040c888 @ 0040c888 size=62 sig=undefined FUN_0040c888() cc=unknown
// callers: 
// callees: 

int FUN_0040c888(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  piVar1 = (int *)(&DAT_00522584 + param_1 * 0x2648);
  do {
    if (param_2 == *piVar1) {
      iVar2 = iVar2 + 1;
    }
    iVar3 = iVar3 + 1;
    piVar1 = piVar1 + 0x31;
  } while (iVar3 < 0x32);
  return iVar2;
}

