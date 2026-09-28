// FUN_00403c04 @ 00403c04 size=158 sig=undefined FUN_00403c04() cc=unknown
// callers: 
// callees: FUN_00476448,FUN_0044d1e4

void FUN_00403c04(int *param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  
  iVar5 = 0;
  sVar3 = 0;
  piVar6 = param_1;
  do {
    sVar1 = *(short *)(*piVar6 + 0x30);
    if ((299 < sVar1) && (sVar3 < sVar1)) {
      iVar5 = *piVar6;
      sVar3 = sVar1;
    }
    piVar6 = (int *)piVar6[1];
  } while (piVar6 != param_1);
  if (iVar5 != 0) {
    do {
      iVar2 = *piVar6;
      while( true ) {
        iVar4 = FUN_0044d1e4(iVar2,0x11,0);
        if (((iVar4 == -1) ||
            (((99 < *(short *)(iVar2 + 0x30) || (*(short *)(iVar5 + 0x30) < 0x12d)) &&
             ((499 < *(short *)(iVar2 + 0x30) || (*(short *)(iVar5 + 0x30) < 0xfa1)))))) ||
           (DAT_00522018 < 4)) break;
        iVar4 = FUN_00476448(iVar5,iVar2,100,0,0xffffffff,0xffffffff);
        if (iVar4 == 0) break;
        DAT_00522018 = DAT_00522018 + -4;
      }
      piVar6 = (int *)piVar6[1];
    } while (piVar6 != param_1);
  }
  return;
}

