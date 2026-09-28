// FUN_00411a68 @ 00411a68 size=72 sig=undefined FUN_00411a68() cc=unknown
// callers: FUN_00411d28,FUN_00411c64,FUN_00411adc
// callees: FUN_004a6b98,GetTickCount

undefined4 FUN_00411a68(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  DWORD DVar3;
  
  iVar1 = *(int *)(param_1 + 4);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    iVar2 = FUN_004a6b98(iVar1,param_2,9);
    if (iVar2 == 0) break;
    iVar1 = *(int *)(iVar1 + 0x1a);
  }
  DVar3 = GetTickCount();
  *(DWORD *)(iVar1 + 0x12) = DVar3;
  *param_3 = *(undefined4 *)(iVar1 + 0xe);
  return *(undefined4 *)(iVar1 + 10);
}

