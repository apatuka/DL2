// FUN_00450000 @ 00450000 size=85 sig=undefined FUN_00450000() cc=unknown
// callers: FUN_00486b74,FUN_00450058,FUN_00450150,FUN_00486d30
// callees: FUN_0044fdf0

undefined4 FUN_00450000(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = FUN_0044fdf0(param_1);
  iVar1 = iVar1 * 0x44 + DAT_004d5a94 * 0xd8;
  iVar3 = 1;
  piVar2 = (int *)(&DAT_004c61a8 + iVar1);
  while( true ) {
    if (*(int *)(&DAT_004c61a4 + iVar1) < iVar3) {
      return 0;
    }
    if (param_2 == *piVar2) break;
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
  }
  return 1;
}

