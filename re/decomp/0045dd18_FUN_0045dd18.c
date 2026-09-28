// FUN_0045dd18 @ 0045dd18 size=375 sig=undefined FUN_0045dd18() cc=unknown
// callers: FUN_0045de90,FUN_0044a92c,FUN_0044a8bc
// callees: FUN_0043edd8,FUN_0045ad98,FUN_0045dfd4,FUN_00419c08,FUN_00459ea8,FUN_0045bf78,FUN_0045bb88

void FUN_0045dd18(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int local_c;
  int local_8;
  
  if (DAT_004d5ad0 == 0) {
    FUN_00459ea8(param_1,param_2,&local_8,&local_c);
  }
  else {
    FUN_0043edd8(param_1,param_2,&local_8,&local_c);
  }
  if (((((-1 < local_8) && (local_8 < DAT_004d5b1a)) && (-1 < local_c)) &&
      ((local_c < DAT_004d5b1b &&
       ((short)(&DAT_005a0552)[local_c * 200 + local_8 * 5] == DAT_00583d8c)))) &&
     (DAT_00583d8c != -1)) {
    FUN_0045dfd4(DAT_00583d8c,1);
    if (DAT_004d59b4 == 0x22) {
      FUN_00419c08(&DAT_005a43d0 + DAT_00583d8c * 0xadc);
    }
    iVar1 = FUN_0045bf78(local_8,local_c,param_1,param_2,0);
    if (DAT_004d5b18 < iVar1) {
      if ((iVar1 == DAT_00583d94) && (iVar1 != -1)) {
        FUN_0045bb88(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,iVar1);
      }
      else if (DAT_004d59b4 == 0) {
        FUN_0045ad98(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
      }
    }
    else {
      FUN_0045ad98(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
    }
  }
  DAT_00583d8c = 0xffffffff;
  DAT_00583d94 = 0xffffffff;
  DAT_00583d88 = 0xffffffff;
  DAT_00583d90 = 0xffffffff;
  return;
}

