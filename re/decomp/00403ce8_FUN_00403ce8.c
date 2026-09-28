// FUN_00403ce8 @ 00403ce8 size=176 sig=undefined FUN_00403ce8() cc=unknown
// callers: FUN_00403d98
// callees: FUN_00475a60,FUN_00476cc0,FUN_0046ca40,FUN_00403ca4

void FUN_00403ce8(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  iVar1 = FUN_00403ca4(param_2,param_1);
  if ((iVar1 == 0) && (*(short *)(param_2 + 0x30) == 0)) {
    if ((*(int *)(param_2 + 0xa60) <= *(int *)(param_2 + 0xa0a)) &&
       (uVar2 = FUN_0046ca40(), (uVar2 & 1) != 0)) {
      return;
    }
    iVar1 = 0;
    piVar3 = (int *)(param_2 + 0x154);
    do {
      if ((*piVar3 != 0) && (*(char *)(*piVar3 + 5) != '\v')) {
        FUN_00475a60(param_2,iVar1,0);
      }
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 0xd;
    } while (iVar1 < 0x24);
    iVar1 = 1;
    piVar3 = (int *)(param_2 + 0x3e);
    do {
      if (*piVar3 != 0) {
        FUN_00476cc0(&DAT_0059f160 + param_1 * 0x2d8,iVar1,-*piVar3,(int)*(short *)(param_2 + 0x1a))
        ;
      }
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar1 < 0xb);
  }
  return;
}

