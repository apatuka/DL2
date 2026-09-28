// FUN_0040d990 @ 0040d990 size=67 sig=undefined FUN_0040d990() cc=unknown
// callers: FUN_0040c7a4
// callees: 

bool FUN_0040d990(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0x44);
  do {
    if ((*piVar2 != 0) && ((&DAT_004faf8d)[*(char *)(*piVar2 + 6) * 0x24] == '\x01')) {
      iVar3 = iVar3 + 1;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0x10);
  return 2 < iVar3;
}

