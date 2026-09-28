// FUN_0040f584 @ 0040f584 size=90 sig=undefined FUN_0040f584() cc=unknown
// callers: FUN_004105e8
// callees: FUN_0044ba40,FUN_0044ba18

undefined4 FUN_0040f584(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar5 = 0;
  piVar4 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *piVar4;
    if (iVar1 != 0) {
      iVar2 = FUN_0044ba18(iVar1);
      iVar3 = FUN_0044ba40(iVar1);
      if ((iVar2 < iVar3) && (*(int *)(&DAT_004f9de6 + *(char *)(iVar1 + 4) * 0x32) == param_2)) {
        return 0;
      }
    }
    iVar5 = iVar5 + 1;
    piVar4 = piVar4 + 0xd;
    if (0x23 < iVar5) {
      return 1;
    }
  } while( true );
}

