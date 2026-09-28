// FUN_0044d230 @ 0044d230 size=81 sig=undefined FUN_0044d230() cc=unknown
// callers: FUN_0044339c,FUN_0046bdfc,FUN_004568c8,FUN_00442978
// callees: 

int FUN_0044d230(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 0x154 + param_3 * 0x34);
  while( true ) {
    if (0x23 < param_3) {
      return -1;
    }
    iVar1 = *piVar2;
    if ((((iVar1 != 0) && (param_2 == *(char *)(iVar1 + 5))) && (*(short *)(iVar1 + 0x14) == 0)) &&
       ((*(byte *)(iVar1 + 2) & 4) != 0)) break;
    param_3 = param_3 + 1;
    piVar2 = piVar2 + 0xd;
  }
  return param_3;
}

