// FUN_0048d920 @ 0048d920 size=517 sig=undefined FUN_0048d920() cc=unknown
// callers: FUN_0048db5d,@BackWndProc$qqspvuiuil,@IntroWndProc$qqspvuiuil
// callees: FUN_0048afe3,GetKeyState

undefined4 FUN_0048d920(int param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  ushort uVar2;
  short sVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  
  if (param_2 < 0x103) {
    if (param_2 == 0x102) goto LAB_0048da81;
    if (param_2 == 3) {
      if (param_1 == DAT_0051b834) {
        FUN_0048afe3(param_1,param_4 & 0xffff,param_4 >> 0x10);
      }
      return 0;
    }
    if (param_2 != 0x100) {
      return 0;
    }
  }
  else if (param_2 != 0x104) {
    if (5 < param_2 - 0x201U) {
      return 0;
    }
    DAT_0051c2fc = DAT_0051c2fc + 1;
    DAT_0051c2f4 = DAT_0051c2f4 + 1;
    if (DAT_0051c2f4 == 0x14) {
      DAT_0051c2f4 = 0;
    }
    iVar1 = DAT_0051c2f4;
    (&DAT_0065e804)[DAT_0051c2f4 * 5] = param_2;
    (&DAT_0065e808)[iVar1 * 5] = param_3;
    (&DAT_0065e810)[iVar1 * 5] = param_4 & 0xffff;
    (&DAT_0065e814)[iVar1 * 5] = param_4 >> 0x10;
    (&DAT_0065e80c)[iVar1 * 5] = (int)DAT_0051c2fc;
    if (0x13 < DAT_0051c2f8) {
      return 1;
    }
    DAT_0051c2f8 = DAT_0051c2f8 + 1;
    return 1;
  }
  sVar3 = (short)param_3;
  if ((sVar3 < 0x70) || (0x7e < sVar3)) {
    switch(param_3) {
    case 0x21:
      sVar3 = 0x101;
      break;
    case 0x22:
      sVar3 = 0x103;
      break;
    case 0x23:
      sVar3 = 0x105;
      break;
    case 0x24:
      sVar3 = 0x107;
      break;
    case 0x25:
      sVar3 = 0x106;
      break;
    case 0x26:
      sVar3 = 0x108;
      break;
    case 0x27:
      sVar3 = 0x102;
      break;
    case 0x28:
      sVar3 = 0x104;
      break;
    default:
      return 0;
    case 0x2d:
      sVar3 = 0x109;
      break;
    case 0x2e:
      sVar3 = 0x10a;
    }
  }
  else {
    sVar3 = sVar3 + 0xa0;
  }
  param_3 = (int)sVar3;
LAB_0048da81:
  if (param_3 != 0) {
    *(short *)(&DAT_0065e7b4 + DAT_0065e7ac * 4) = (short)param_3;
    uVar4 = 4;
    uVar2 = GetKeyState(0x10);
    if ((uVar2 & 0x8000) == 0) {
      uVar4 = 0;
    }
    uVar5 = 8;
    uVar2 = GetKeyState(0x11);
    if ((uVar2 & 0x8000) == 0) {
      uVar5 = 0;
    }
    uVar6 = 0x4000;
    uVar2 = GetKeyState(0x12);
    if ((uVar2 & 0x8000) == 0) {
      uVar6 = 0;
    }
    *(ushort *)(&DAT_0065e7b6 + DAT_0065e7ac * 4) = uVar4 | uVar5 | uVar6;
    DAT_0065e7ac = DAT_0065e7ac + 1;
    if (DAT_0065e7ac == 0x14) {
      DAT_0065e7ac = 0;
    }
    if (DAT_0065e7b0 == DAT_0065e7ac) {
      DAT_0065e7b0 = DAT_0065e7b0 + 1;
    }
    if (DAT_0065e7b0 == 0x14) {
      DAT_0065e7b0 = 0;
    }
  }
  return 1;
}

