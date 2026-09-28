// FUN_00450340 @ 00450340 size=62 sig=undefined FUN_00450340() cc=unknown
// callers: FUN_00486e34,FUN_00450380
// callees: FUN_00450320

undefined4 FUN_00450340(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = FUN_00450320();
  if (iVar1 == 0) {
    return 0;
  }
  iVar2 = 0;
  iVar1 = 0;
  piVar3 = &DAT_0065e3cc;
  do {
    if (iVar1 != DAT_0058f1f4) {
      iVar2 = iVar2 + *piVar3;
    }
    iVar1 = iVar1 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar1 < 7);
  if ((iVar2 == 0) && (DAT_0065e420 == 0)) {
    return 1;
  }
  return 0;
}

