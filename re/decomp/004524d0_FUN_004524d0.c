// FUN_004524d0 @ 004524d0 size=66 sig=undefined FUN_004524d0() cc=unknown
// callers: FUN_004526b0
// callees: FUN_00450f60

undefined4 FUN_004524d0(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = 0;
  iVar1 = *(int *)(DAT_0057cdf8 + 0x74);
  do {
    if (iVar1 == 0) {
      return uVar2;
    }
    if (param_1 == *(byte *)(iVar1 + 0x1e)) {
      iVar3 = FUN_00450f60(iVar1);
      if (iVar3 == 0) {
        return 0;
      }
      uVar2 = 1;
    }
    iVar1 = *(int *)(iVar1 + 0x44);
  } while( true );
}

