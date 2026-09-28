// FUN_0040a098 @ 0040a098 size=143 sig=undefined FUN_0040a098() cc=unknown
// callers: FUN_00408a88
// callees: FUN_00409e2c,FUN_0040a14c,FUN_00408b58,FUN_00409ef0,FUN_00409f6c,FUN_00409d9c,FUN_00408f58

void FUN_0040a098(int param_1)

{
  if (DAT_004d5b04 != 0) {
    FUN_00409d9c(param_1);
  }
  FUN_00409e2c(param_1);
  if (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) != 0) {
    FUN_00409ef0(param_1);
  }
  FUN_00409f6c(param_1);
  FUN_00408b58(param_1,5,9000,1,100,1);
  FUN_00408f58(param_1,5,0xfffff060,1,0);
  FUN_00408f58(param_1,5,0xffffec78,10,0);
  FUN_0040a14c(param_1,5,&DAT_004b65d0);
  return;
}

