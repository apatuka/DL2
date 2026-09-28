// FUN_0046bd3c @ 0046bd3c size=189 sig=undefined FUN_0046bd3c() cc=unknown
// callers: FUN_0046bdfc
// callees: FUN_00441388,FUN_00416e70

int FUN_0046bd3c(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int local_8;
  
  local_8 = 0;
  for (iVar2 = *(int *)(param_1 + 0x76); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
    if ((*(char *)(iVar2 + 0x25) == '\n') &&
       (iVar3 = FUN_00416e70(iVar2,10,(int)(char)(&DAT_0059f162)[*(char *)(iVar2 + 8) * 0x2d8]),
       iVar3 != 0)) {
      local_8 = local_8 + 1;
    }
  }
  for (iVar2 = *(int *)(param_1 + 0x7a); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
    cVar1 = (&DAT_0059f162)[*(char *)(iVar2 + 8) * 0x2d8];
    if (((*(char *)(iVar2 + 0x25) == '\n') &&
        (iVar3 = FUN_00441388((int)*(char *)(iVar2 + 8),(int)*(char *)(param_1 + 0x20),2),
        iVar3 != 0)) && (iVar3 = FUN_00416e70(iVar2,10,(int)cVar1), iVar3 != 0)) {
      local_8 = local_8 + 1;
    }
  }
  if (*(int *)(param_1 + 0x8a8) != 0) {
    local_8 = local_8 + 2;
  }
  return local_8;
}

