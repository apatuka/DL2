// FUN_00432ad0 @ 00432ad0 size=499 sig=undefined FUN_00432ad0() cc=unknown
// callers: CheckSubUnit,CheckSubTech
// callees: FUN_004493dc,FUN_0049eb44,FUN_00414ea4,FUN_0043239c,FUN_00432d30,FUN_00414f04,FUN_00431f58,FUN_004326b0,FUN_00432cf4,FUN_004a3de6,FUN_004a2004,FUN_00432610,FUN_00432660,FUN_0045dfb0

void FUN_00432ad0(void)

{
  char cVar1;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_004c42d8 = FUN_004a3de6(0,0x30313944);
  if (DAT_004c42d8 != 0) {
    DAT_004d59a4 = 1;
    FUN_004493dc(1);
    DAT_00558d58 = 1;
    FUN_00414f04(DAT_004c42d8);
    local_20 = 0;
    local_1c = 0;
    local_18 = 0x280;
    local_14 = 0x1e0;
    FUN_00414ea4(&local_20);
    FUN_0049eb44(DAT_004c42d8,0xe,1,7,0,FUN_00432824);
    FUN_004a2004(DAT_004c42d8);
    FUN_0049eb44(DAT_004c42d8,10,1,0xb,1,0);
    FUN_0049eb44(DAT_004c42d8,1,1,7,0,FUN_00431258);
    if ((DAT_004c42e8 == 0) ||
       ((((DAT_004d5ac4 == 0 && (DAT_004d5ab0 != 0)) && (DAT_004d5aa8 != 0)) && (DAT_004d59ac != 0))
       )) {
      FUN_0049eb44(DAT_004c42d8,3,1,0xf,0,&DAT_004c4588);
    }
    else {
      FUN_0049eb44(DAT_004c42d8,3,1,0xf,0,DAT_004c42e8);
    }
    if ((DAT_004c42e4 != 0) && (DAT_004c42ec == 0)) {
      local_10 = 10000;
      local_c = 10000;
      local_8 = 0x27d8;
      local_4 = 0x27d8;
      FUN_0049eb44(DAT_004c42d8,0xd,1,0xd,0,&local_10);
    }
    cVar1 = FUN_00431f58();
    if (cVar1 == '\0') {
      FUN_0049eb44(DAT_004c42d8,0xb,1,10,1,0);
    }
    else {
      FUN_0049eb44(DAT_004c42d8,0xb,1,10,0,0);
    }
    cVar1 = FUN_0043239c();
    if (cVar1 == '\0') {
      FUN_0049eb44(DAT_004c42d8,0xc,1,10,1,0);
    }
    else {
      FUN_0049eb44(DAT_004c42d8,0xc,1,10,0,0);
    }
    FUN_0045dfb0(6);
    FUN_00432610();
    FUN_00432660();
    FUN_004326b0();
    FUN_00432d30();
    FUN_00432cf4();
  }
  return;
}

