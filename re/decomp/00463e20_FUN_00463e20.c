// FUN_00463e20 @ 00463e20 size=103 sig=undefined FUN_00463e20() cc=unknown
// callers: 
// callees: FUN_0049b3c9,FUN_004935fc

void FUN_00463e20(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (DAT_0051bddc != 0) {
    iVar3 = 0;
    do {
      iVar2 = 0;
      do {
        uVar1 = FUN_0049b3c9(DAT_0058df44,iVar3 * 0x10 + iVar2);
        FUN_004935fc(param_1 + iVar2 * 4,iVar3 * 4 + param_2,param_1 + iVar2 * 4 + 4,
                     iVar3 * 4 + param_2 + 4,uVar1);
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x10);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x10);
  }
  return;
}

