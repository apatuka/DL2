// FUN_00449870 @ 00449870 size=1105 sig=undefined FUN_00449870() cc=unknown
// callers: FUN_0044a000
// callees: FUN_00440f64,FUN_00418e00,FUN_0048149c,FUN_0045ab1c,FUN_004812f4,FUN_004824c4,FUN_0045e0b4,FUN_00465df8

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00449870(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  if (((((DAT_004d59b4 == 1) || (DAT_004d59b4 == 0)) || (DAT_004d59b4 == 7)) || (DAT_004d59b4 == 5))
     || ((DAT_004d59b4 == 0x22 && (DAT_005332b0 == '\0')))) {
    DAT_004c5478 = 0x1e6;
    DAT_004c547c = 0x147;
    DAT_004c5480 = 0x91;
    DAT_004c5484 = 0x91;
    DAT_004c5470 = 1;
    if (DAT_004d59b4 == 0x22) {
      cVar1 = FUN_00418e00();
      if (cVar1 != '\0') goto LAB_004498eb;
    }
    else {
LAB_004498eb:
      FUN_0045e0b4(DAT_004c5b54,DAT_004c5b58);
    }
    FUN_004824c4(param_1);
  }
  else {
    DAT_004c5470 = 0;
  }
  if (DAT_004d59b4 == 1) {
LAB_0044993f:
    iVar3 = DAT_004c5b50 * 0xadc;
    FUN_004812f4(param_1,(int)*(char *)(&DAT_005a4450)
                                       [DAT_004c5b50 * 0x2b7 + (int)(char)(&DAT_005a4444)[iVar3]],
                 (int)((char *)(&DAT_005a4450)
                               [DAT_004c5b50 * 0x2b7 + (int)(char)(&DAT_005a4444)[iVar3]])[1]);
    _DAT_004c5958 = 0x4b;
    _DAT_004c595c = 0x1b;
    _DAT_004c5960 = 0x12;
    _DAT_004c5964 = 0x12;
    _DAT_004c5950 = 1;
    if ((&DAT_005a43f1)[iVar3] != '\0') {
      _DAT_004c5978 = 0xb;
      _DAT_004c597c = 0x1b;
    }
    else {
      _DAT_004c5978 = 0x2b;
      _DAT_004c597c = 0xb;
    }
    _DAT_004c5980 = 0x12;
    _DAT_004c5984 = 0x12;
    _DAT_004c5970 = 1;
    _DAT_004c5998 = 0x4b;
    _DAT_004c599c = 0xb;
    _DAT_004c59a0 = 0x12;
    _DAT_004c59a4 = 0x12;
    _DAT_004c5990 = 1;
    if ((&DAT_005a43f1)[iVar3] != '\0') {
      _DAT_004c59b8 = 0xb;
      _DAT_004c59bc = 0xb;
    }
    else {
      _DAT_004c59b8 = 0x2b;
      _DAT_004c59bc = 0x1b;
    }
    _DAT_004c59c0 = 0x12;
    _DAT_004c59c4 = 0x12;
    _DAT_004c59b0 = 1;
    _DAT_004c59d8 = 0x6c;
    _DAT_004c59dc = 0xc;
    _DAT_004c59e0 = 0x12;
    _DAT_004c59e4 = 0x12;
    _DAT_004c59d0 = 1;
    _DAT_004c59f8 = 0xc;
    _DAT_004c59fc = 0x2c;
    _DAT_004c5a00 = 0x12;
    _DAT_004c5a04 = 0x20;
    _DAT_004c59f0 = 1;
    _DAT_004c5a18 = 0x2c;
    _DAT_004c5a1c = 0x2c;
    _DAT_004c5a20 = 0x12;
    _DAT_004c5a24 = 0x20;
    _DAT_004c5a10 = 1;
    _DAT_004c5a38 = 0x4c;
    _DAT_004c5a3c = 0x2c;
    _DAT_004c5a40 = 0x12;
    _DAT_004c5a44 = 0x20;
    _DAT_004c5a30 = 1;
    _DAT_004c5a58 = 0x6c;
    _DAT_004c5a5c = 0x2c;
    _DAT_004c5a60 = 0x12;
    _DAT_004c5a64 = 0x20;
    _DAT_004c5a50 = 1;
    _DAT_004c5a78 = 0xc;
    _DAT_004c5a7c = 0x60;
    _DAT_004c5a80 = 0x12;
    _DAT_004c5a84 = 0x20;
    _DAT_004c5a70 = 1;
    _DAT_004c5a98 = 0x2c;
    _DAT_004c5a9c = 0x60;
    _DAT_004c5aa0 = 0x12;
    _DAT_004c5aa4 = 0x20;
    _DAT_004c5a90 = 1;
  }
  else {
    if ((DAT_004d59b4 == 0x22) && (DAT_005332b0 == '\0')) {
      cVar1 = FUN_00418e00();
      if (cVar1 == '\0') goto LAB_0044993f;
    }
    _DAT_004c5950 = 0;
    _DAT_004c5970 = 0;
    _DAT_004c5990 = 0;
    _DAT_004c59b0 = 0;
    _DAT_004c59d0 = 0;
    _DAT_004c59f0 = 0;
    _DAT_004c5a10 = 0;
    _DAT_004c5a30 = 0;
    _DAT_004c5a50 = 0;
    _DAT_004c5a70 = 0;
  }
  if (DAT_004d59b4 == 2) {
    iVar3 = *(int *)(DAT_00559dbc + 4);
    iVar2 = (int)**(char **)(iVar3 + 0x80 + *(char *)(iVar3 + 0x74) * 4);
    if (*(char *)(DAT_00559dbc + 0xd) == '\0') {
      iVar2 = iVar2 + 1;
    }
    FUN_0048149c(iVar2,(int)*(char *)(*(int *)(iVar3 + 0x80 + *(char *)(iVar3 + 0x74) * 4) + 1),
                 iVar3,DAT_00559dbc);
  }
  if (DAT_004d59b4 != 0) {
    if ((DAT_004d59b4 != 0x22) || (DAT_005332b0 != '\0')) goto LAB_00449ca7;
    cVar1 = FUN_00418e00();
    if (cVar1 == '\0') goto LAB_00449ca7;
  }
  FUN_00465df8(1);
  if (DAT_004d5ad0 == 0) {
    FUN_0045ab1c(param_1);
  }
  else {
    FUN_00440f64();
  }
LAB_00449ca7:
  FUN_0045e0b4(DAT_004c5b54,DAT_004c5b58);
  return;
}

