// FUN_00421154 @ 00421154 size=33 sig=undefined FUN_00421154() cc=unknown
// callers: FUN_00421178,FUN_00421734
// callees: 

int FUN_00421154(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = &DAT_004b7a20;
  do {
    if (param_1 == *piVar2) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0x18);
  return -1;
}

