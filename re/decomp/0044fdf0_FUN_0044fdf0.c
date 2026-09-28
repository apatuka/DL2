// FUN_0044fdf0 @ 0044fdf0 size=44 sig=undefined FUN_0044fdf0() cc=unknown
// callers: FUN_0044ffbc,FUN_00450150,FUN_0044fe58,FUN_00486e34,FUN_00450000,FUN_0044febc,FUN_004500d8,FUN_0047c730,FUN_00450204,FUN_0044fe8c
// callees: 

void FUN_0044fdf0(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(&DAT_004c61a0 + DAT_004d5a94 * 0xd8);
  do {
    if (param_1 == *piVar2) {
      return;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 0x11;
  } while (iVar1 < 3);
  return;
}

