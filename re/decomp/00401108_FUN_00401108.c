// FUN_00401108 @ 00401108 size=467 sig=undefined FUN_00401108() cc=unknown
// callers: FUN_00442c44,FUN_0045727c,FUN_0040b644,FUN_0040febc,FUN_0040c3b8,FUN_0040ee34,FUN_004012dc
// callees: FUN_00447b0c,FUN_00447b30,FUN_00447b9c,FUN_00447bc0

/* WARNING: Removing unreachable block (ram,0x00401240) */

undefined8 FUN_00401108(int param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int local_c;
  int local_8;
  
  iVar2 = FUN_00447b30(param_1);
  iVar2 = iVar2 - *(short *)(param_1 + 0x2c);
  if (((param_2 == 0) ||
      ((((cVar1 = (&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24], cVar1 != '\x01' &&
         (cVar1 != '\x06')) && (cVar1 != '\a')) && (cVar1 != '\v')))) ||
     (*(char *)(param_1 + 6) == '\x17')) {
    if (((1 << (*(byte *)(param_1 + 8) & 0x1f) & (int)DAT_004fbf62) != 0) &&
       ((&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24] == '\n')) {
      iVar2 = iVar2 * 2;
    }
  }
  else {
    iVar2 = iVar2 * 2;
  }
  iVar3 = FUN_00447bc0(param_1);
  if (((param_3 == 0) ||
      (((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] != '\x01' &&
       ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] != '\x06')))) ||
     ((&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24] == '\n')) {
    if (((param_4 == 0) || ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] != '\x03')) ||
       ((&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24] == '\t')) {
      if (((1 << (*(byte *)(param_1 + 8) & 0x1f) & (int)DAT_004fc02a) != 0) &&
         ((&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24] == '\n')) {
        iVar3 = iVar3 + 0xf;
      }
    }
    else {
      iVar3 = iVar3 + 0xf;
    }
  }
  else {
    iVar3 = iVar3 + 0xf;
  }
  iVar4 = FUN_00447b0c(param_1);
  iVar3 = iVar4 * iVar2 * iVar3;
  local_8 = FUN_00447b9c(param_1);
  local_c = 1;
  if (local_8 < 1) {
    piVar5 = &local_c;
  }
  else {
    piVar5 = &local_8;
  }
  iVar3 = iVar3 / *piVar5;
  if (((&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24] == '\t') ||
     (iVar4 = (int)*(char *)(param_1 + 6), iVar2 = iVar3,
     (&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24] == '\x14')) {
    iVar2 = iVar3 / 10;
    iVar4 = iVar3 % 10;
  }
  return CONCAT44(iVar4,iVar2);
}

