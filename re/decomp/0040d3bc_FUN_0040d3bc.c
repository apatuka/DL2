// FUN_0040d3bc @ 0040d3bc size=232 sig=undefined FUN_0040d3bc() cc=unknown
// callers: FUN_004059bc
// callees: FUN_0046bdfc,FUN_004054d8,FUN_004067d0,FUN_0044d034,FUN_00407d60

void FUN_0040d3bc(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  
  iVar1 = *(int *)(param_2 + 0x1c);
  if (iVar1 == -1) {
    *(undefined4 *)(param_2 + 0x10) = 1;
  }
  else {
    puVar3 = &DAT_005a43d0 + iVar1 * 0xadc;
    if (((puVar3 == (undefined *)0x0) || ((&DAT_005a4400)[iVar1 * 0x56e] == 0)) ||
       ((char)(&DAT_005a43f0)[iVar1 * 0xadc] != param_1)) {
      *(undefined4 *)(param_2 + 0x10) = 1;
    }
    else {
      iVar2 = FUN_0046bdfc(puVar3);
      if ((iVar2 < 100) && (DAT_0058f16c < 0x19)) {
        iVar2 = FUN_004067d0(param_1,puVar3,7,1,1,0);
        if (iVar2 == 0) {
          iVar2 = FUN_004067d0(param_1,puVar3,7,1,1,10000);
        }
        if (iVar2 == 0) {
          iVar2 = FUN_004054d8(7,puVar3);
          if ((iVar2 != 0) && (iVar2 = FUN_0044d034(puVar3,6), iVar2 < 2)) {
            *(undefined4 *)(param_2 + 0xc) = 1;
            FUN_00407d60(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),0x15,
                         iVar1,7,1);
            return;
          }
          *(undefined4 *)(param_2 + 0xc) = 1;
        }
      }
      else {
        *(undefined4 *)(param_2 + 0x10) = 1;
      }
    }
  }
  return;
}

