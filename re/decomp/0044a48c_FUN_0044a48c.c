// FUN_0044a48c @ 0044a48c size=316 sig=undefined FUN_0044a48c() cc=unknown
// callers: @BackWndProc$qqspvuiuil
// callees: FUN_0045e398,FUN_0044930c,FUN_00418e00,FUN_00449dec,FUN_0045e13c,FUN_00449f5c,FUN_0045e0b4,FUN_0045e1c0

void FUN_0044a48c(uint param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_0044930c();
  if (iVar2 != 0) {
    return;
  }
  if (DAT_004d59b4 != 0) {
    if (DAT_004d59b4 == 1) {
      if (((short)param_1 == 4) || ((short)param_1 == 5)) {
        FUN_0045e1c0(DAT_004dcc24,param_1 >> 0x10);
      }
      goto switchD_0044a4cf_default;
    }
    if ((DAT_004d59b4 != 0x22) || (cVar1 = FUN_00418e00(), cVar1 == '\0'))
    goto switchD_0044a4cf_default;
  }
  switch(param_1 & 0xffff) {
  case 0:
    FUN_0045e398(2,1);
    break;
  case 1:
    FUN_0045e398(3,1);
    break;
  case 2:
    FUN_0045e398(2,DAT_005644dc);
    break;
  case 3:
    FUN_0045e398(3,DAT_005644dc);
    break;
  case 4:
  case 5:
    if (DAT_004d5ad0 == 0) {
      FUN_0045e0b4(DAT_004c5b54,param_1 >> 0x10);
    }
    else {
      FUN_0045e13c(DAT_004c4a58,param_1 >> 0x10);
    }
    break;
  case 6:
    FUN_0045e398(2,DAT_005644e0);
    break;
  case 7:
    FUN_0045e398(3,DAT_005644e0);
  }
switchD_0044a4cf_default:
  if ((((DAT_004d59b4 == 0) || (DAT_004d59b4 == 1)) || (DAT_004d59b4 == 0x22)) ||
     (DAT_004d59b4 == 3)) {
    FUN_00449dec();
    FUN_00449f5c();
  }
  return;
}

