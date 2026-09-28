// FUN_0045c27c @ 0045c27c size=263 sig=undefined FUN_0045c27c() cc=unknown
// callers: FUN_00419eac,FUN_0045ccf8
// callees: FUN_0043edd8,FUN_00481a5c,FUN_00418e00,FUN_00459ea8,FUN_00449cc4

undefined * FUN_0045c27c(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined *puVar3;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar2 = FUN_00449cc4(param_1,param_2,&local_8,&local_c);
  if (iVar2 == 0) {
    if ((DAT_004d59b4 == 0) || ((DAT_004d59b4 == 0x22 && (cVar1 = FUN_00418e00(), cVar1 != '\0'))))
    {
      if (DAT_004d5ad0 == 0) {
        FUN_00459ea8(local_8,local_c,&local_10,&local_14);
      }
      else {
        FUN_0043edd8(local_8,local_c,&local_10,&local_14);
      }
    }
  }
  else if (iVar2 == 1) {
    FUN_00481a5c(local_8,local_c,&local_10,&local_14);
  }
  else if (iVar2 - 0xdU < 3) {
    return &DAT_005a43d0 + DAT_004c5b50 * 0xadc;
  }
  if ((((local_10 < 0) || (DAT_004d5b1a <= local_10)) || (local_14 < 0)) ||
     (DAT_004d5b1b <= local_14)) {
    puVar3 = (undefined *)0x0;
  }
  else {
    puVar3 = &DAT_005a43d0 + (short)(&DAT_005a0552)[local_14 * 200 + local_10 * 5] * 0xadc;
  }
  return puVar3;
}

