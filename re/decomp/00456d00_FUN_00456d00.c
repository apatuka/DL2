// FUN_00456d00 @ 00456d00 size=110 sig=undefined FUN_00456d00() cc=unknown
// callers: FUN_00423a80,FUN_0048192c,FUN_00481da0,FUN_00421efc
// callees: 

int FUN_00456d00(int param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 0;
  piVar1 = &DAT_0057bd3c;
  while( true ) {
    if (DAT_005649cc <= uVar2) {
      return 0;
    }
    if ((param_1 == *(short *)(*piVar1 + 0x1a)) &&
       (((param_2 == (short)piVar1[1] || (param_2 == *(short *)((int)piVar1 + 6))) ||
        ((1 << ((byte)param_2 & 0x1f) & (uint)*(byte *)(piVar1 + 2)) != 0)))) break;
    uVar2 = uVar2 + 1;
    piVar1 = (int *)((int)piVar1 + 0x86);
  }
  return (int)&DAT_0057bd38 + uVar2 * 0x86;
}

