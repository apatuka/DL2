// FUN_00446e30 @ 00446e30 size=420 sig=undefined FUN_00446e30() cc=unknown
// callers: FUN_004471c0
// callees: FUN_00446bf0

bool FUN_00446e30(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  if (param_2 == *(char *)(param_1 + 0x20)) {
    for (iVar2 = *(int *)(param_1 + 0x7a); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
      if (((param_2 == *(char *)(iVar2 + 8)) && (iVar3 = FUN_00446bf0(iVar2), iVar3 == 0)) &&
         ((cVar1 = (&DAT_004faf8d)[*(char *)(iVar2 + 6) * 0x24], cVar1 == '\x02' ||
          ((cVar1 == '\x06' || (cVar1 == '\x01')))))) {
        return true;
      }
    }
    for (iVar2 = *(int *)(param_1 + 0x76); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
      if (((param_2 == *(char *)(iVar2 + 8)) && (iVar3 = FUN_00446bf0(iVar2), iVar3 == 0)) &&
         ((cVar1 = (&DAT_004faf8d)[*(char *)(iVar2 + 6) * 0x24], cVar1 == '\x02' ||
          ((cVar1 == '\x06' || (cVar1 == '\x01')))))) {
        return true;
      }
    }
  }
  iVar3 = -1;
  for (iVar2 = *(int *)(param_1 + 0x7a); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x54)) {
    if (((iVar3 != *(char *)(iVar2 + 8)) && (iVar4 = FUN_00446bf0(iVar2), iVar4 == 0)) &&
       ((cVar1 = (&DAT_004faf8d)[*(char *)(iVar2 + 6) * 0x24], cVar1 == '\x02' ||
        ((cVar1 == '\x06' || (cVar1 == '\x01')))))) {
      if (iVar3 != -1) {
        return false;
      }
      iVar3 = (int)*(char *)(iVar2 + 8);
    }
  }
  iVar2 = *(int *)(param_1 + 0x76);
  do {
    if (iVar2 == 0) {
      if ((*(short *)(param_1 + 0x30) == 0) || (iVar3 == *(char *)(param_1 + 0x20))) {
        bVar5 = param_2 == iVar3;
      }
      else {
        bVar5 = false;
      }
      return bVar5;
    }
    if (((iVar3 != *(char *)(iVar2 + 8)) && (iVar4 = FUN_00446bf0(iVar2), iVar4 == 0)) &&
       ((cVar1 = (&DAT_004faf8d)[*(char *)(iVar2 + 6) * 0x24], cVar1 == '\x02' ||
        ((cVar1 == '\x06' || (cVar1 == '\x01')))))) {
      if (iVar3 != -1) {
        return false;
      }
      iVar3 = (int)*(char *)(iVar2 + 8);
    }
    iVar2 = *(int *)(iVar2 + 0x54);
  } while( true );
}

