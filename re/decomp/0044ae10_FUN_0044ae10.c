// FUN_0044ae10 @ 0044ae10 size=547 sig=undefined FUN_0044ae10() cc=unknown
// callers: @BackWndProc$qqspvuiuil
// callees: FUN_00421584,FUN_00458f14,FUN_0045cff4,FUN_00463d00,FUN_00449cc4,FUN_00463da8,FUN_00494d38,FUN_0044930c,FUN_00418e00,FUN_0045cd88,FUN_0041a14c,FUN_0041e1fc

int FUN_0044ae10(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_00494d38();
  uVar3 = param_3 & 0xffff;
  param_3 = param_3 >> 0x10;
  iVar1 = FUN_00458f14(uVar3,param_3);
  if (((iVar1 == 0) && (iVar1 = FUN_0044930c(), iVar1 == 0)) && (DAT_004c5bc8 != '\0')) {
    FUN_00463da8(1);
    FUN_00463d00(0,0,DAT_0058f1c0,DAT_0058f1c4);
    iVar2 = FUN_00449cc4(uVar3,param_3,&local_8,&local_c);
    iVar1 = iVar2;
    if (iVar2 != -1) {
      iVar1 = DAT_004d59b4;
      if (iVar2 < 8) {
        if (iVar2 == 0) {
          if ((DAT_004d59b4 == 0) ||
             ((DAT_004d59b4 == 0x22 && (iVar1 = FUN_00418e00(), (char)iVar1 != '\0')))) {
            if ((DAT_00583d84 != '\0') &&
               ((DAT_00583d90 != 0 ||
                (((iVar1 = 0, DAT_004d59b4 == 0x22 && (iVar1 = FUN_00418e00(), (char)iVar1 != '\0'))
                 && (DAT_00583d64 != 0)))))) {
              iVar1 = FUN_0045cff4(uVar3,param_3,local_8,local_c,param_2);
              DAT_00583d84 = '\0';
            }
          }
          else if ((DAT_004d59b4 + -1 == 0) ||
                  ((iVar1 = DAT_004d59b4 + -1, DAT_004d59b4 == 0x22 &&
                   (iVar1 = FUN_00418e00(), (char)iVar1 == '\0')))) {
            iVar1 = FUN_0045cd88(uVar3,param_3,local_8,local_c,param_2);
            DAT_004c5bc8 = '\0';
          }
        }
        else {
          iVar1 = iVar2 + -8;
          if (iVar2 - 2U < 6) {
            iVar1 = FUN_0041e1fc(uVar3,param_3,local_8,local_c,param_2);
            DAT_004c5bc8 = '\0';
          }
        }
      }
      else if (iVar2 - 8U < 4) {
        if (DAT_004d59b4 == 5) {
          iVar1 = FUN_0041e1fc(uVar3,param_3,local_8,local_c,param_2);
          DAT_004c5bc8 = '\0';
        }
        else if (DAT_004d59b4 == 7) {
          iVar1 = FUN_00421584(uVar3,param_3,local_8,local_c,param_2);
          DAT_004c5bc8 = '\0';
        }
      }
      else if (iVar2 - 0xdU < 3) {
        iVar1 = FUN_0041a14c(uVar3,param_3,local_8,local_c,param_2);
        DAT_004c5bc8 = '\0';
      }
      else {
        iVar1 = iVar2 + -0x28;
        if (iVar2 - 0x10U < 0x18) {
          iVar1 = FUN_00421584(uVar3,param_3,local_8,local_c,param_2);
          DAT_004c5bc8 = '\0';
        }
      }
    }
  }
  return iVar1;
}

