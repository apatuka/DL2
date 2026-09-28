// FUN_00452558 @ 00452558 size=60 sig=undefined FUN_00452558() cc=unknown
// callers: FUN_004526b0
// callees: FUN_00450f84

undefined4 FUN_00452558(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(DAT_0057cdf8 + 0x74);
  while( true ) {
    if (iVar1 == 0) {
      return 1;
    }
    if (((ushort)*(byte *)(iVar1 + 0x1e) != *(ushort *)(DAT_0057cdf8 + 8)) &&
       (iVar2 = FUN_00450f84(iVar1), iVar2 == 0)) break;
    iVar1 = *(int *)(iVar1 + 0x44);
  }
  return 0;
}

