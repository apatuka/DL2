// FUN_00438830 @ 00438830 size=627 sig=undefined FUN_00438830() cc=unknown
// callers: FUN_00438aa4
// callees: FUN_0049eb44,FUN_004383a4,FUN_004a2004,FUN_004a60b1,FUN_004a3de6,FUN_00414f04,FUN_004493dc

undefined4 FUN_00438830(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004c46b4 = FUN_004a3de6(0,0x31303944);
  if (DAT_004c46b4 == 0) {
    uVar1 = 0;
  }
  else {
    FUN_004493dc(1);
    DAT_005594ac = DAT_004d59b4;
    DAT_004d59b4 = 0x4b;
    DAT_0055933c = &DAT_005a43d0 + DAT_004c5b50 * 0xadc;
    DAT_00559340 = 0;
    DAT_005594a8 = 0;
    FUN_00414f04(DAT_004c46b4);
    FUN_0049eb44(DAT_004c46b4,0xe,1,0xe,200,&DAT_00559341);
    FUN_004a2004(DAT_004c46b4);
    FUN_004383a4();
    local_10 = 0;
    local_c = 0;
    local_8 = 0x280;
    local_4 = 0x1e0;
    FUN_004a60b1(&local_10,0);
    FUN_0049eb44(DAT_004c46b4,5,1,7,0,FUN_00438134);
    if (DAT_00559338 == 0) {
      FUN_0049eb44(DAT_004c46b4,10,1,0x3c,0,1);
      FUN_0049eb44(DAT_004c46b4,8,1,0x3c,0,1);
      FUN_0049eb44(DAT_004c46b4,0xb,1,0x3c,0,1);
      FUN_0049eb44(DAT_004c46b4,9,1,0x3c,0,1);
    }
    else {
      if ((1 << ((byte)*(undefined4 *)(&DAT_004f9de6 + *(char *)(DAT_00559338 + 4) * 0x32) & 0x1f) &
          (int)(char)DAT_0055933c[0x9ae]) == 0) {
        FUN_0049eb44(DAT_004c46b4,10,1,0xb,1,0);
      }
      else {
        FUN_0049eb44(DAT_004c46b4,10,1,0xb,0,0);
      }
      if (DAT_005594ac == 7) {
        FUN_0049eb44(DAT_004c46b4,9,1,0x3c,0,1);
      }
      else {
        FUN_0049eb44(DAT_004c46b4,9,1,0x3c,1,1);
        if ((((*(byte *)(DAT_00559338 + 2) & 2) == 0) ||
            ((&DAT_004f9dc8)[*(char *)(DAT_00559338 + 4) * 0x32] == '\0')) ||
           (*(char *)(DAT_00559338 + 4) == '$')) {
          FUN_0049eb44(DAT_004c46b4,9,1,10,1,0);
        }
        else {
          FUN_0049eb44(DAT_004c46b4,9,1,10,0,0);
          if ((*(ushort *)(DAT_00559338 + 2) & 4) == 0) {
            FUN_0049eb44(DAT_004c46b4,9,1,0xb,0,0);
          }
          else {
            FUN_0049eb44(DAT_004c46b4,9,1,0xb,1,0);
          }
        }
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

