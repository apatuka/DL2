// FUN_0047dd58 @ 0047dd58 size=313 sig=undefined FUN_0047dd58() cc=unknown
// callers: FUN_0047de94,FUN_0047dd58
// callees: FUN_0047dd58

void FUN_0047dd58(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  short *psVar5;
  short *psVar6;
  int local_10;
  
  *(undefined2 *)(DAT_00655040 + 0x152 + param_1 * 0x34) = (undefined2)param_2;
  if (param_1 == DAT_0065503c) {
    DAT_00655038 = param_2;
  }
  else {
    psVar5 = &DAT_004dcbe0;
    local_10 = 0;
    psVar6 = &DAT_004dcbd8;
    do {
      iVar1 = (int)*psVar6 + param_1 % 6;
      iVar2 = (int)*psVar5 + param_1 / 6;
      if ((((-1 < iVar1) && (iVar1 < 6)) && (-1 < iVar2)) && (iVar2 < 6)) {
        iVar1 = iVar2 * 6 + iVar1;
        iVar2 = iVar1 * 0x34 + DAT_00655040;
        uVar3 = (int)*(short *)(iVar2 + 0x142) & 0xff;
        if (((int)*(short *)(iVar2 + 0x142) & 0xff00U) != 0x2000) {
          if (*(char *)(iVar2 + 0x150) == '\0') {
            if (uVar3 == 0xff) {
              iVar4 = param_2 + 0x19;
            }
            else {
              iVar4 = *(int *)(&DAT_004dcbe8 + uVar3 * 4) + param_2;
            }
          }
          else {
            iVar4 = param_2 + 1;
          }
          if ((iVar4 < *(short *)(iVar2 + 0x152)) && (iVar4 < DAT_00655038)) {
            FUN_0047dd58(iVar1,iVar4);
          }
        }
      }
      local_10 = local_10 + 1;
      psVar5 = psVar5 + 1;
      psVar6 = psVar6 + 1;
    } while (local_10 < 4);
  }
  return;
}

