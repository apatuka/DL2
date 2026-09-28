// FUN_00455c88 @ 00455c88 size=922 sig=undefined FUN_00455c88() cc=unknown
// callers: FUN_004570e0
// callees: FUN_0043d860,FUN_0043d8dc,FUN_0043d958,FUN_0043d974,FUN_00453350,FUN_00453210,FUN_00453568,FUN_004481a4,FUN_00447c2c,FUN_00450e04,FUN_0043da44,FUN_00450f38,FUN_00454928,FUN_004480a8,FUN_00450da4,CreateBldgHit,FUN_0043d2d8,FUN_00450ec8,FUN_00448008,FUN_00455a04,CreateHit,FUN_00450e88,FUN_004482cc,FUN_00448210,FUN_00450e28

/* WARNING: Type propagation algorithm not settling */

void FUN_00455c88(int param_1)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  char *pcVar10;
  int local_2c;
  int local_28;
  undefined4 local_24;
  int local_20 [4];
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (((param_1 != 0) && (*(char *)(param_1 + 0x35) == '\0')) &&
     (FUN_00454928(param_1,1), *(char *)(param_1 + 0x1d) != '\0')) {
    uVar3 = FUN_004480a8(param_1);
    if (uVar3 < DAT_0057e244) {
      *(undefined1 *)(param_1 + 0x35) = 0;
    }
    else {
      cVar1 = FUN_00448008(param_1);
      cVar2 = FUN_00450da4(3);
      *(char *)(param_1 + 0x35) = cVar1 + cVar2;
      if (*(int *)(param_1 + 0x3c) == 0) {
        if (*(int *)(param_1 + 0x40) == 0) {
          *(undefined1 *)(param_1 + 0x35) = 0;
        }
        else {
          uVar9 = *(undefined4 *)(param_1 + 0x40);
          FUN_00453210(uVar9,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),
                       &local_8,&local_c);
          if (DAT_004cf850 != 0) {
            FUN_0043d2d8(param_1);
          }
          iVar4 = FUN_00455a04(param_1,local_8,local_c);
          if (iVar4 != 0) {
            if (DAT_004cf850 != 0) {
              CreateBldgHit(uVar9,*(undefined4 *)(param_1 + 4));
            }
            iVar4 = FUN_004482cc(param_1);
            if (iVar4 == 0) {
              uVar5 = FUN_00447c2c(param_1);
              FUN_00453568(uVar9,uVar5,param_1);
            }
          }
        }
      }
      else {
        iVar4 = *(int *)(param_1 + 0x3c);
        if (DAT_004cf850 != 0) {
          iVar6 = FUN_004481a4(param_1);
          if (iVar6 == 0) {
            iVar6 = FUN_00448210(param_1);
            if (iVar6 == 0) {
              FUN_0043d2d8(param_1);
            }
            else {
              FUN_0043d8dc(param_1);
            }
          }
          else {
            FUN_0043d860(param_1);
          }
        }
        iVar6 = FUN_00455a04(param_1,*(undefined4 *)(iVar4 + 0x20),*(undefined4 *)(iVar4 + 0x24));
        if (iVar6 != 0) {
          iVar6 = FUN_004481a4(param_1);
          if (iVar6 == 0) {
            iVar6 = FUN_00448210(param_1);
            if (iVar6 == 0) {
              iVar6 = FUN_00450e28(param_1);
              if (((iVar6 == 0) && (iVar6 = FUN_00450ec8(param_1), iVar6 == 0)) ||
                 ((&DAT_004faf8d)[*(int *)(iVar4 + 4) * 0x24] != '\x03')) {
                iVar6 = FUN_00450e88(param_1);
                if ((iVar6 == 0) || ((&DAT_004faf8d)[*(int *)(iVar4 + 4) * 0x24] != '\x03')) {
                  uVar5 = 0;
                  uVar9 = FUN_00447c2c(param_1);
                  FUN_00453350(iVar4,uVar9,uVar5);
                }
                else {
                  iVar6 = FUN_00447c2c(param_1);
                  local_28 = (iVar6 * 0x50) / 100;
                  local_2c = 1;
                  if (local_28 < 1) {
                    piVar8 = &local_2c;
                  }
                  else {
                    piVar8 = &local_28;
                  }
                  FUN_00453350(iVar4,*piVar8,0);
                }
              }
              else {
                switch(*(undefined4 *)(param_1 + 4)) {
                case 9:
                  FUN_00453350(iVar4,5,0);
                  break;
                case 10:
                  FUN_00453350(iVar4,2,0);
                  break;
                case 0xb:
                  FUN_00453350(iVar4,0xe,0);
                  break;
                case 0x14:
                case 0x22:
                  FUN_00453350(iVar4,10,0);
                  break;
                case 0x1c:
                  FUN_00453350(iVar4,1,0);
                }
              }
              if (DAT_004cf850 != 0) {
                CreateHit(iVar4,param_1,0xb5);
              }
            }
            else {
              iVar6 = FUN_004482cc(param_1);
              if (iVar6 != 0) {
                FUN_0043da44(param_1);
              }
              iVar6 = FUN_00450e04(iVar4);
              if (iVar6 == 0) {
                if ((ushort)*(byte *)(param_1 + 0x1e) == *(ushort *)(DAT_0057cdf8 + 8)) {
                  DAT_005649e4 = DAT_005649e4 + 1;
                  DAT_005649e0 = DAT_005649e0 + -1;
                }
                *(byte *)(iVar4 + 0x1e) = *(byte *)(param_1 + 0x1e);
              }
              else {
                *(undefined1 *)(iVar4 + 0x1e) = *(undefined1 *)(param_1 + 0x1e);
                DAT_005649e4 = DAT_005649e4 + -1;
                DAT_005649e0 = DAT_005649e0 + 1;
              }
              iVar6 = FUN_00448008(param_1);
              local_20[0] = iVar6 + -2;
              local_24 = 0;
              if (iVar6 + -2 < 0) {
                pcVar10 = (char *)&local_24;
              }
              else {
                pcVar10 = (char *)local_20;
              }
              *(char *)(iVar4 + 0x35) = *(char *)(iVar4 + 0x35) + *pcVar10;
              if (DAT_004cf850 != 0) {
                FUN_0043d974(iVar4,param_1);
              }
              FUN_00453350(iVar4,2,1);
            }
          }
          else {
            if (DAT_004cf850 != 0) {
              FUN_0043d958(iVar4,param_1);
            }
            local_10 = FUN_004481a4(param_1);
            local_20[3] = (local_10 * 0x19) / 100;
            local_20[2] = 1;
            if (local_20[3] < 1) {
              piVar8 = local_20 + 2;
            }
            else {
              piVar8 = local_20 + 3;
            }
            iVar6 = *piVar8;
            iVar7 = FUN_00450f38(param_1);
            if (iVar7 != 0) {
              local_10 = local_10 + iVar6;
            }
            iVar7 = FUN_00450f38(iVar4);
            if (iVar7 != 0) {
              local_10 = local_10 - iVar6;
            }
            local_20[1] = 0;
            if (local_10 < 0) {
              piVar8 = local_20 + 1;
            }
            else {
              piVar8 = &local_10;
            }
            local_10 = *piVar8;
            FUN_00453350(iVar4,local_10,1);
          }
        }
      }
    }
  }
  return;
}

