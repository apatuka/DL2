// FUN_0040d9d4 @ 0040d9d4 size=100 sig=undefined FUN_0040d9d4() cc=unknown
// callers: FUN_0040dbc4
// callees: FUN_004726cc

undefined4 FUN_0040d9d4(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  piVar2 = (int *)(param_1 + 0x44);
  while (((iVar1 = *piVar2, iVar1 == 0 || ((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] != '\x01'))
         || ((*(char *)(*(int *)(iVar1 + 0x3c) + 0x22) == *(char *)(*(int *)(param_1 + 0x10) + 0x22)
             && (iVar1 = FUN_004726cc(*(undefined4 *)(iVar1 + 0x3c),*(undefined4 *)(param_1 + 0x10),
                                      (int)*(short *)(param_1 + 10)), iVar1 < 2))))) {
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
    if (0xf < iVar3) {
      return 1;
    }
  }
  return 0;
}

