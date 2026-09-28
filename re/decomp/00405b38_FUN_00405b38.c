// FUN_00405b38 @ 00405b38 size=539 sig=undefined FUN_00405b38() cc=unknown
// callers: FUN_00408a88
// callees: FUN_0044b5bc,FUN_004107ec,FUN_00484ea4,FUN_00484ebc,FUN_00484ee0,FUN_0040917c,FUN_00410558,FUN_00408288,FUN_0046b074,FUN_004100e0,FUN_0046b0e4

void FUN_00405b38(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int *local_1c;
  int local_10;
  int local_c;
  int *local_8;
  
  iVar6 = 0;
  do {
    if (*(int *)(&DAT_00522584 + param_1 * 0x2648 + iVar6 * 0xc4) != 0) {
      FUN_004100e0(param_1,1,(int)(char)(&DAT_0059f219)[param_1 * 0x2d8],iVar6,0);
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x32);
  iVar6 = 0;
  do {
    if (((&DAT_00645376)[iVar6 * 0x5c] != '\0') && (param_1 == (char)(&DAT_00645378)[iVar6 * 0x5c]))
    {
      FUN_004107ec(param_1,1,(int)(char)(&DAT_0059f219)[param_1 * 0x2d8],
                   (&DAT_00645370)[iVar6 * 0x2e],0);
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x230);
  local_8 = &DAT_00521bb4;
  do {
    iVar6 = *local_8;
    local_c = 1;
    do {
      iVar2 = FUN_0044b5bc(iVar6,local_c);
      if (iVar2 != 0) {
        iVar3 = FUN_00484ea4(iVar2);
        while (iVar3 != 0) {
          uVar8 = 0;
          uVar7 = 0xffffffff;
          cVar1 = FUN_00484ee0(iVar2);
          FUN_00410558(param_1,1,(int)(char)(&DAT_0059f219)[param_1 * 0x2d8],
                       (int)*(short *)(iVar6 + 0x1a),(int)cVar1,uVar7,uVar8);
          iVar3 = FUN_00484ebc(iVar2);
        }
      }
      local_c = local_c + 1;
    } while (local_c < 6);
    local_10 = 0;
    local_1c = (int *)(iVar6 + 0x154);
    do {
      iVar2 = *local_1c;
      if (iVar2 != 0) {
        iVar3 = FUN_00408288(param_1,(int)*(char *)(iVar2 + 0xe),
                             (int)(char)(&DAT_0059f1bf)
                                        [*(char *)(iVar2 + 0xe) * 0x5a + param_1 * 0x2d8],
                             (int)*(short *)(iVar6 + 0x1a),(int)*(char *)(iVar2 + 7),0);
        if ((*(char *)(iVar2 + 5) == '\x12') &&
           (iVar4 = FUN_0040917c(param_1,(int)*(short *)(iVar2 + 8),(int)*(char *)(iVar2 + 4)),
           iVar4 != *(char *)(iVar2 + 4))) {
          *(undefined4 *)(iVar3 + 8) = 100000;
        }
        iVar4 = FUN_0046b0e4(iVar6);
        if ((iVar4 * 9) / 10 <= (int)*(short *)(iVar6 + 0x30)) {
          iVar4 = FUN_0046b0e4(iVar6);
          iVar5 = FUN_0046b074(iVar6);
          if ((iVar4 != iVar5) && (*(char *)(iVar2 + 5) == '\x11')) {
            *(undefined4 *)(iVar3 + 8) = 100000;
          }
        }
      }
      local_10 = local_10 + 1;
      local_1c = local_1c + 0xd;
    } while (local_10 < 0x24);
    local_8 = (int *)local_8[1];
  } while (local_8 != &DAT_00521bb4);
  return;
}

