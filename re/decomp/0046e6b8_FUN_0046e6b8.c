// FUN_0046e6b8 @ 0046e6b8 size=119 sig=undefined FUN_0046e6b8() cc=unknown
// callers: FUN_0046e730,FUN_00419924,FUN_0045b304,FUN_0041482c,FUN_0045b094,FUN_004471c0
// callees: ReLinkArmy,FUN_0046e56c,FUN_00446bf0

void FUN_0046e6b8(int param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  
  bVar2 = false;
  iVar1 = *(int *)(param_1 + 0x76);
  do {
    if (iVar1 == 0) {
LAB_0046e6f6:
      if ((*(short *)(param_1 + 0x30) == 0) && (!bVar2)) {
        iVar1 = *(int *)(param_1 + 0x76);
        while (iVar1 != 0) {
          iVar3 = *(int *)(iVar1 + 0x54);
          ReLinkArmy(iVar1,param_1,param_1 + 0x76,param_1 + 0x7a);
          iVar1 = iVar3;
        }
        FUN_0046e56c(param_1,0xffffffff);
      }
      return;
    }
    iVar3 = FUN_00446bf0(iVar1);
    if ((iVar3 == 0) && ((&DAT_004faf87)[*(char *)(iVar1 + 6) * 0x24] != '\t')) {
      bVar2 = true;
      goto LAB_0046e6f6;
    }
    iVar1 = *(int *)(iVar1 + 0x54);
  } while( true );
}

