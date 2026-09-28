// FUN_0040daf4 @ 0040daf4 size=57 sig=undefined FUN_0040daf4() cc=unknown
// callers: FUN_0040dbc4
// callees: 

undefined4 FUN_0040daf4(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0x44);
  while ((*piVar2 == 0 || ((&DAT_004faf8d)[*(char *)(*piVar2 + 6) * 0x24] != '\x01'))) {
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
    if (0xf < iVar1) {
      return 0;
    }
  }
  return 1;
}

