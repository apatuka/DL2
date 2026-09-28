// FUN_0042267c @ 0042267c size=35 sig=undefined FUN_0042267c() cc=unknown
// callers: FUN_00423960
// callees: 

undefined4 FUN_0042267c(void)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &DAT_00651cb4;
  while( true ) {
    if (DAT_0065209c <= iVar2) {
      return 0;
    }
    if (*piVar1 == 0x8f) break;
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 5;
  }
  return CONCAT31((int3)((uint)piVar1 >> 8),1);
}

