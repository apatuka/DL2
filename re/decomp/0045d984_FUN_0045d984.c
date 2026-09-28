// FUN_0045d984 @ 0045d984 size=707 sig=undefined FUN_0045d984() cc=unknown
// callers: FUN_0044a7c8
// callees: FUN_00449fe8,FUN_0043edd8,FUN_0045df90,FUN_0045bde4,sprintf,FUN_00419c08,FUN_0042836c,FUN_00449fd8,FUN_00459068,FUN_0045dfd4,FUN_00459ea8,FUN_00449f5c,FUN_0045bf78,FUN_00472fb4,FUN_0045df3c,FUN_00449dec
// strings: \"blow away mines?\"

void FUN_0045d984(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  undefined1 local_a8 [152];
  int local_10;
  int local_c;
  int local_8;
  
  bVar1 = false;
  if (DAT_004d5ad0 == 0) {
    FUN_00459ea8(param_1,param_2,&local_8,&local_c);
  }
  else {
    FUN_0043edd8(param_1,param_2,&local_8,&local_c);
  }
  if ((((-1 < local_8) && (local_8 < DAT_004d5b1a)) && (-1 < local_c)) &&
     ((local_c < DAT_004d5b1b &&
      ((short)(&DAT_005a0552)[local_c * 200 + local_8 * 5] == DAT_00583d88)))) {
    if (DAT_00583d88 != DAT_004c5b50) {
      bVar1 = true;
      FUN_0045df90();
      local_10 = DAT_004c5b50;
      (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] = (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] & 0xfffffffe;
      (&DAT_005a43ec)[DAT_00583d88 * 0x2b7] = (&DAT_005a43ec)[DAT_00583d88 * 0x2b7] | 1;
      FUN_0045dfd4(DAT_00583d88,1);
      DAT_004c5b50 = DAT_00583d88;
      if (DAT_004d59b4 == 0x22) {
        FUN_00419c08(&DAT_005a43d0 + DAT_00583d88 * 0xadc);
      }
    }
    iVar2 = FUN_0045bf78(local_8,local_c,param_1,param_2,1);
    if (iVar2 == 2000) {
      sprintf(local_a8,s_blow_away_mines__004d1cba);
      iVar2 = FUN_0042836c(local_a8,local_a8,6,0,0xc);
      if (iVar2 == 1) {
        *(undefined4 *)(&DAT_005a4c78 + (short)(&DAT_005a0552)[local_c * 200 + local_8 * 5] * 0xadc)
             = 0;
      }
      FUN_0045df3c(DAT_004c5b50);
      FUN_00449dec();
    }
    else if (((DAT_004d5b18 < iVar2) && (iVar2 == DAT_00583d90)) && (iVar2 != -1)) {
      FUN_0045bde4(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,iVar2);
      bVar1 = true;
    }
    if (((DAT_004d5aa0 != '\0') &&
        (iVar2 = (int)(char)(&DAT_005a43f0)[DAT_00583d88 * 0xadc], iVar2 != DAT_0058f1f4)) &&
       (iVar2 != -1)) {
      bVar1 = true;
      FUN_00472fb4(iVar2);
    }
    if (bVar1) {
      FUN_0045df3c(local_10);
      FUN_0045df3c(DAT_004c5b50);
      FUN_00449fd8();
      FUN_00449fe8();
      FUN_00449dec();
      FUN_00449f5c();
    }
  }
  DAT_00583d8c = 0xffffffff;
  DAT_00583d94 = 0xffffffff;
  DAT_00583d88 = 0xffffffff;
  DAT_00583d90 = 0xffffffff;
  FUN_00459068();
  return;
}

