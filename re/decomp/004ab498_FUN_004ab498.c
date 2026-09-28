// FUN_004ab498 @ 004ab498 size=29 sig=undefined FUN_004ab498() cc=unknown
// callers: 
// callees: 

uint FUN_004ab498(int *param_1)

{
  byte *pbVar1;
  uint uVar2;
  
  pbVar1 = (byte *)*param_1;
  *param_1 = *param_1 + 1;
  if (*pbVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (uint)*pbVar1;
  }
  return uVar2;
}

