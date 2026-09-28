// FUN_00447190 @ 00447190 size=46 sig=undefined FUN_00447190() cc=unknown
// callers: FUN_00401a18,FUN_004471c0,FUN_00417434,FUN_00416e70,FUN_00446084,FUN_00445d30,FUN_00401ac0,FUN_00442c44,FUN_0040e1fc,FUN_00437a3c,FUN_00401320,FUN_00442978
// callees: 

int FUN_00447190(int param_1)

{
  int iVar1;
  
  iVar1 = CONCAT31(*(char *)(param_1 + 6) >> 7,(&DAT_004faf8c)[*(char *)(param_1 + 6) * 0x24]);
  if ((1 << (*(byte *)(param_1 + 8) & 0x1f) & (int)DAT_004fc4a8) != 0) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

