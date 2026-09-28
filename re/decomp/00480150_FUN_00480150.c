// FUN_00480150 @ 00480150 size=2581 sig=undefined FUN_00480150() cc=unknown
// callers: FUN_0043e058,FUN_00480b80,FUN_0043e0dc,FUN_0044a000,FUN_00449dec
// callees: FUN_0047f5cc,FUN_0047ee04,FUN_0047fffc,FUN_0048477c,FUN_0048447c,FUN_00445190,FUN_00490796,FUN_0047f178,FUN_0047f728,FUN_0047fd88,FUN_0048463c,FUN_0047f4ec,sprintf,FUN_0044e9e4,FUN_00459864,FUN_0047f670,FUN_0048c85e,FUN_0047fc38,FUN_00463d00,FUN_0047ff5c,FUN_00490ab3,FUN_0047f9a0,FUN_0047fc84,DrawSTileBuilding

void FUN_00480150(void)

{
  bool bVar1;
  int iVar2;
  ushort uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  int iVar10;
  undefined4 local_6c;
  undefined4 local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  char local_48 [12];
  int local_3c;
  int local_38;
  int *local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  iVar9 = DAT_004c545c;
  iVar2 = DAT_004c5458;
  if (DAT_004dcc1c != 0) {
    iVar7 = DAT_004c5460 - DAT_004c5b60;
    iVar10 = DAT_004c5464 - DAT_004c5b64;
    FUN_00463d00(DAT_004c5458,DAT_004c545c,iVar7,iVar10);
    if (*(int *)(*(int *)(&DAT_0058de34 + DAT_00583e18 * 0x1c) + 4) < iVar7) {
      iVar7 = *(int *)(*(int *)(&DAT_0058de34 + DAT_00583e18 * 0x1c) + 4);
    }
    if (*(int *)(*(int *)(&DAT_0058de34 + DAT_00583e18 * 0x1c) + 8) < iVar10) {
      iVar10 = *(int *)(*(int *)(&DAT_0058de34 + DAT_00583e18 * 0x1c) + 8);
    }
    local_30 = DAT_004dcc24;
    local_28 = DAT_004dcc24 + iVar7;
    local_2c = DAT_004dcc28;
    local_24 = DAT_004dcc28 + iVar10;
    local_20 = iVar2;
    local_1c = iVar9;
    local_18 = iVar7 + iVar2;
    local_14 = iVar10 + iVar9;
    FUN_0048c85e(DAT_004dcc1c,*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c),&local_30,
                 &local_20,0,&DAT_0065e580,0);
    iVar2 = DAT_00657de0;
    uVar4 = DAT_00561a30;
    if (DAT_00657de0 != 0) {
      if ((DAT_004cf850 == 0) || (*(char *)(DAT_00559dbc + 0xd) != '\0')) {
        local_34 = &DAT_004dcd00;
        iVar9 = 0;
        do {
          local_64 = *local_34;
          iVar7 = local_64 * 0x34 + iVar2;
          FUN_0047ee04((int)*(char *)(iVar7 + 0x140),(int)*(char *)(iVar7 + 0x141),&local_6c,
                       &local_68);
          if (DAT_004cf850 == 0) {
            if ((*(char *)(iVar2 + 0x66 + DAT_0058f1f4) == '\x04') || (DAT_004d5aa0 != '\0')) {
              if (*(char *)(iVar7 + 0x150) != '\0') {
                FUN_0047f178(local_6c,local_68,(int)*(char *)(iVar7 + 0x150));
              }
            }
            else if (*(char *)(iVar7 + 0x15c) != '\0') {
              FUN_0047f178(local_6c,local_68,(int)*(char *)(iVar7 + 0x15c));
            }
          }
          else if (*(short *)(DAT_00559dbc + 0x2c + local_64 * 2) != 0) {
            FUN_0047f178(local_6c,local_68,(int)*(short *)(DAT_00559dbc + 0x2c + local_64 * 2));
          }
          if (((DAT_004d5aa0 == '\0') && (*(char *)(iVar2 + 0x66 + DAT_0058f1f4) != '\x04')) ||
             (*(char *)(iVar7 + 0x143) != '\0')) {
            if (((DAT_004d5aa0 == '\0') && (*(char *)(iVar2 + 0x66 + DAT_0058f1f4) != '\x04')) &&
               ((*(char *)(iVar7 + 0x173) == '\0' &&
                ((uVar3 = *(ushort *)(iVar7 + 0x172) & 0xff, uVar3 != 2 && (uVar3 != 3)))))) {
              FUN_0047f9a0(local_6c,local_68,uVar3,(int)*(char *)(iVar7 + 0x15c),iVar9);
            }
          }
          else {
            uVar3 = *(ushort *)(iVar7 + 0x142) & 0xff;
            if ((uVar3 != 2) && (uVar3 != 3)) {
              FUN_0047f9a0(local_6c,local_68,uVar3,(int)*(char *)(iVar7 + 0x150),iVar9);
            }
          }
          iVar9 = iVar9 + 1;
          local_34 = local_34 + 1;
        } while (iVar9 < 0x24);
        local_34 = &DAT_004dcd00;
        iVar9 = 0;
        do {
          local_58 = *local_34;
          iVar7 = local_58 * 0x34 + iVar2;
          pcVar8 = (char *)(iVar7 + 0x140);
          local_54 = *(int *)(&DAT_004dcc2c + local_58 * 4) * 100;
          FUN_0047ee04((int)*pcVar8,(int)*(char *)(iVar7 + 0x141),&local_60,&local_5c);
          uVar4 = FUN_00445190(uVar4,local_54 + 0x32);
          if (((DAT_004d5aa0 == '\0') && (*(char *)(iVar2 + 0x66 + DAT_0058f1f4) != '\x04')) ||
             (*(char *)(iVar7 + 0x143) != '\0')) {
            if (((DAT_004d5aa0 == '\0') && (*(char *)(iVar2 + 0x66 + DAT_0058f1f4) != '\x04')) &&
               (*(char *)(iVar7 + 0x173) == '\0')) {
              uVar3 = *(ushort *)(iVar7 + 0x172) & 0xff;
              if ((uVar3 == 2) || (uVar3 == 3)) {
                FUN_0047f9a0(local_60,local_5c,uVar3,(int)*(char *)(iVar7 + 0x15c),iVar9);
              }
              if ((*(char *)(iVar7 + 0x144) != '\0') && (DAT_004cf850 == 0)) {
                FUN_0047fc38(local_60,local_5c,(int)*(char *)(iVar7 + 0x144));
              }
            }
          }
          else {
            uVar3 = *(ushort *)(iVar7 + 0x142) & 0xff;
            if ((uVar3 == 2) || (uVar3 == 3)) {
              FUN_0047f9a0(local_60,local_5c,uVar3,(int)*(char *)(iVar7 + 0x150),iVar9);
            }
            if ((*(char *)(iVar7 + 0x144) != '\0') && (DAT_004cf850 == 0)) {
              FUN_0047fc38(local_60,local_5c,(int)*(char *)(iVar7 + 0x144));
            }
          }
          uVar4 = FUN_00445190(uVar4,local_54 + 0x4b);
          if (DAT_004cf850 == 0) {
            if ((*(char *)(iVar2 + 0x66 + DAT_0058f1f4) == '\x04') || (DAT_004d5aa0 != '\0')) {
              if ((*(int *)(iVar7 + 0x154) == 0) ||
                 (*(char *)(*(int *)(iVar7 + 0x154) + 5) == '\x14')) {
                if ((((int)(short)*(ushort *)(iVar7 + 0x142) & 0xf000U) == 0x4000) &&
                   ((*(ushort *)(iVar7 + 0x142) & 0xf00) == 0)) {
                  local_50 = iVar7 + 0x244;
                  if (*(int *)(iVar7 + 600) != 0) {
                    uVar6 = *(undefined4 *)(iVar7 + 600);
                    iVar10 = (int)*(char *)(*(int *)(iVar7 + 600) + 4);
                    uVar5 = FUN_0047f4ec(*(undefined4 *)(iVar7 + 600));
                    DrawSTileBuilding(local_60 + -100,local_5c,uVar5,iVar10,uVar6);
                  }
                }
                else if ((((int)*(short *)(iVar7 + 0x142) & 0xf000U) == 0x6000) &&
                        (local_4c = iVar7 + 0x620, *(int *)(iVar7 + 0x634) != 0)) {
                  uVar6 = *(undefined4 *)(iVar7 + 0x634);
                  iVar10 = (int)*(char *)(*(int *)(iVar7 + 0x634) + 4);
                  uVar5 = FUN_0047f4ec(*(undefined4 *)(iVar7 + 0x634));
                  DrawSTileBuilding(local_60 + -200,local_5c + 100,uVar5,iVar10,uVar6);
                }
              }
              else if ((&DAT_004f9dc5)[*(char *)(*(int *)(iVar7 + 0x154) + 4) * 0x32] == '\x01') {
                uVar6 = *(undefined4 *)(iVar7 + 0x154);
                iVar10 = (int)*(char *)(*(int *)(iVar7 + 0x154) + 4);
                uVar5 = FUN_0047f4ec(*(undefined4 *)(iVar7 + 0x154));
                DrawSTileBuilding(local_60,local_5c,uVar5,iVar10,uVar6);
              }
            }
            else if (*(char *)(iVar7 + 0x15a) != '\0') {
              if ((&DAT_004f9dc5)[*(char *)(iVar7 + 0x15a) * 0x32] == '\x01') {
                FUN_0047ff5c(pcVar8,local_60,local_5c,
                             CONCAT22((short)((uint)(*(char *)(iVar7 + 0x15a) * 0x19) >> 0x10),
                                      *(undefined2 *)(iVar2 + 0x1a)),local_58);
              }
              else if ((&DAT_004f9dc5)[*(char *)(iVar7 + 0x15a) * 0x32] == '\x02') {
                FUN_0047ff5c(pcVar8,local_60 + -100,local_5c,
                             CONCAT22((short)((uint)(*(char *)(iVar7 + 0x15a) * 0x19) >> 0x10),
                                      *(undefined2 *)(iVar2 + 0x1a)),local_58);
              }
              else {
                FUN_0047ff5c(pcVar8,local_60 + -200,local_5c + 100,
                             CONCAT22((char)(&DAT_004f9dc5)[*(char *)(iVar7 + 0x15a) * 0x32] >> 7,
                                      *(undefined2 *)(iVar2 + 0x1a)),local_58);
              }
            }
          }
          else if (*(char *)(iVar7 + 0x158) != '\0') {
            if ((&DAT_004f9dc5)[*(char *)(iVar7 + 0x158) * 0x32] == '\x01') {
              FUN_0047fd88(pcVar8,local_60,local_5c,
                           CONCAT22((short)((uint)(*(char *)(iVar7 + 0x158) * 0x19) >> 0x10),
                                    *(undefined2 *)(iVar2 + 0x1a)),local_58);
            }
            else if ((&DAT_004f9dc5)[*(char *)(iVar7 + 0x158) * 0x32] == '\x02') {
              FUN_0047fd88(pcVar8,local_60 + -100,local_5c,
                           CONCAT22((short)((uint)(*(char *)(iVar7 + 0x158) * 0x19) >> 0x10),
                                    *(undefined2 *)(iVar2 + 0x1a)),local_58);
            }
            else {
              FUN_0047fd88(pcVar8,local_60 + -200,local_5c + 100,
                           CONCAT22((char)(&DAT_004f9dc5)[*(char *)(iVar7 + 0x158) * 0x32] >> 7,
                                    *(undefined2 *)(iVar2 + 0x1a)),local_58);
            }
          }
          if (*(int *)(iVar7 + 0x154) == 0) {
            bVar1 = false;
            if ((short)*(ushort *)(iVar7 + 0x142) < 5) {
              bVar1 = true;
            }
            else if ((*(ushort *)(iVar7 + 0x142) & 0xf00) == 0x100) {
              bVar1 = true;
            }
            if ((bVar1) && (DAT_004cf850 == 0)) {
              local_48[0] = '\0';
              switch(DAT_00559da0) {
              case 1:
                uVar6 = FUN_0044e9e4(DAT_00657de0,pcVar8,0xc,100,1);
                sprintf(local_48,&DAT_004dce05,uVar6);
                break;
              case 2:
                uVar6 = FUN_0044e9e4(DAT_00657de0,pcVar8,0xd,100,1);
                sprintf(local_48,&DAT_004dce05,uVar6);
                break;
              case 3:
                uVar6 = FUN_0044e9e4(DAT_00657de0,pcVar8,0xf,100,1);
                sprintf(local_48,&DAT_004dce05,uVar6);
                break;
              case 4:
                uVar6 = FUN_0044e9e4(DAT_00657de0,pcVar8,3,100,1);
                sprintf(local_48,&DAT_004dce05,uVar6);
                break;
              case 5:
                uVar6 = FUN_0044e9e4(DAT_00657de0,pcVar8,4,100,1);
                sprintf(local_48,&DAT_004dce05,uVar6);
              }
              if (local_48[0] != '\0') {
                FUN_0048463c(0);
                FUN_0048447c(local_48,0x32);
                FUN_0048477c(local_60 + 0x19,local_5c,0x32,0x32,local_48,0xff,1);
                FUN_0048463c(DAT_0058f1d0);
              }
            }
          }
          uVar4 = FUN_00445190(uVar4,local_54 + 99);
          iVar10 = *(int *)(iVar7 + 0x154);
          if (((iVar10 == 0) || ((&DAT_004f9dc5)[*(char *)(iVar10 + 4) * 0x32] != '\x01')) ||
             (DAT_004cf850 != 0)) {
            if (((((int)(short)*(ushort *)(iVar7 + 0x142) & 0xf000U) == 0x4000) &&
                ((*(ushort *)(iVar7 + 0x142) & 0xf00) == 0)) &&
               ((DAT_004cf850 == 0 && (local_3c = iVar7 + 0x244, *(int *)(iVar7 + 600) != 0)))) {
              FUN_0047f670(local_60,local_5c,*(undefined4 *)(iVar7 + 600),iVar2);
              FUN_0047f728(local_60,local_5c,*(undefined4 *)(local_3c + 0x14),iVar2);
            }
          }
          else {
            FUN_0047f670(local_60,local_5c,iVar10,iVar2);
            FUN_0047f728(local_60,local_5c,*(undefined4 *)(iVar7 + 0x154),iVar2);
          }
          iVar10 = *(int *)(iVar7 + 0x154);
          if (((iVar10 == 0) || ((&DAT_004f9dc5)[*(char *)(iVar10 + 4) * 0x32] != '\x01')) ||
             (DAT_004cf850 != 0)) {
            if ((((((int)(short)*(ushort *)(iVar7 + 0x142) & 0xf000U) == 0x4000) &&
                 ((*(ushort *)(iVar7 + 0x142) & 0xf00) == 0)) && (DAT_004cf850 == 0)) &&
               (*(int *)(iVar7 + 600) != 0)) {
              FUN_0047f5cc(local_60,local_5c,*(undefined4 *)(iVar7 + 600));
            }
          }
          else {
            FUN_0047f5cc(local_60,local_5c,iVar10);
          }
          iVar9 = iVar9 + 1;
          local_34 = local_34 + 1;
        } while (iVar9 < 0x24);
        FUN_0047fc84(DAT_00657de0);
        if (DAT_004cf850 == 0) {
          FUN_0047fffc();
          local_38 = FUN_00490ab3(0,0x47414d49,0x31304d43,0,0x80000000);
          if (local_38 != 0) {
            FUN_00459864(local_38,0x3ef,0,4,0x119);
            FUN_00490796(local_38,1);
          }
        }
        FUN_00445190(uVar4,0x7fff);
      }
      else {
        FUN_00445190(DAT_00561a30,0x7fff);
      }
    }
  }
  return;
}

