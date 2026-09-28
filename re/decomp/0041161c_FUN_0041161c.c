// FUN_0041161c @ 0041161c size=214 sig=undefined FUN_0041161c() cc=unknown
// callers: 
// callees: fclose,FUN_004112c0,FUN_004b0a30,FUN_004114f0,malloc,memset,fopen,fread

undefined4 FUN_0041161c(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_8;
  
  memset(&DAT_0053319e,0,0x4e);
  memset(&DAT_00533198,0,6);
  DAT_005331bc = fopen(param_1,&DAT_004b6f8f);
  if (DAT_005331bc == 0) {
    uVar2 = 0;
  }
  else {
    DAT_005331c0 = 0;
    iVar1 = fread(&local_8,4,1,DAT_005331bc);
    if (iVar1 == 1) {
      *param_2 = local_8;
      DAT_005331c8 = malloc(local_8);
      iVar1 = FUN_004114f0();
      if (iVar1 == 0) {
        fclose(DAT_005331bc);
        uVar2 = 0;
      }
      else {
        FUN_004112c0();
        FUN_004b0a30(DAT_0053319e);
        fclose(DAT_005331bc);
        uVar2 = DAT_005331c8;
      }
    }
    else {
      fclose(DAT_005331bc);
      uVar2 = 0;
    }
  }
  return uVar2;
}

