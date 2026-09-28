// FUN_00453c30 @ 00453c30 size=362 sig=undefined FUN_00453c30() cc=unknown
// callers: FUN_00454928,FUN_00453c30
// callees: FUN_00447c2c,FUN_00454928,FUN_00453c30,FUN_0043da00,FUN_0043da5c,FUN_00451180,FUN_00453350,FUN_00453210,FUN_00453568,FUN_00453bf4

void FUN_00453c30(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  *(undefined4 *)(param_1 + 0x3c) = 0;
  DAT_0057e244 = 9999;
  iVar1 = *(int *)(param_1 + 0x40);
  if ((iVar1 == 0) || (*(short *)(iVar1 + 0x14) <= *(short *)(iVar1 + 0xe))) {
    uVar5 = 0xffffffff;
    for (iVar1 = *(int *)(DAT_0057cdf8 + 0x7c); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x16)) {
      if ((((&DAT_004f9dc3)[*(short *)(iVar1 + 4) * 0x32] != '\x01') &&
          (*(short *)(iVar1 + 0xe) < *(short *)(iVar1 + 0x14))) &&
         (iVar3 = FUN_00453bf4(iVar1), iVar3 == 0)) {
        FUN_00453210(iVar1,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),&local_10
                     ,&local_14);
        uVar4 = FUN_00451180(param_1,local_10,local_14);
        if (uVar4 < uVar5) {
          *(int *)(param_1 + 0x40) = iVar1;
          uVar5 = uVar4;
        }
      }
    }
    if (*(int *)(param_1 + 0x40) == 0) {
      *(undefined1 *)(param_1 + 9) = 5;
      FUN_00454928(param_1,param_2);
      *(undefined1 *)(param_1 + 9) = 2;
    }
  }
  else {
    FUN_00453210(iVar1,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),&local_8,
                 &local_c);
    iVar1 = FUN_00451180(param_1,local_8,local_c);
    if (iVar1 < 3) {
      DAT_0057e244 = 0;
      if (param_2 == 0) {
        if (*(short *)(*(int *)(param_1 + 0x40) + 0x14) <=
            *(short *)(*(int *)(param_1 + 0x40) + 0xe)) {
          *(undefined4 *)(param_1 + 0x40) = 0;
          FUN_00453c30(param_1,0);
        }
      }
      else {
        iVar1 = param_1;
        uVar2 = FUN_00447c2c(param_1);
        FUN_00453568(*(undefined4 *)(param_1 + 0x40),uVar2,iVar1);
        FUN_00453350(param_1,2,0);
        if (DAT_004cf850 != 0) {
          FUN_0043da5c(param_1);
        }
      }
    }
    else if (DAT_004cf850 != 0) {
      FUN_0043da00(param_1);
    }
  }
  return;
}

