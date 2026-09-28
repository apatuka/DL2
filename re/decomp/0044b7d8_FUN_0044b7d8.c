// FUN_0044b7d8 @ 0044b7d8 size=133 sig=undefined FUN_0044b7d8() cc=unknown
// callers: FUN_0041db10,FUN_0041c418,FUN_0041b71c,FUN_0041e0a8,FUN_0041c258,FUN_0041bd60
// callees: FUN_004023dc,FUN_0044ba40

int FUN_0044b7d8(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int local_8;
  
  local_8 = 0;
  iVar6 = 0;
  piVar5 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *piVar5;
    if ((iVar1 != 0) && ((&DAT_004f9dc3)[*(char *)(iVar1 + 4) * 0x32] == '\x11')) {
      iVar2 = FUN_004023dc(iVar1,0x14);
      if (iVar2 != -1) {
        iVar3 = FUN_0044ba40(iVar1);
        local_8 = local_8 + iVar3;
        iVar3 = 0;
        piVar4 = (int *)(iVar1 + 0x18);
        do {
          if ((iVar3 != iVar2) && (*piVar4 != 0)) {
            local_8 = local_8 - *piVar4;
          }
          iVar3 = iVar3 + 1;
          piVar4 = piVar4 + 1;
        } while (iVar3 < 5);
      }
    }
    iVar6 = iVar6 + 1;
    piVar5 = piVar5 + 0xd;
  } while (iVar6 < 0x24);
  return local_8;
}

