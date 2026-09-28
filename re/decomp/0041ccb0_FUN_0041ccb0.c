// FUN_0041ccb0 @ 0041ccb0 size=1237 sig=undefined FUN_0041ccb0() cc=unknown
// callers: FUN_0045b8e8
// callees: sprintf,FUN_00414f04,FUN_00482b38,FUN_004493dc,FUN_004a3de6,FUN_0044eb4c,FUN_004a2004,FUN_0049eb44,FUN_004023dc,FUN_0041c814,FUN_00449f5c,FUN_0041bd60,FUN_00482cec
// strings: \"%s Production\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041ccb0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_104 [256];
  
  DAT_0053b850 = param_1;
  DAT_004b7758 = FUN_004a3de6(0,0x34303044);
  if (DAT_004b7758 == 0) {
    uVar1 = 0;
  }
  else {
    DAT_004d59a4 = 1;
    FUN_004493dc(1);
    DAT_0053b344 = DAT_004d59b4;
    DAT_004d59b4 = 5;
    FUN_00449f5c();
    FUN_00414f04(DAT_004b7758);
    FUN_004a2004(DAT_004b7758);
    FUN_0049eb44(DAT_004b7758,0x1e,1,0x34,1,0);
    FUN_0049eb44(DAT_004b7758,7,1,7,0,FUN_0041b608);
    FUN_0049eb44(DAT_004b7758,10,1,7,0,FUN_0041be6c);
    FUN_0049eb44(DAT_004b7758,0xd,1,7,0,FUN_0041be6c);
    FUN_0049eb44(DAT_004b7758,0x10,1,7,0,FUN_0041be6c);
    FUN_0049eb44(DAT_004b7758,0x13,1,7,0,FUN_0041be6c);
    FUN_0049eb44(DAT_004b7758,0x16,1,7,0,FUN_0041be6c);
    FUN_0049eb44(DAT_004b7758,0x19,1,7,0,FUN_0041be6c);
    iVar2 = 1000;
    do {
      FUN_0049eb44(DAT_004b7758,iVar2,1,7,0,FUN_0041b330);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x3f2);
    FUN_0049eb44(DAT_004b7758,0x2c,1,7,0,FUN_00414b10);
    FUN_0049eb44(DAT_004b7758,6,1,0x42,0,DAT_004d5b1c + 0x406);
    FUN_0049eb44(DAT_004b7758,8,1,0xb,DAT_004c48a4 != 0,0);
    FUN_0049eb44(DAT_004b7758,1,1,7,0,FUN_0041c258);
    _DAT_0053b848 = (int)*(char *)(DAT_0053b850 + 7);
    DAT_0053b84c = &DAT_005a43d0 + *(short *)(DAT_0053b850 + 8) * 0xadc;
    iVar2 = FUN_004023dc(param_1,5);
    if (iVar2 == -1) {
      FUN_0049eb44(DAT_004b7758,0x2b,1,0x3c,0,1);
      FUN_0049eb44(DAT_004b7758,0x2a,1,0x3c,0,1);
    }
    else {
      FUN_0049eb44(DAT_004b7758,0x2b,1,7,0,FUN_00414bd8);
    }
    DAT_0053b33c = (int)*(short *)(param_1 + 2) & 4;
    if (DAT_0053b33c == 0) {
      FUN_0049eb44(DAT_004b7758,0x1a,1,0xb,0,0);
    }
    else {
      FUN_0049eb44(DAT_004b7758,0x1a,1,0xb,1,0);
    }
    sprintf(local_104,PTR_s__s_Production_00509238,
            *(undefined4 *)(&DAT_004f9dbc + *(char *)(param_1 + 4) * 0x32));
    if ((*(byte *)(DAT_0053b850 + 3) & 1) == 0) {
      FUN_0049eb44(DAT_004b7758,0xb,1,0xb,0,0);
    }
    else {
      FUN_0049eb44(DAT_004b7758,0xb,1,0xb,1,0);
    }
    if ((*(byte *)(DAT_0053b850 + 3) & 2) == 0) {
      FUN_0049eb44(DAT_004b7758,0xe,1,0xb,0,0);
    }
    else {
      FUN_0049eb44(DAT_004b7758,0xe,1,0xb,1,0);
    }
    if ((*(byte *)(DAT_0053b850 + 3) & 4) == 0) {
      FUN_0049eb44(DAT_004b7758,0x11,1,0xb,0,0);
    }
    else {
      FUN_0049eb44(DAT_004b7758,0x11,1,0xb,1,0);
    }
    if ((*(byte *)(DAT_0053b850 + 3) & 8) == 0) {
      FUN_0049eb44(DAT_004b7758,0x14,1,0xb,0,0);
    }
    else {
      FUN_0049eb44(DAT_004b7758,0x14,1,0xb,1,0);
    }
    if ((*(byte *)(DAT_0053b850 + 3) & 0x10) == 0) {
      FUN_0049eb44(DAT_004b7758,0x17,1,0xb,0,0);
    }
    else {
      FUN_0049eb44(DAT_004b7758,0x17,1,0xb,1,0);
    }
    if ((&DAT_004f9dc3)[*(char *)(DAT_0053b850 + 4) * 0x32] != '\a') {
      FUN_0049eb44(DAT_004b7758,5,1,0x3c,0,1);
    }
    FUN_0044eb4c(PTR_DAT_004d5988,DAT_0053b84c,_DAT_0053b848,&DAT_0053b854,0);
    if ((((DAT_0053b33c != 0) && ((*(byte *)(DAT_0053b850 + 2) & 2) != 0)) &&
        ((&DAT_004f9dc8)[*(char *)(DAT_0053b850 + 4) * 0x32] == '\0')) &&
       (*(char *)(DAT_0053b850 + 4) != 0x24)) {
      FUN_0049eb44(DAT_004b7758,0x1a,1,10,1,0);
    }
    DAT_0053b874 = DAT_004c5450;
    DAT_004c5450 = 0;
    FUN_0041c814();
    FUN_0041bd60(_DAT_0053b340);
    if (*(short *)(DAT_0053b850 + 0x14) < 1) {
      DAT_004b775c = *(int *)(&DAT_004f9dea + *(char *)(DAT_0053b850 + 4) * 0x32);
    }
    else {
      DAT_004b775c = 6;
    }
    if (DAT_004b775c != -1) {
      FUN_00482cec();
      FUN_00482b38(4,DAT_004b775c);
    }
    DAT_004d59a4 = 0;
    uVar1 = 1;
  }
  return uVar1;
}

