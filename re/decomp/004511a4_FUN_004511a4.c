// FUN_004511a4 @ 004511a4 size=51 sig=undefined FUN_004511a4() cc=unknown
// callers: FUN_00451410,FUN_00454d94,FUN_00455530,FUN_00454c2c,FUN_00455288,FUN_00451550
// callees: 

undefined1 FUN_004511a4(int param_1,int param_2)

{
  undefined1 uVar1;
  
  if ((((param_1 < -9) || (0x1a < param_1)) || (param_2 < -9)) || (0x1a < param_2)) {
    uVar1 = 0;
  }
  else {
    uVar1 = (&DAT_004cf9a5)[param_1 + param_2 * 0x24];
  }
  return uVar1;
}

