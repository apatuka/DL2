// FUN_00454690 @ 00454690 size=661 sig=undefined FUN_00454690() cc=unknown
// callers: FUN_00454928
// callees: FUN_00453a38,FUN_00447c2c,FUN_00450f84,FUN_004538b4,FUN_0043d594,FUN_00447da4,FUN_00451180,FUN_00453350,FUN_00453210,FUN_00453568,FUN_00445040

void FUN_00454690(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char cVar6;
  uint local_10;
  int local_c;
  int local_8;
  
  iVar1 = *(int *)(param_1 + 0x3c);
  if (((iVar1 == 0) && (*(int *)(param_1 + 0x40) == 0)) && (*(int *)(param_1 + 0x24) == 0x7f)) {
    local_10 = 0;
    for (iVar1 = *(int *)(DAT_0057cdf8 + 0x74); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x44)) {
      iVar5 = FUN_00450f84(iVar1);
      if (iVar5 != 0) {
        local_10 = local_10 + 1;
      }
    }
    for (DAT_005649dc = 0; DAT_005649dc < local_10; DAT_005649dc = DAT_005649dc + 1) {
      if ((*(char *)(param_1 + 9) != '\0') && (iVar1 = FUN_00453a38(param_1,0), iVar1 != -1)) {
        DAT_0057e244 = 9999;
        return;
      }
      iVar5 = 0;
      for (iVar1 = *(int *)(DAT_0057cdf8 + 0x74); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x44)) {
        if (((*(char *)(iVar1 + 0x1d) != '\0') &&
            (*(char *)(iVar1 + 0x1e) != *(char *)(param_1 + 0x1e))) &&
           (iVar2 = FUN_004538b4(iVar1), iVar2 == 0)) {
          iVar2 = FUN_00447da4(iVar1);
          iVar2 = iVar2 - *(short *)(iVar1 + 0x32);
          if (iVar5 < iVar2) {
            *(int *)(param_1 + 0x3c) = iVar1;
            iVar5 = iVar2;
          }
        }
      }
      if (*(int *)(param_1 + 0x3c) != 0) {
        DAT_0057e244 = 9999;
        return;
      }
    }
    *(undefined4 *)(param_1 + 0x24) = 0x20;
    DAT_0057e244 = 9999;
  }
  else {
    if (iVar1 == 0) {
      if (*(int *)(param_1 + 0x40) == 0) {
        local_c = 9;
        local_8 = *(int *)(param_1 + 0x20);
      }
      else {
        FUN_00453210(*(int *)(param_1 + 0x40),*(undefined4 *)(param_1 + 0x20),
                     *(undefined4 *)(param_1 + 0x24),&local_8,&local_c);
      }
    }
    else {
      local_8 = *(int *)(iVar1 + 0x20);
      local_c = *(int *)(*(int *)(param_1 + 0x3c) + 0x24);
    }
    if (*(int *)(param_1 + 0x24) == 0x7f) {
      *(undefined4 *)(param_1 + 0x24) = 0x20;
      *(int *)(param_1 + 0x20) = local_8;
    }
    if (local_c < *(int *)(param_1 + 0x24)) {
      if (((DAT_004cf850 != 0) && (iVar1 = FUN_00451180(param_1,local_8,local_c), iVar1 < 0x11)) &&
         ((*(int *)(param_1 + 0x38) != 0 && (*(short *)(*(int *)(param_1 + 0x38) + 0x2c) == 0)))) {
        FUN_00445040(*(undefined4 *)(param_1 + 0x38),1,1);
      }
      DAT_0057e244 = 9999;
    }
    else {
      FUN_00453350(param_1,0x7f,0);
      iVar1 = FUN_00447c2c(param_1);
      if (*(int *)(param_1 + 0x3c) == 0) {
        if (*(int *)(param_1 + 0x40) != 0) {
          FUN_00453568(*(int *)(param_1 + 0x40),iVar1,param_1);
        }
      }
      else {
        FUN_00453350(*(int *)(param_1 + 0x3c),iVar1,0);
      }
      for (iVar5 = *(int *)(DAT_0057cdf8 + 0x74); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x44)) {
        if (((param_1 != iVar5) && (iVar5 != *(int *)(param_1 + 0x3c))) &&
           ((uVar3 = *(int *)(iVar5 + 0x20) - local_8, uVar4 = (int)uVar3 >> 0x1f,
            (int)((uVar3 ^ uVar4) - uVar4) < 2 &&
            ((uVar3 = *(int *)(iVar5 + 0x24) - local_c, uVar4 = (int)uVar3 >> 0x1f,
             (int)((uVar3 ^ uVar4) - uVar4) < 2 &&
             ((&DAT_004faf8d)[*(int *)(iVar5 + 4) * 0x24] != '\x03')))))) {
          FUN_00453350(iVar5,iVar1 / 2,0);
        }
      }
      if (DAT_004cf850 != 0) {
        for (iVar1 = local_c + -1; iVar1 <= local_c + 1; iVar1 = iVar1 + 1) {
          for (iVar5 = local_8 + -1; iVar5 <= local_8 + 1; iVar5 = iVar5 + 1) {
            cVar6 = iVar1 == local_c;
            if (iVar5 == local_8) {
              cVar6 = cVar6 + '\x01';
            }
            FUN_0043d594(iVar5,iVar1,cVar6);
          }
        }
      }
    }
  }
  return;
}

