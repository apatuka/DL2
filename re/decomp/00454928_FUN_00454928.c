// FUN_00454928 @ 00454928 size=772 sig=undefined FUN_00454928() cc=unknown
// callers: FUN_004556b0,FUN_00455c88,FUN_00453c30
// callees: FUN_00453a38,FUN_00453ec8,FUN_00453c30,FUN_004480a8,FUN_00453d9c,FUN_00450da4,FUN_004543f8,FUN_004412d4,FUN_00450f60,FUN_00450f84,FUN_00447c2c,FUN_00450e04,FUN_00454690,FUN_00447da4,FUN_00454160,FUN_004482cc,FUN_00451180,FUN_00450e28

void FUN_00454928(int param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int local_1c;
  uint local_18;
  uint local_14;
  uint local_c;
  int local_8;
  
  iVar5 = FUN_00450f84(param_1);
  if (iVar5 == 0) {
    iVar5 = FUN_00450f60(param_1);
    if (iVar5 == 0) {
      iVar5 = FUN_004482cc(param_1);
      if (iVar5 == 0) {
        local_8 = 0;
        local_c = 0xffffffff;
        uVar3 = 0;
        local_14 = 0;
        local_18 = 0;
        local_1c = FUN_00447c2c(param_1);
        iVar5 = FUN_00450e04(param_1);
        if ((iVar5 == 0) && (*(char *)(param_1 + 9) != '\0')) {
          *(undefined4 *)(param_1 + 0x3c) = 0;
          local_c = FUN_00453a38(param_1,param_2);
          if ((*(char *)(param_1 + 9) == '\x17') && (*(int *)(param_1 + 0x3c) != 0)) {
            DAT_0057e244 = local_c;
            return;
          }
          if ((4 < *(byte *)(param_1 + 9)) && (*(int *)(param_1 + 0x40) != 0)) {
            *(undefined4 *)(param_1 + 0x3c) = 0;
            DAT_0057e244 = local_c;
            return;
          }
        }
        else {
          *(undefined4 *)(param_1 + 0x40) = 0;
        }
        uVar4 = local_18;
        for (iVar5 = *(int *)(DAT_0057cdf8 + 0x74); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x44)) {
          uVar9 = 0;
          local_18 = uVar4;
          if (((((*(char *)(iVar5 + 0x1d) != '\0') &&
                (*(char *)(iVar5 + 0x1e) != *(char *)(param_1 + 0x1e))) &&
               (iVar6 = FUN_004412d4(*(undefined1 *)(iVar5 + 0x1e),*(undefined1 *)(param_1 + 0x1e),2
                                    ), iVar6 == 0)) && (iVar6 = FUN_00450f60(iVar5), iVar6 == 0)) &&
             (((&DAT_004faf8d)[*(int *)(iVar5 + 4) * 0x24] != '\x03' ||
              (*(int *)(param_1 + 4) != 0x20)))) {
            *(int *)(param_1 + 0x3c) = iVar5;
            uVar7 = FUN_00451180(param_1,*(undefined4 *)(iVar5 + 0x20),*(undefined4 *)(iVar5 + 0x24)
                                );
            if ((param_2 == 0) || (uVar8 = FUN_004480a8(param_1), uVar7 <= uVar8)) {
              iVar6 = FUN_00450e28(param_1);
              if (iVar6 != 0) {
                if (((&DAT_004faf87)[*(int *)(iVar5 + 4) * 0x24] == '\x02') ||
                   ((&DAT_004faf87)[*(int *)(iVar5 + 4) * 0x24] == '\f')) goto LAB_00454c09;
                if ((&DAT_004faf8d)[*(int *)(iVar5 + 4) * 0x24] == '\x03') {
                  local_1c = 10;
                  uVar9 = 0x200;
                }
              }
              if (uVar7 < 3) {
                uVar9 = uVar9 + 0x100;
              }
              if (param_1 == *(int *)(iVar5 + 0x3c)) {
                uVar9 = uVar9 + 0x80;
              }
              if ((uVar7 <= local_c) && (uVar9 = uVar9 + 0x40, uVar7 < local_c)) {
                local_14 = local_14 & 0xffffffbf;
                local_c = uVar7;
              }
              iVar6 = FUN_00447da4(iVar5);
              if (iVar6 - *(short *)(iVar5 + 0x32) <= local_1c) {
                uVar9 = uVar9 + 0x20;
              }
              if (*(int *)(iVar5 + 0x40) != 0) {
                uVar9 = uVar9 + 0x10;
              }
              if (0 < *(short *)(iVar5 + 0x32)) {
                uVar9 = uVar9 + 8;
              }
              if ((*(int *)(iVar5 + 4) == 6) || (*(int *)(iVar5 + 4) == 0xd)) {
                uVar9 = uVar9 + 4;
              }
              uVar2 = *(ushort *)(iVar5 + 10);
              if ((uVar3 <= uVar2) && (uVar9 = uVar9 + 2, uVar3 < uVar2)) {
                local_14 = local_14 & 0xfffffffd;
                uVar3 = uVar2;
              }
              if ((uVar9 == local_14) && (uVar7 < local_c)) {
                local_18 = FUN_00450da4(0xffffffff);
                while (local_18 == uVar4) {
                  local_18 = FUN_00450da4(0xffffffff);
                }
                if (uVar4 < local_18) {
                  uVar9 = uVar9 + 1;
                }
              }
              if (local_14 < uVar9) {
                uVar3 = *(ushort *)(iVar5 + 10);
                local_14 = uVar9;
                local_c = uVar7;
                local_8 = iVar5;
              }
            }
          }
LAB_00454c09:
          uVar4 = local_18;
        }
        *(int *)(param_1 + 0x3c) = local_8;
        DAT_0057e244 = local_c;
      }
      else {
        FUN_00453c30(param_1,param_2);
      }
    }
    else {
      FUN_00453d9c(param_1);
    }
  }
  else {
    cVar1 = *(char *)(param_1 + 0x14);
    if (cVar1 == '\x01') {
      FUN_00454690(param_1);
    }
    else if (cVar1 == '\x02') {
      FUN_00454160(param_1);
    }
    else if (cVar1 == '\x04') {
      FUN_004543f8(param_1);
    }
    else if (cVar1 == '\b') {
      FUN_00453ec8(param_1);
    }
  }
  return;
}

