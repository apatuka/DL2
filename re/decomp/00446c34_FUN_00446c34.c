// FUN_00446c34 @ 00446c34 size=85 sig=undefined FUN_00446c34() cc=unknown
// callers: FUN_004471c0
// callees: FUN_004412d4,FUN_00446bf0

undefined4 FUN_00446c34(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x7a);
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if ((((DAT_004d5aa0 == '\0') && (*(char *)(iVar1 + 8) != *(char *)(param_1 + 0x20))) &&
        (iVar2 = FUN_00446bf0(iVar1), iVar2 == 0)) &&
       (iVar2 = FUN_004412d4((int)*(char *)(iVar1 + 8),(int)*(char *)(param_1 + 0x20),2), iVar2 == 0
       )) break;
    iVar1 = *(int *)(iVar1 + 0x54);
  }
  return 1;
}

