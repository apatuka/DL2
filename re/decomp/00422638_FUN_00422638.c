// FUN_00422638 @ 00422638 size=65 sig=undefined FUN_00422638() cc=unknown
// callers: FUN_00423960,FUN_004226a0
// callees: FUN_00483cbc

undefined4 FUN_00422638(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  piVar2 = &DAT_00651cb4;
  do {
    if (DAT_0065209c <= iVar3) {
      return 0;
    }
    if ((*piVar2 == 0x37) || (*piVar2 == 0x39)) {
      iVar1 = FUN_00483cbc(PTR_DAT_004d5988,0);
      if (iVar1 != 0) {
        return 1;
      }
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 5;
  } while( true );
}

