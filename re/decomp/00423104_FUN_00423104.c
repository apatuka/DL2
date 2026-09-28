// FUN_00423104 @ 00423104 size=635 sig=undefined FUN_00423104() cc=unknown
// callers: FUN_00423904
// callees: FUN_00422bd8,FUN_004152e0,FUN_004a3de6,FUN_004225ec,sprintf,FUN_004a2004,UpdateWindow,FUN_004493dc,FUN_004229f4,FUN_00422344,FUN_00414f04,FUN_0049eb44,FUN_00421efc,FUN_004a60b1,FUN_00422cd4,FUN_00422d04
// strings: \"%s  %d\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00423104(void)

{
  char cVar1;
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined4 local_204;
  undefined1 local_200 [256];
  undefined1 local_100 [256];
  
  DAT_004b7b50 = FUN_004a3de6(0,0x35303944);
  if (DAT_004b7b50 != 0) {
    FUN_004152e0();
    UpdateWindow(DAT_004d5974);
    FUN_004493dc(1);
    DAT_005574f0 = DAT_004d59b4;
    DAT_004d59b4 = 9;
    DAT_004b7b40 = 1;
    DAT_004d59b8 = 0;
    FUN_00414f04(DAT_004b7b50);
    local_210 = 0;
    local_20c = 0;
    local_208 = 0x280;
    local_204 = 0x1e0;
    FUN_004a60b1(&local_210,0);
    FUN_00422cd4();
    FUN_00422d04();
    FUN_0049eb44(DAT_004b7b50,3,1,7,0,FUN_00421fc4);
    FUN_004a2004(DAT_004b7b50);
    if ((DAT_00540ce0 == '\0') || (cVar1 = FUN_00421efc(), cVar1 == '\0')) {
      DAT_0053b8cc = '\0';
    }
    else {
      DAT_0053b8cc = '\x01';
    }
    if (DAT_0053b8cc == '\0') {
      FUN_0049eb44(DAT_004b7b50,4,1,0xb,0,0);
    }
    else {
      FUN_0049eb44(DAT_004b7b50,4,1,0xb,1,0);
    }
    DAT_004b7b44 = 0;
    _DAT_004b7b48 = 0;
    FUN_004229f4();
    FUN_0049eb44(DAT_004b7b50,0x10,1,0xe,0xff,local_200);
    sprintf(local_100,s__s__d_004b7bd8,local_200,DAT_0059f154);
    FUN_0049eb44(DAT_004b7b50,0x10,1,0xf,0,local_100);
    FUN_00422bd8(DAT_004b7b44);
    local_20c = 0x53;
    local_210 = 0x10;
    local_204 = 0x11b;
    local_208 = 0xd8;
    FUN_0049eb44(DAT_004b7b50,
                 *(undefined4 *)(&DAT_004b7b68 + (char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] * 4),1,
                 0xd,0,&local_210);
    FUN_0049eb44(DAT_004b7b50,2,1,0xf,0,&DAT_004b7b84);
    DAT_0053c4dc = 0;
    FUN_0049eb44(DAT_004b7b50,0xe,1,7,0,FUN_00422f7c);
    FUN_0049eb44(DAT_004b7b50,0xe,1,0x1c,3,0);
    FUN_0049eb44(DAT_004b7b50,0xe,1,0x1b,0,0);
    DAT_0053b8d8 = DAT_004c5450;
    DAT_004c5450 = 0;
    FUN_004225ec();
    FUN_00422344();
    return 1;
  }
  return 0;
}

