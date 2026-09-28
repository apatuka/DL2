// FUN_00441868 @ 00441868 size=66 sig=undefined FUN_00441868() cc=unknown
// callers: 
// callees: FUN_00441388

undefined4 FUN_00441868(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    iVar1 = FUN_00441388(param_1,iVar2,0x10);
    if (iVar1 != 0) {
      return 0;
    }
    iVar1 = FUN_00441388(param_2,iVar2,0x10);
    if (iVar1 != 0) break;
    iVar2 = iVar2 + 1;
    if (6 < iVar2) {
      return 1;
    }
  }
  return 0;
}

