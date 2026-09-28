// FUN_004489e0 @ 004489e0 size=761 sig=undefined FUN_004489e0() cc=unknown
// callers: FUN_00448d1c
// callees: CanUpgradeBuilding,FUN_004488c8,FUN_0046b958,FUN_0046bdfc,FUN_00483c3c,FUN_0044890c,FUN_0046b910,FUN_0044eeb4,TotalUnitLabor,FUN_0044c718,FUN_0046b0e4,FUN_004023dc,FUN_0046ac44,FUN_0040552c

undefined4 FUN_004489e0(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 local_90 [16];
  int local_80;
  int *local_18;
  int *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  uVar4 = 0;
  if (*(int *)(&DAT_00564228 + param_2 * 0x18) != 0) {
    uVar4 = 0;
    if (param_3 == 0) {
      if (param_2 == 7) {
        iVar2 = FUN_0046bdfc(param_1);
        if (((iVar2 < 100) && (DAT_0058f16c < 0x19)) &&
           (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] * 2) != 0)) {
          uVar4 = 1;
        }
      }
      else if (param_2 == 0xc) {
        iVar2 = FUN_0040552c(param_1,0xc,0);
        iVar3 = FUN_0046b958(param_1);
        if (iVar2 < iVar3) {
          uVar4 = 1;
        }
      }
      else if (param_2 == 0xf) {
        iVar2 = FUN_0040552c(param_1,0xf,0);
        iVar3 = FUN_0046b910(param_1);
        if (iVar2 < iVar3) {
          uVar4 = 1;
        }
      }
    }
    else {
      switch(param_2) {
      default:
        if ((1 < param_3) || ((param_2 != 0xc && (param_2 != 0xf)))) {
          uVar4 = 1;
        }
        break;
      case 2:
        local_14 = (int *)(param_1 + 0x154);
        local_8 = 0;
        do {
          iVar2 = *local_14;
          if ((iVar2 != 0) && (*(short *)(iVar2 + 0x14) != 0)) {
            iVar3 = FUN_004023dc(iVar2,2);
            iVar3 = FUN_0044eeb4(PTR_DAT_004d5988,param_1,(int)*(char *)(iVar2 + 7),iVar3,
                                 *(undefined4 *)(iVar2 + 0x18 + iVar3 * 4));
            if (iVar3 < *(short *)(iVar2 + 0x14)) {
              uVar4 = 1;
            }
          }
          local_8 = local_8 + 1;
          local_14 = local_14 + 0xd;
        } while (local_8 < 0x24);
        break;
      case 5:
        cVar1 = PTR_DAT_004d5988[0x3e];
        if (&DAT_004fbbac + cVar1 * 0x19 != (undefined2 *)0x0) {
          FUN_0046ac44(local_90,DAT_0058f1f4);
          iVar2 = FUN_00483c3c(PTR_DAT_004d5988,&DAT_004fbbac + cVar1 * 0x19);
          if ((short)(&DAT_004fbbb2)[cVar1 * 0x19 + DAT_0058f1f4] + local_80 < iVar2) {
            uVar4 = 1;
          }
        }
        break;
      case 7:
        iVar2 = FUN_0046bdfc(param_1);
        if (((iVar2 < 100) && (DAT_0058f16c < 0x19)) &&
           (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] * 2) != 0)) {
          uVar4 = 1;
        }
        break;
      case 0x11:
        iVar2 = FUN_0040552c(param_1,0x11,0);
        iVar3 = FUN_0046b0e4(param_1);
        if (iVar2 + *(short *)(param_1 + 0x30) < iVar3) {
          uVar4 = 1;
        }
        break;
      case 0x12:
        uVar4 = FUN_0040552c(param_1,0x12,0);
        uVar4 = FUN_0044890c(param_1,uVar4);
        break;
      case 0x15:
        local_18 = (int *)(param_1 + 0x154);
        local_c = 0;
        do {
          iVar2 = *local_18;
          if ((iVar2 != 0) && (iVar3 = CanUpgradeBuilding(iVar2), iVar3 != 0)) {
            iVar3 = FUN_004023dc(iVar2,0x15);
            local_10 = FUN_0044eeb4(PTR_DAT_004d5988,param_1,(int)*(char *)(iVar2 + 7),iVar3,
                                    *(undefined4 *)(iVar2 + 0x18 + iVar3 * 4));
            iVar3 = FUN_0044c718(iVar2);
            if (*(short *)(iVar2 + 0x16) + local_10 < iVar3) {
              uVar4 = 1;
            }
          }
          local_c = local_c + 1;
          local_18 = local_18 + 0xd;
        } while (local_c < 0x24);
        break;
      case 0x17:
      case 0x18:
      case 0x19:
      case 0x1a:
      case 0x1b:
        iVar2 = FUN_004488c8(param_1,param_2 + -0x16);
        iVar3 = TotalUnitLabor(param_1,param_2 + -0x16);
        if (iVar3 < iVar2) {
          uVar4 = 1;
        }
      }
    }
  }
  return uVar4;
}

