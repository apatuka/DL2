// FUN_0044d600 @ 0044d600 size=434 sig=undefined FUN_0044d600() cc=unknown
// callers: FindConstructionSite,FUN_0044db50,FUN_00402548,FUN_0045eadc
// callees: FUN_0044d2f8,FUN_0044d3f4,FUN_0044d1a4,FUN_0044d440

undefined4 FUN_0044d600(int param_1,int param_2,int param_3)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  ushort uVar7;
  int iVar8;
  
  cVar1 = (&DAT_004f9dc5)[param_2 * 0x32];
  iVar3 = param_3 / 6;
  cVar2 = (&DAT_004f9dc3)[param_2 * 0x32];
  if ((*(char *)(param_1 + 0x21) == '\0') || (iVar4 = FUN_0044d440(param_2), iVar4 == 0)) {
    if ((cVar2 == '\t') && (iVar4 = FUN_0044d1a4(param_1,9,0), iVar4 != -1)) {
      uVar5 = 4;
    }
    else if ((cVar2 == '\x14') && (iVar4 = FUN_0044d1a4(param_1,0x14,0), iVar4 != -1)) {
      uVar5 = 8;
    }
    else if ((cVar2 == '\v') && (iVar4 = FUN_0044d1a4(param_1,0xb,0), iVar4 != -1)) {
      uVar5 = 10;
    }
    else {
      iVar4 = iVar3;
      if ((cVar2 == '\a') && (iVar6 = FUN_0044d2f8(param_1,0), iVar6 == 0)) {
        uVar5 = 5;
      }
      else {
        for (; iVar6 = param_3 % 6, iVar3 - cVar1 < iVar4; iVar4 = iVar4 + -1) {
          for (; iVar6 < param_3 % 6 + (int)cVar1; iVar6 = iVar6 + 1) {
            if ((((iVar6 < 0) || (iVar4 < 0)) || (5 < iVar6)) || (5 < iVar4)) {
              return 1;
            }
            iVar8 = (iVar4 * 6 + iVar6) * 0x34 + param_1;
            if ((*(ushort *)(iVar8 + 0x142) & 0xf00) == 0x100) {
              iVar3 = FUN_0044d3f4(param_2);
              if (iVar3 != 0) {
                return 0;
              }
              return 7;
            }
            if ((*(int *)(iVar8 + 0x154) != 0) || (*(char *)(iVar8 + 0x143) != '\0')) {
              return 2;
            }
            uVar7 = *(ushort *)(iVar8 + 0x142) & 0xff;
            if (((uVar7 == 0xff) && (param_2 != 0x26)) && (param_2 != 0x2f)) {
              return 3;
            }
            if (uVar7 == 5) {
              return 6;
            }
          }
        }
        uVar5 = 0;
      }
    }
  }
  else {
    uVar5 = 9;
  }
  return uVar5;
}

