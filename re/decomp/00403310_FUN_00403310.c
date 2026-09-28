// FUN_00403310 @ 00403310 size=61 sig=undefined FUN_00403310() cc=unknown
// callers: 
// callees: 

undefined4 FUN_00403310(int param_1,int param_2)

{
  short *psVar1;
  
  psVar1 = &DAT_0055a820;
  while( true ) {
    if (DAT_00651cb0 <= *psVar1) {
      return 0;
    }
    if ((4 < *(int *)(psVar1 + param_1 * 2 + 0xc)) && (4 < *(int *)(psVar1 + param_2 * 2 + 0xc)))
    break;
    psVar1 = psVar1 + 0xd1;
  }
  return 1;
}

