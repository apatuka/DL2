// FUN_00411534 @ 00411534 size=231 sig=undefined FUN_00411534() cc=unknown
// callers: 
// callees: fclose,FUN_004aa518,FUN_004b0a30,FUN_0041140c,memset,fopen,FUN_004111ec

undefined4 FUN_00411534(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  memset(&DAT_0053319e,0,0x4e);
  memset(&DAT_00533198,0,6);
  DAT_005331c0 = fopen(param_3,&DAT_004b6f8c);
  if (DAT_005331c0 == 0) {
    uVar1 = 0;
  }
  else {
    DAT_005331bc = 0;
    iVar2 = FUN_004aa518(&param_2,4,1,DAT_005331c0);
    if (iVar2 == 1) {
      DAT_005331c4 = param_1;
      DAT_005331d0 = param_2;
      iVar2 = FUN_0041140c();
      if (iVar2 == 0) {
        fclose(DAT_005331c0);
        uVar1 = 0;
      }
      else {
        FUN_004111ec();
        FUN_004b0a30(DAT_005331b2);
        FUN_004b0a30(DAT_005331b6);
        FUN_004b0a30(DAT_0053319e);
        fclose(DAT_005331c0);
        uVar1 = 1;
      }
    }
    else {
      fclose(DAT_005331c0);
      uVar1 = 0;
    }
  }
  return uVar1;
}

