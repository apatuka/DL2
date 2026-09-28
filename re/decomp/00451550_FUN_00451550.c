// FUN_00451550 @ 00451550 size=935 sig=undefined FUN_00451550() cc=unknown
// callers: FUN_00451b68
// callees: FUN_00450de0,FUN_00450f84,FUN_00450da4,FUN_00454c2c,FUN_004511a4,FUN_00451508,FUN_00450f60

/* WARNING: Removing unreachable block (ram,0x0045181a) */

void FUN_00451550(undefined4 *param_1)

{
  undefined4 *puVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined *local_10;
  undefined *local_c;
  uint local_8;
  
  iVar4 = FUN_00451508(param_1);
  iVar5 = FUN_00450f60(param_1);
  if (iVar5 == 0) {
    iVar5 = FUN_00450f84(param_1);
    if (iVar5 == 0) {
      iVar5 = FUN_00450de0(param_1);
      if (iVar5 == 0) {
        bVar3 = false;
        do {
          iVar4 = FUN_00450da4(4);
          if (iVar4 == 0) {
            if ((*(byte *)(DAT_0057cdf8 + 0x84) & 2) != 0) {
              local_c = &DAT_004cef10;
              local_10 = &DAT_004cf030;
              *(undefined1 *)(param_1 + 5) = 2;
              bVar3 = true;
            }
          }
          else if (iVar4 == 1) {
            if ((*(byte *)(DAT_0057cdf8 + 0x84) & 8) != 0) {
              local_c = &DAT_004cf150;
              local_10 = &DAT_004cf270;
              *(undefined1 *)(param_1 + 5) = 8;
              bVar3 = true;
            }
          }
          else if (iVar4 == 2) {
            if ((*(byte *)(DAT_0057cdf8 + 0x84) & 1) != 0) {
              local_c = &DAT_004cf390;
              local_10 = &DAT_004cf4b0;
              *(undefined1 *)(param_1 + 5) = 1;
              bVar3 = true;
            }
          }
          else if ((iVar4 == 3) && ((*(byte *)(DAT_0057cdf8 + 0x84) & 4) != 0)) {
            local_c = &DAT_004cf5d0;
            local_10 = &DAT_004cf6f0;
            *(undefined1 *)(param_1 + 5) = 4;
            bVar3 = true;
          }
        } while (!bVar3);
        local_8 = 0x48;
      }
      else {
        if (iVar4 == 1) {
          local_c = &DAT_004cebb0;
          local_10 = &DAT_004cec88;
          *(undefined1 *)(param_1 + 5) = 4;
        }
        else if (iVar4 == 2) {
          local_c = &DAT_004ce850;
          local_10 = &DAT_004ce928;
          *(undefined1 *)(param_1 + 5) = 8;
        }
        else if (iVar4 == 4) {
          local_c = &DAT_004ced60;
          local_10 = &DAT_004cee38;
          *(undefined1 *)(param_1 + 5) = 1;
        }
        else if (iVar4 == 8) {
          local_c = &DAT_004cea00;
          local_10 = &DAT_004cead8;
          *(undefined1 *)(param_1 + 5) = 2;
        }
        local_8 = 0x36;
      }
      DAT_0057e248 = (int)(char)(&DAT_004faf8d)[param_1[1] * 0x24];
      if (DAT_0057e248 == 3) {
        DAT_0057e248 = 1;
      }
      DAT_004cf854 = 0;
      iVar4 = FUN_00450de0(param_1);
      uVar7 = DAT_005649e4;
      if (iVar4 != 0) {
        uVar7 = DAT_005649e0;
      }
      uVar7 = uVar7 + (*(ushort *)*param_1 & 0x80000003);
      puVar1 = (undefined4 *)(local_10 + uVar7 * 4);
      puVar8 = (undefined4 *)(local_c + uVar7 * 4);
      while (((int)uVar7 < (int)local_8 && (uVar6 = FUN_00454c2c(*puVar8,*puVar1), 0x12 < uVar6))) {
        uVar7 = uVar7 + 1;
        puVar1 = puVar1 + 1;
        puVar8 = puVar8 + 1;
      }
      if ((int)local_8 <= (int)uVar7) {
        iVar4 = FUN_00450de0(param_1);
        if (iVar4 == 0) {
          uVar7 = DAT_005649e4 % local_8;
        }
        else {
          uVar7 = DAT_005649e0 % local_8;
        }
      }
      param_1[3] = *(undefined4 *)(local_c + uVar7 * 4);
      param_1[4] = *(undefined4 *)(local_10 + uVar7 * 4);
      if ((((&DAT_004faf87)[param_1[1] * 0x24] == '\x03') ||
          ((&DAT_004faf87)[param_1[1] * 0x24] == '\r')) && (*(char *)(DAT_0057cdf8 + 0xd) != '\0'))
      {
        cVar2 = *(char *)(param_1 + 5);
        if (cVar2 == '\x01') {
          param_1[4] = param_1[4] + 5;
        }
        else if (cVar2 == '\x02') {
          param_1[3] = param_1[3] + -5;
        }
        else if (cVar2 == '\x04') {
          param_1[4] = param_1[4] + -5;
        }
        else if (cVar2 == '\b') {
          param_1[3] = param_1[3] + 5;
        }
      }
    }
    else if (iVar4 == 1) {
      param_1[3] = 9;
      param_1[4] = 0xffffff81;
      *(undefined1 *)(param_1 + 5) = 4;
    }
    else if (iVar4 == 2) {
      param_1[3] = 0x7f;
      param_1[4] = 9;
      *(undefined1 *)(param_1 + 5) = 8;
    }
    else if (iVar4 == 4) {
      param_1[3] = 9;
      param_1[4] = 0x7f;
      *(undefined1 *)(param_1 + 5) = 1;
    }
    else if (iVar4 == 8) {
      param_1[3] = 0xffffff81;
      param_1[4] = 9;
      *(undefined1 *)(param_1 + 5) = 2;
    }
  }
  else {
    do {
      do {
        iVar4 = FUN_00450da4(0x24);
        param_1[3] = iVar4 + -9;
        iVar4 = FUN_00450da4(0x24);
        param_1[4] = iVar4 + -9;
        iVar4 = FUN_004511a4(param_1[3],iVar4 + -9);
      } while (iVar4 == 0);
      if ((((int)param_1[3] < 0x12) && (-1 < (int)param_1[3])) &&
         (((int)param_1[4] < 0x12 && (-1 < (int)param_1[4])))) {
        bVar3 = true;
      }
      else {
        bVar3 = false;
      }
    } while ((((*(char *)(DAT_0057cdf8 + 0xd) == '\0') || (bVar3)) &&
             ((*(char *)(DAT_0057cdf8 + 0xd) != '\0' || (!bVar3)))) ||
            ((*(char *)(*(int *)(DAT_0057cdf8 + 4) + 0x21) == '\x04' &&
             (((int)param_1[3] < 0 || ((int)param_1[4] < 0))))));
  }
  return;
}

