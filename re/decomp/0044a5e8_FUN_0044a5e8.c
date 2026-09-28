// FUN_0044a5e8 @ 0044a5e8 size=326 sig=undefined FUN_0044a5e8() cc=unknown
// callers: @BackWndProc$qqspvuiuil
// callees: FUN_0045e398,FUN_0044930c,FUN_00418e00,FUN_00449dec,FUN_0045e13c,FUN_00449f5c,FUN_0045e0b4,FUN_0045e1c0

void FUN_0044a5e8(uint param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_0044930c();
  if (iVar2 == 0) {
    switch(param_1 & 0xffff) {
    case 0:
      FUN_0045e398(0,1);
      break;
    case 1:
      FUN_0045e398(1,1);
      break;
    case 2:
      FUN_0045e398(0,DAT_005644d8);
      break;
    case 3:
      FUN_0045e398(1,DAT_005644d8);
      break;
    case 4:
    case 5:
      if ((DAT_004d59b4 == 0) || ((DAT_004d59b4 == 0x22 && (cVar1 = FUN_00418e00(), cVar1 != '\0')))
         ) {
        if (DAT_004d5ad0 == 0) {
          FUN_0045e0b4(param_1 >> 0x10,DAT_004c5b58);
        }
        else {
          FUN_0045e13c((param_1 >> 0x10) + DAT_00559dd8,DAT_004c4a5c);
        }
      }
      else if ((DAT_004d59b4 == 1) ||
              ((DAT_004d59b4 == 0x22 && (cVar1 = FUN_00418e00(), cVar1 == '\0')))) {
        FUN_0045e1c0(param_1 >> 0x10,DAT_004dcc28);
      }
      if (((DAT_004d59b4 == 0) || (DAT_004d59b4 == 1)) || (DAT_004d59b4 == 0x22)) {
        FUN_00449dec();
        FUN_00449f5c();
      }
      break;
    case 6:
      FUN_0045e398(0,DAT_005644e4);
      break;
    case 7:
      FUN_0045e398(1,DAT_005644e4);
    }
  }
  return;
}

