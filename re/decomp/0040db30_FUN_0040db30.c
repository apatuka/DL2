// FUN_0040db30 @ 0040db30 size=66 sig=undefined FUN_0040db30() cc=unknown
// callers: FUN_0040dbc4
// callees: 

undefined4 FUN_0040db30(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = 0;
  piVar3 = (int *)(param_1 + 0x44);
  while (((iVar1 = *piVar3, iVar1 == 0 || ((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] != '\x01'))
         || (*(int *)(iVar1 + 0x48) == 0))) {
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
    if (0xf < iVar2) {
      return 0;
    }
  }
  return 1;
}

