// FUN_00409474 @ 00409474 size=99 sig=undefined FUN_00409474() cc=unknown
// callers: 
// callees: FUN_0044d1a4

int FUN_00409474(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int local_8;
  
  piVar4 = &DAT_00521bb4;
  iVar5 = 0;
  local_8 = 0;
  do {
    iVar1 = *piVar4;
    iVar2 = *(int *)(iVar1 + 0xa12) - *(int *)(iVar1 + 0xa60);
    iVar3 = FUN_0044d1a4(iVar1,0x13,0);
    if (((iVar3 == 0) && (*(short *)(iVar1 + 0x30) != 0)) && (local_8 < iVar2)) {
      iVar5 = iVar1;
      local_8 = iVar2;
    }
    piVar4 = (int *)piVar4[1];
  } while (piVar4 != &DAT_00521bb4);
  return iVar5;
}

