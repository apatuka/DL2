// FUN_0040aaa4 @ 0040aaa4 size=139 sig=undefined FUN_0040aaa4() cc=unknown
// callers: FUN_00408a88
// callees: FUN_0040a14c,FUN_00408b58,FUN_0040a898,FUN_0040a5a4,FUN_0040be04,FUN_0040a710,FUN_00408f58,FUN_0040c74c

void FUN_0040aaa4(int param_1)

{
  int iVar1;
  
  FUN_00408b58(param_1,1,12000,0,100,1);
  FUN_00408f58(param_1,1,0xfffff830,0,0);
  iVar1 = FUN_0040c74c(param_1,1);
  if (iVar1 == 0) {
    FUN_0040be04(param_1,0xffffffff,0xffffffff,0,1,(int)(char)(&DAT_0059f219)[param_1 * 0x2d8]);
  }
  FUN_0040a710(param_1);
  if (DAT_004d5b00 == '\x02') {
    FUN_0040a898(param_1);
  }
  FUN_0040a5a4(param_1);
  FUN_0040a14c(param_1,1,&DAT_004b65f8);
  return;
}

