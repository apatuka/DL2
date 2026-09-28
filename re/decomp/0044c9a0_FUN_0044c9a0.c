// FUN_0044c9a0 @ 0044c9a0 size=147 sig=undefined FUN_0044c9a0() cc=unknown
// callers: FUN_00445f08,FUN_004526b0,FUN_0044db50,FUN_0046b1ac,FUN_0044dcf4,FUN_00475e40,FUN_00475da4
// callees: FUN_0044ba40,FUN_0044bea8,MoveHousingLabor,FUN_0044c754

void FUN_0044c9a0(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  int iVar5;
  int local_8;
  
  iVar1 = param_3;
  FUN_0044bea8(param_1);
  if (iVar1 != 0) {
    iVar2 = FUN_0044c754(param_1);
    if ((param_2 == -1) || (iVar2 < param_2)) {
      param_2 = iVar2;
    }
    local_8 = FUN_0044ba40(iVar1);
    if (param_2 < local_8) {
      piVar3 = &param_2;
    }
    else {
      piVar3 = &local_8;
    }
    param_2 = *piVar3;
    pcVar4 = (char *)(iVar1 + 0x2c);
    iVar2 = 0;
    do {
      if ((*pcVar4 != '\x15') && (*pcVar4 != '\0')) break;
      iVar2 = iVar2 + 1;
      pcVar4 = pcVar4 + 1;
    } while (iVar2 < 5);
    if ((iVar2 != 5) && (iVar5 = 0, 0 < param_2)) {
      do {
        MoveHousingLabor(param_1,iVar1,iVar2);
        iVar5 = iVar5 + 1;
      } while (iVar5 < param_2);
    }
  }
  return;
}

