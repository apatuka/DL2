// FUN_004485e8 @ 004485e8 size=280 sig=undefined FUN_004485e8() cc=unknown
// callers: FUN_004487b8,FUN_00448878
// callees: FUN_004484fc,FUN_004023dc

int FUN_004485e8(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *local_20;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 10000;
  local_c = 0;
  local_10 = param_2;
  if (0x16 < param_2) {
    local_10 = 0xb;
  }
  local_14 = param_3;
  if (0x16 < param_3) {
    local_14 = 0xb;
  }
  local_18 = 0;
  local_20 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *local_20;
    if (((iVar1 != 0) &&
        ((param_2 < 0x16 ||
         (*(int *)(&DAT_004f9de6 + *(char *)(iVar1 + 4) * 0x32) == param_2 + -0x16)))) &&
       ((*(int *)(&DAT_00564228 + param_3 * 0x18) != 0 ||
        ((param_3 < 0x16 ||
         (*(int *)(&DAT_004f9de6 + *(char *)(iVar1 + 4) * 0x32) == param_3 + -0x16)))))) {
      iVar2 = FUN_004023dc(iVar1,local_10);
      if (iVar2 != -1) {
        if (*(int *)(&DAT_00564228 + param_3 * 0x18) == 0) {
          iVar3 = FUN_004023dc(iVar1,local_14);
          if (iVar3 == -1) goto LAB_004486e1;
        }
        iVar3 = FUN_004484fc(local_10,param_1,iVar1);
        if ((0 < *(int *)(iVar1 + 0x18 + iVar2 * 4)) && (iVar3 < local_8)) {
          local_c = iVar1;
          local_8 = iVar3;
        }
      }
    }
LAB_004486e1:
    local_18 = local_18 + 1;
    local_20 = local_20 + 0xd;
    if (0x23 < local_18) {
      return local_c;
    }
  } while( true );
}

