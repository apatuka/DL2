// FUN_0047da24 @ 0047da24 size=352 sig=undefined FUN_0047da24() cc=unknown
// callers: FUN_0047db84
// callees: FUN_0047d988,FUN_0047d9f8,FUN_0047d930,FUN_0047d8f0

void FUN_0047da24(int param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  short *local_14;
  int local_10;
  int local_8;
  
  puVar3 = &DAT_005a0558;
  iVar5 = 0;
  local_8 = 0x7fff;
  do {
    iVar4 = 0;
    puVar2 = puVar3;
    do {
      *puVar2 = 0x7fff;
      iVar4 = iVar4 + 1;
      puVar2 = puVar2 + 5;
    } while (iVar4 < 0x28);
    iVar5 = iVar5 + 1;
    puVar3 = puVar3 + 200;
  } while (iVar5 < 0x28);
  DAT_00655048 = 0;
  DAT_00655044 = 0;
  (&DAT_005a0558)[param_2 * 200 + param_1 * 5] = 0;
  FUN_0047d8f0(param_1,param_2);
  while( true ) {
    iVar5 = FUN_0047d930(&param_1,&param_2);
    if (iVar5 == 0) break;
    psVar7 = &DAT_004dcbd8;
    sVar1 = (&DAT_005a0558)[param_2 * 200 + param_1 * 5];
    local_10 = 0;
    local_14 = &DAT_004dcbe0;
    do {
      iVar4 = *psVar7 + param_1;
      iVar6 = *local_14 + param_2;
      iVar5 = FUN_0047d988(iVar4,iVar6);
      if (iVar5 != 0) {
        iVar5 = FUN_0047d9f8(iVar4,iVar6);
        iVar5 = iVar5 + sVar1;
        if (iVar5 < local_8) {
          if ((iVar4 == param_3) && (iVar6 == param_4)) {
            if (iVar5 < local_8) {
              local_8 = iVar5;
            }
          }
          else if (iVar5 < (short)(&DAT_005a0558)[iVar6 * 200 + iVar4 * 5]) {
            (&DAT_005a0558)[iVar6 * 200 + iVar4 * 5] = (short)iVar5;
            FUN_0047d8f0(iVar4,iVar6);
          }
        }
      }
      local_10 = local_10 + 1;
      local_14 = local_14 + 1;
      psVar7 = psVar7 + 1;
    } while (local_10 < 4);
  }
  return;
}

