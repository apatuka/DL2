// FUN_00408a88 @ 00408a88 size=205 sig=undefined FUN_00408a88() cc=unknown
// callers: 
// callees: FUN_004034b8,FUN_00403858,FUN_004064a0,FUN_00403238,FUN_0040af0c,FUN_0040a420,FUN_00404570,FUN_00409d38,FUN_0046ca40,FUN_00406fa0,FUN_00403684,FUN_00405b38,FUN_00405aac,FUN_00409914,FUN_004087b0,FUN_00407030,FUN_004089a4,FUN_00403d98,FUN_0040a098,FUN_004038c4,FUN_00403750,FUN_00404b68,FUN_004437c4,FUN_0040aaa4,FUN_0040c21c,FUN_00407be8,FUN_00409b58,FUN_004046ac

void FUN_00408a88(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  
  FUN_004034b8(param_1);
  FUN_0040af0c(param_1);
  FUN_004087b0(param_1);
  FUN_004064a0(param_1,&DAT_00521bb4);
  FUN_00403858(param_1);
  FUN_00404570(param_1);
  FUN_004089a4(param_1);
  FUN_00403d98(param_1,&DAT_00521bb4);
  FUN_00403238(param_1);
  uVar1 = FUN_00407030(param_1);
  uVar2 = FUN_0046ca40();
  if ((uVar2 & 7) == 0) {
    uVar2 = FUN_00406fa0(param_1);
    uVar1 = uVar1 | uVar2;
  }
  if (uVar1 != 0) {
    FUN_004437c4(param_1);
  }
  FUN_00403684(param_1);
  FUN_00403750(param_1);
  FUN_0040a098(param_1);
  FUN_00409914(param_1);
  FUN_00409b58(param_1);
  FUN_0040a420(param_1);
  FUN_00409d38(param_1);
  FUN_0040aaa4(param_1);
  FUN_00405b38(param_1);
  FUN_00405aac(param_1);
  FUN_0040c21c(param_1);
  FUN_00407be8(param_1);
  FUN_004038c4(param_1);
  FUN_004046ac(param_1);
  FUN_00404b68(param_1,0x32);
  return;
}

