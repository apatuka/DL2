// FUN_0040d5c0 @ 0040d5c0 size=84 sig=undefined FUN_0040d5c0() cc=unknown
// callers: FUN_0040d808
// callees: FUN_00445b94

undefined4 FUN_0040d5c0(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 1;
  piVar2 = (int *)(param_2 + 0x48);
  while (((iVar1 = *piVar2, iVar1 == 0 || ((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] != '\x01'))
         || (iVar1 = FUN_00445b94(param_1,(int)*(char *)(iVar1 + 6)), iVar1 != 0))) {
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
    if (0xf < iVar3) {
      return 1;
    }
  }
  return 0;
}

