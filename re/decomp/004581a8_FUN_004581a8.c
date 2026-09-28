// FUN_004581a8 @ 004581a8 size=240 sig=undefined FUN_004581a8() cc=unknown
// callers: FUN_00426868,FUN_00468214,FUN_00468a28
// callees: FUN_00457dbc,CGNetService_GetType

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004581a8(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  _DAT_00583854 = param_2;
  puVar1 = &DAT_0058389c;
  do {
    *puVar1 = 0;
    iVar3 = iVar3 + 1;
    puVar1 = puVar1 + 0x20;
  } while (iVar3 < 0x14);
  if (DAT_004d1718 == 0) {
    iVar3 = FUN_00457dbc();
    if (iVar3 == 0) {
      return 0;
    }
    DAT_004d1718 = 1;
  }
  iVar3 = 0;
  while( true ) {
    if (DAT_00583b70 <= iVar3) {
      return 0;
    }
    iVar2 = CGNetService_GetType(*(undefined4 *)(DAT_00583b6c + iVar3 * 4));
    if ((iVar2 == 3) && (param_2 == 2)) {
      DAT_00583b74 = *(undefined4 *)(DAT_00583b6c + iVar3 * 4);
      return 1;
    }
    if ((iVar2 == 4) && (param_2 == 1)) {
      DAT_00583b74 = *(undefined4 *)(DAT_00583b6c + iVar3 * 4);
      return 1;
    }
    if ((iVar2 == 1) && (param_2 == 4)) break;
    if ((iVar2 == 2) && (param_2 == 8)) {
      DAT_00583b74 = *(undefined4 *)(DAT_00583b6c + iVar3 * 4);
      return 1;
    }
    iVar3 = iVar3 + 1;
  }
  DAT_00583b74 = *(undefined4 *)(DAT_00583b6c + iVar3 * 4);
  return 1;
}

