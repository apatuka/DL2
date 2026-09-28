// FUN_004a57b2 @ 004a57b2 size=45 sig=undefined FUN_004a57b2() cc=unknown
// callers: 
// callees: 

int FUN_004a57b2(int *param_1)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    iVar1 = 0;
  }
  else if ((*(byte *)(*param_1 + 2) & 1) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(short *)*param_1 * 8 + *param_1 + 0xc;
  }
  return iVar1;
}

