// FUN_0044d1e4 @ 0044d1e4 size=75 sig=undefined FUN_0044d1e4() cc=unknown
// callers: FUN_00485668,FUN_0046ae1c,FUN_004096a8,FUN_00445b94,FUN_0045a50c,FUN_00486964,FUN_0046bdfc,FUN_00446440,FUN_0046e064,FUN_00402df4,FUN_0044081c,FUN_00403c04,FUN_00466508,FUN_0040eb34,FUN_004526b0,FUN_00407864,FUN_0045a0bc
// callees: 

int FUN_0044d1e4(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 0x154 + param_3 * 0x34);
  while( true ) {
    if (0x23 < param_3) {
      return -1;
    }
    iVar1 = *piVar2;
    if (((iVar1 != 0) && (param_2 == *(char *)(iVar1 + 5))) && (*(short *)(iVar1 + 0x14) == 0))
    break;
    param_3 = param_3 + 1;
    piVar2 = piVar2 + 0xd;
  }
  return param_3;
}

