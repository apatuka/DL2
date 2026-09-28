// FUN_00458138 @ 00458138 size=109 sig=undefined FUN_00458138() cc=unknown
// callers: FUN_00426868,FUN_00468214,FUN_00468a28
// callees: FUN_00457dbc,CGNetService_GetType

uint FUN_00458138(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (DAT_004d1718 == 0) {
    iVar1 = FUN_00457dbc();
    if (iVar1 == 0) {
      return 0;
    }
    DAT_004d1718 = 1;
  }
  for (iVar1 = 0; iVar1 < DAT_00583b70; iVar1 = iVar1 + 1) {
    iVar2 = CGNetService_GetType(*(undefined4 *)(DAT_00583b6c + iVar1 * 4));
    if (iVar2 == 3) {
      uVar3 = uVar3 | 2;
    }
    else if (iVar2 == 4) {
      uVar3 = uVar3 | 1;
    }
    else if (iVar2 == 1) {
      uVar3 = uVar3 | 4;
    }
    else if (iVar2 == 2) {
      uVar3 = uVar3 | 8;
    }
  }
  return uVar3;
}

