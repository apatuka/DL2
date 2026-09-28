// FUN_0047d8f0 @ 0047d8f0 size=62 sig=undefined FUN_0047d8f0() cc=unknown
// callers: FUN_0047da24
// callees: 

int FUN_0047d8f0(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  *(undefined2 *)(&DAT_0065504c + DAT_00655048 * 4) = param_1;
  *(undefined2 *)(&DAT_0065504e + DAT_00655048 * 4) = param_2;
  iVar1 = DAT_00655048 + 1;
  DAT_00655048 = iVar1 % 0xa0;
  return iVar1 / 0xa0;
}

