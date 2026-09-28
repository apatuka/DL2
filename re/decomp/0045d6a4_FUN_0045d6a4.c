// FUN_0045d6a4 @ 0045d6a4 size=502 sig=undefined FUN_0045d6a4() cc=unknown
// callers: FUN_0044b034
// callees: FUN_00449fe8,FUN_0045ad98,FUN_00481a5c,FUN_00419c08,FUN_00418e00,FUN_00449fd8,FUN_00418d18,FUN_00418cf4,FUN_0045dfd4,FUN_00449f5c,FUN_00449d54,FUN_0045df3c,FUN_00449dec

void FUN_0045d6a4(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int local_c;
  int local_8;
  
  FUN_00481a5c(param_1,param_2,&local_8,&local_c);
  iVar2 = DAT_00583d8c;
  iVar1 = DAT_004c5b50;
  iVar4 = (int)(short)(&DAT_005a0552)[local_c * 200 + local_8 * 5];
  if (iVar4 == DAT_00583d8c) {
    if (DAT_004d59b4 == 0) {
      (&DAT_005a43ec)[DAT_00583d8c * 0x2b7] = (&DAT_005a43ec)[DAT_00583d8c * 0x2b7] | 1;
      FUN_0045dfd4(iVar2,1);
      FUN_0045df3c(iVar1);
      FUN_0045df3c(DAT_004c5b50);
      FUN_0045ad98(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
      FUN_00449fd8();
      FUN_00449fe8();
      FUN_00449dec();
      FUN_00449f5c();
    }
    else if ((DAT_004d59b4 == 1) &&
            ('\x02' < (char)(&DAT_005a4436)[DAT_0058f1f4 + DAT_00583d8c * 0xadc])) {
      FUN_00449d54(iVar4);
    }
    else if (DAT_004d59b4 == 0x22) {
      cVar3 = FUN_00418e00();
      iVar1 = DAT_004c5b50;
      if (cVar3 == '\0') {
        if ((char)(&DAT_005a4436)[DAT_0058f1f4 + DAT_00583d8c * 0xadc] < '\x03') {
          return;
        }
        FUN_00449d54(iVar4);
      }
      else {
        (&DAT_005a43ec)[DAT_00583d8c * 0x2b7] = (&DAT_005a43ec)[DAT_00583d8c * 0x2b7] | 1;
        FUN_0045dfd4(DAT_00583d8c,1);
        FUN_0045df3c(iVar1);
        FUN_0045df3c(DAT_004c5b50);
        FUN_0045ad98(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
      }
      FUN_00419c08(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
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

