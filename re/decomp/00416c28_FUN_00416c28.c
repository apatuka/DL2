// FUN_00416c28 @ 00416c28 size=122 sig=undefined FUN_00416c28() cc=unknown
// callers: FUN_0040a6a0,FUN_004467e8,FUN_0040fc14,FUN_00416ca4
// callees: 

undefined4 FUN_00416c28(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = (&DAT_004faf87)[param_2 * 0x24];
  if ((((param_2 == 0x18) || (param_2 == 0xb)) ||
      ((*(short *)(&DAT_0055a0f4 + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) != 0 &&
       ((cVar1 == '\x01' || (cVar1 == '\v')))))) ||
     (((1 << ((byte)param_1 & 0x1f) & (int)DAT_004fc412) != 0 &&
      (((param_2 == 0xc || (cVar1 == '\x01')) || (cVar1 == '\v')))))) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

