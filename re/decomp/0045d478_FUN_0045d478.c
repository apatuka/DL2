// FUN_0045d478 @ 0045d478 size=440 sig=undefined FUN_0045d478() cc=unknown
// callers: FUN_0044a9b8
// callees: FUN_00418d18,FUN_0045e274,FUN_00418cf4,FUN_00459068,FUN_0045d418,FUN_00481a5c,FUN_00437134,FUN_00419c08,FUN_00418e00,FUN_00449d54,FUN_00421828

void FUN_0045d478(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int local_c;
  int local_8;
  
  FUN_00459068();
  FUN_00481a5c(param_1,param_2,&local_8,&local_c);
  if ((short)(&DAT_005a0552)[local_c * 200 + local_8 * 5] == DAT_00583d88) {
    if (DAT_004d59b4 < 8) {
      if (DAT_004d59b4 == 7) {
        FUN_00421828(&DAT_005a43d0 + DAT_00583d88 * 0xadc,local_8,local_c);
        FUN_0045d418();
        return;
      }
      if (DAT_004d59b4 == 0) {
        FUN_0045e274(local_8,local_c);
        FUN_0045d418();
      }
      else if (DAT_004d59b4 == 1) {
        if ((char)(&DAT_005a4436)[DAT_0058f1f4 + DAT_00583d88 * 0xadc] < '\x03') {
          return;
        }
        FUN_00449d54(DAT_00583d88);
        FUN_0045d418();
      }
    }
    else if (DAT_004d59b4 == 0xb) {
      iVar2 = FUN_00437134(local_8,local_c);
      if (iVar2 == 0) {
        return;
      }
      FUN_0045d418();
    }
    else if (DAT_004d59b4 == 0x22) {
      cVar1 = FUN_00418e00();
      if (cVar1 == '\0') {
        if ((char)(&DAT_005a4436)[DAT_0058f1f4 + DAT_00583d88 * 0xadc] < '\x03') {
          return;
        }
        FUN_00449d54(DAT_00583d88);
      }
      else {
        FUN_0045e274(local_8,local_c);
      }
      FUN_00419c08(&DAT_005a43d0 + DAT_00583d88 * 0xadc);
      FUN_0045d418();
      FUN_00418d18();
      FUN_00418cf4();
    }
  }
  DAT_00583d94 = 0xffffffff;
  DAT_00583d90 = 0xffffffff;
  DAT_00583d8c = 0xffffffff;
  DAT_00583d88 = 0xffffffff;
  return;
}

