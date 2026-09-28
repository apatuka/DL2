// FUN_00448700 @ 00448700 size=184 sig=undefined FUN_00448700() cc=unknown
// callers: FUN_004487b8
// callees: FUN_004484fc,FUN_004023dc,FUN_0044ba18,FUN_0044ba40

int FUN_00448700(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  local_10 = param_3;
  if (0x16 < param_3) {
    local_10 = 0xb;
  }
  iVar5 = 0;
  piVar4 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *piVar4;
    if ((iVar1 != 0) &&
       (((param_3 < 0x16 ||
         (*(int *)(&DAT_004f9de6 + *(char *)(iVar1 + 4) * 0x32) == param_3 + -0x16)) &&
        ((*(byte *)(iVar1 + 2) & 4) != 0)))) {
      iVar2 = FUN_0044ba18(iVar1);
      iVar3 = FUN_0044ba40(iVar1);
      if ((iVar2 < iVar3) || (iVar1 == param_2)) {
        iVar2 = FUN_004023dc(iVar1,local_10);
        if (iVar2 != -1) {
          iVar2 = FUN_004484fc(local_10,param_1,iVar1);
          if (local_8 < iVar2) {
            local_c = iVar1;
            local_8 = iVar2;
          }
        }
      }
    }
    iVar5 = iVar5 + 1;
    piVar4 = piVar4 + 0xd;
  } while (iVar5 < 0x24);
  return local_c;
}

