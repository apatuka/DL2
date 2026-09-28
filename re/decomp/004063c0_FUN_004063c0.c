// FUN_004063c0 @ 004063c0 size=100 sig=undefined FUN_004063c0() cc=unknown
// callers: FUN_00403a10,FUN_00406538,FUN_00406424
// callees: FUN_0044c754

int FUN_004063c0(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = param_3;
  while (((iVar1 = *piVar3, *(short *)(iVar1 + 0x30) < 0x12d ||
          (((399 < *(short *)(param_2 + 0x30) && ((int)(&DAT_0059f16c)[param_1 * 0xb6] < 0x191)) ||
           ((*(byte *)(iVar1 + 0x1c) & 0x20) != 0)))) || (iVar2 = FUN_0044c754(iVar1), iVar2 < 1)))
  {
    piVar3 = (int *)piVar3[1];
    if (param_3 == piVar3) {
      return 0;
    }
  }
  return iVar1;
}

