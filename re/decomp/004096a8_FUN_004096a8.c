// FUN_004096a8 @ 004096a8 size=454 sig=undefined FUN_004096a8() cc=unknown
// callers: FUN_00409914
// callees: FUN_00401670,FUN_00409544,FUN_0044d06c,FUN_00409364,FUN_00407d60,FUN_0044d1e4,FUN_0044d1a4,FUN_0040be04,FindConstructionSite,FUN_0040c68c,FUN_00409270

void FUN_004096a8(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  
  piVar6 = &DAT_00521bb4;
  iVar5 = (int)(char)(&DAT_0059f1bf)[param_1 * 0x2d8];
  do {
    iVar1 = *piVar6;
    iVar2 = FUN_0044d06c(iVar1,0x12);
    if ((*(short *)(iVar1 + 0x30) != 0) && (iVar3 = FUN_00401670(iVar1,param_1), iVar3 != 0)) {
      if ((*(char *)(iVar1 + 0x21) == '\0') || (iVar3 = FUN_0040c68c(param_1,5,iVar1), iVar3 != 0))
      {
        if ((*(char *)(iVar1 + 0x21) == '\0') &&
           (iVar3 = FUN_0040c68c(param_1,0xd,iVar1), iVar3 == 0)) {
          FUN_0040be04(param_1,0xffffffff,0xffffffff,iVar1,0xd,iVar5);
        }
      }
      else {
        FUN_0040be04(param_1,0xffffffff,0xffffffff,iVar1,5,iVar5);
      }
    }
    iVar3 = FUN_0044d1a4(iVar1,7,0);
    if (iVar3 != -1) {
      FUN_00409544(param_1,iVar1);
    }
    iVar3 = FUN_00409364(param_1,iVar1);
    if (((iVar3 != 0) && (iVar4 = FindConstructionSite(iVar1,iVar3), iVar4 != -1)) &&
       (iVar4 = FUN_00409270(param_1,iVar1), iVar2 < iVar4)) {
      iVar4 = iVar5;
      if (iVar2 == 0) {
        iVar4 = 15000;
      }
      FUN_00407d60(param_1,0,iVar4,iVar3,(int)*(short *)(iVar1 + 0x1a),1,1);
    }
    if (((*(int *)(iVar1 + 0x8a8) == 0) && (*(short *)(iVar1 + 0x30) != 0)) &&
       ((1 << ((byte)param_1 & 0x1f) & (int)DAT_004fc05c) != 0)) {
      if (((*(char *)(iVar1 + 0x21) == '\0') && (iVar2 = FUN_0044d1e4(iVar1,0x14,0), iVar2 != -1))
         && (iVar2 = FUN_0040c68c(param_1,0xf,iVar1), iVar2 == 0)) {
        FUN_0040be04(param_1,0xffffffff,0xffffffff,iVar1,0xf,100);
      }
      else if ((*(char *)(iVar1 + 0x21) != '\0') &&
              (((iVar2 = FUN_0044d1a4(iVar1,6,0), iVar2 != -1 ||
                (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) == 0)) &&
               (iVar2 = FUN_0040c68c(param_1,7,iVar1), iVar2 == 0)))) {
        FUN_0040be04(param_1,0xffffffff,0xffffffff,iVar1,7,100);
      }
    }
    piVar6 = (int *)piVar6[1];
  } while (piVar6 != &DAT_00521bb4);
  return;
}

