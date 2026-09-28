// FUN_00453bf4 @ 00453bf4 size=59 sig=undefined FUN_00453bf4() cc=unknown
// callers: FUN_00453c30
// callees: FUN_004482cc

undefined4 FUN_00453bf4(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(DAT_0057cdf8 + 0x74);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if ((param_1 == *(int *)(iVar1 + 0x40)) && (iVar2 = FUN_004482cc(iVar1), iVar2 != 0)) break;
    iVar1 = *(int *)(iVar1 + 0x44);
  }
  return 1;
}

