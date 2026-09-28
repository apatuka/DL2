// FUN_00427440 @ 00427440 size=1043 sig=undefined FUN_00427440() cc=unknown
// callers: FUN_00427a6c
// callees: FUN_00426f20,FUN_0048e319,FUN_00481a5c,FUN_00427100,FUN_004a26e8,FUN_00427278,FUN_0048e1d5,FUN_00475344,FUN_0042726c,FUN_00477070,FUN_00426594,FUN_0048e169,FUN_0048db5d,FUN_0044b518,FUN_0048e385,FUN_004a2cb5,FUN_0048e2ad,FUN_0048e241,FUN_004775c8,FUN_0044b544

undefined4 FUN_00427440(void)

{
  int iVar1;
  int local_18;
  int local_14;
  int local_10;
  undefined1 local_c [4];
  undefined4 local_8;
  undefined4 local_4;
  
  if ((DAT_004b7d34 != 0) && (DAT_00557578 == 0)) {
    if (DAT_004d8264 == 0) {
      FUN_00426f20();
      DAT_004d59a4 = 1;
      DAT_0051b824 = 1;
      FUN_0048db5d(0);
      FUN_004a26e8(DAT_004c36ac);
      FUN_0042726c();
      iVar1 = FUN_0048e1d5(1,&local_14,&local_10,local_c);
      if (iVar1 == 0) {
        iVar1 = FUN_0048e385(1,&local_14,&local_10,local_c);
        if (iVar1 == 0) {
          iVar1 = FUN_0048e1d5(2,&local_14,&local_10,local_c);
          if (iVar1 == 0) {
            iVar1 = FUN_0048e2ad(2,&local_14,&local_10,local_c);
            if ((iVar1 != 0) && (DAT_00557794 != 0)) {
              FUN_0048e241(2,&local_14,&local_10,local_c);
              FUN_0044b518();
              DAT_00557794 = 0;
              FUN_00427278();
              FUN_0042726c();
            }
          }
          else if ((((DAT_004b7d4c <= local_14) && (local_14 <= DAT_004b7d54)) &&
                   (DAT_004b7d48 <= local_10)) && (local_10 <= DAT_004b7d50)) {
            FUN_0048e169(2,&local_14,&local_10,local_c);
            DAT_00557794 = 1;
            FUN_0044b544();
          }
        }
        else if (((DAT_004b7d4c <= local_14) && (local_14 <= DAT_004b7d54)) &&
                ((DAT_004b7d48 <= local_10 && (local_10 <= DAT_004b7d50)))) {
          FUN_0048e319(1,&local_14,&local_10,local_c);
          FUN_00481a5c(local_14 - DAT_004b7d4c,local_10 - DAT_004b7d48,&local_8,&local_4);
          FUN_00427100(local_8,local_4);
          if (DAT_004d5aa0 == '\0') {
            if (DAT_0058f1f4 == DAT_00557788) {
              FUN_004775c8(DAT_0058f1f4,DAT_00557790);
            }
          }
          else {
            FUN_004775c8(DAT_00557788,DAT_00557790);
          }
        }
      }
      else if (((DAT_004b7d4c <= local_14) && (local_14 <= DAT_004b7d54)) &&
              ((DAT_004b7d48 <= local_10 && (local_10 <= DAT_004b7d50)))) {
        FUN_0048e169(1,&local_14,&local_10,local_c);
        FUN_00481a5c(local_14 - DAT_004b7d4c,local_10 - DAT_004b7d48,&local_8,&local_4);
        FUN_00427100(local_8,local_4);
      }
      iVar1 = FUN_004a2cb5(DAT_004b7d34,&local_18);
      if (((iVar1 == 0) && (local_18 != 0)) && (*(int *)(DAT_004b7d34 + 100) == 0)) {
        if (local_18 == 2) {
          FUN_00426594(&DAT_004d2a84 + (char)(&DAT_005a43f1)[DAT_00557790 * 0xadc] * 0x24);
        }
        else if (local_18 == 3) {
          if (DAT_004d5aa0 == '\0') {
            if (DAT_0058f1f4 == DAT_00557788) {
              FUN_004775c8(DAT_0058f1f4,DAT_00557790);
            }
          }
          else {
            FUN_004775c8(DAT_00557788,DAT_00557790);
          }
        }
        else {
          if (local_18 == 4) {
            if (DAT_0058f1fc != 0) {
              FUN_00475344();
            }
            DAT_00557578 = 1;
            DAT_0058f1ec = 1;
            return 0;
          }
          if (local_18 == 5) {
            if (DAT_0058f1fc != 0) {
              FUN_00477070();
              return 0;
            }
            DAT_004d5a7c = 0;
            DAT_00557578 = 1;
            return 0;
          }
        }
      }
      DAT_004d59a4 = 0;
    }
    else {
      DAT_0058f1ec = 1;
      DAT_00557578 = 1;
    }
  }
  return 0;
}

