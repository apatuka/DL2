// FUN_0047d2f0 @ 0047d2f0 size=108 sig=undefined FUN_0047d2f0() cc=unknown
// callers: 
// callees: FUN_0047cb04,FUN_0046e338,FUN_00423690

void FUN_0047d2f0(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 8) == 0) {
    if ((DAT_004d5b24 & 1) == 0) {
      *(undefined4 *)(param_1 + 8) = 2;
    }
    else {
      FUN_0047cb04(param_1);
    }
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  if (*(int *)(param_1 + 8) < 1) {
    DAT_004d5b24 = DAT_004d5b24 & 0xfffffffe;
    FUN_0046e338();
    FUN_0047cb04(param_1);
  }
  else {
    DAT_004d5b24 = DAT_004d5b24 | 1;
    FUN_0046e338();
    iVar1 = 0;
    do {
      FUN_00423690(iVar1,100,0,0,0,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 7);
  }
  return;
}

