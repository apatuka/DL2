// FUN_0040febc @ 0040febc size=546 sig=undefined FUN_0040febc() cc=unknown
// callers: FUN_00410164
// callees: FUN_0040ac58,FUN_0040b87c,FUN_00447a40,FUN_0040c3b8,FUN_0040fc14,FUN_0040ba64,FUN_004101d4,FUN_00401108,FUN_0040fe58,FUN_0040b0c0

void FUN_0040febc(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  int *local_18;
  int local_10;
  int local_8;
  
  iVar6 = *(int *)(param_2 + 0x1c);
  iVar7 = param_1 * 0x2648 + iVar6 * 0xc4;
  piVar8 = (int *)(&DAT_00522584 + iVar7);
  local_8 = -1;
  if ((&DAT_00522594)[iVar6 * 0x31 + param_1 * 0x992] != 0) {
    local_8 = (int)*(short *)((&DAT_00522594)[iVar6 * 0x31 + param_1 * 0x992] + 0x1a);
  }
  iVar4 = *(int *)(&DAT_004b6640 + *piVar8 * 0x40);
  if ((iVar4 != 0) &&
     (iVar2 = FUN_0040ac58(piVar8,iVar4), iVar2 < *(int *)(&DAT_004b6b80 + *piVar8 * 4))) {
    if ((iVar4 == 4) && (*piVar8 == 9)) {
      local_8 = FUN_0040fe58(piVar8);
    }
    uVar9 = 1;
    uVar3 = FUN_0040fc14(param_1,iVar4);
    FUN_004101d4(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),uVar3,local_8,
                 uVar9);
    return;
  }
  local_18 = &DAT_005225c8 + iVar6 * 0x31 + param_1 * 0x992;
  local_10 = 0;
  do {
    iVar6 = *local_18;
    if (((iVar6 != 0) && ((int)*(char *)(iVar6 + 7) != *(int *)(&DAT_004b6640 + *piVar8 * 0x40))) &&
       ((*piVar8 != 9 || ((&DAT_004faf8d)[*(char *)(iVar6 + 6) * 0x24] != '\x01')))) {
      cVar1 = (&DAT_004faf87)[*(char *)(iVar6 + 6) * 0x24];
      iVar4 = FUN_0040b87c(piVar8,(int)cVar1);
      if (iVar4 != 0) {
        iVar2 = FUN_00401108(iVar4,0,0,0,0);
        iVar5 = FUN_00401108(iVar6,0,0,0,0);
        if (iVar5 < iVar2) {
          FUN_0040b0c0(&DAT_00522584 + param_1 * 0x2648,iVar6);
          FUN_0040b0c0(piVar8,iVar4);
          goto LAB_0041007a;
        }
      }
      iVar2 = FUN_0040fc14(param_1,(int)cVar1);
      if (((iVar4 != 0) && (*(char *)(iVar4 + 6) != iVar2)) ||
         ((iVar4 == 0 &&
          ((*(char *)(iVar6 + 6) != iVar2 ||
           (iVar6 = FUN_00447a40((int)*(short *)(iVar6 + 0x28)), iVar6 == 0)))))) {
        FUN_004101d4(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),iVar2,local_8
                     ,1);
      }
    }
LAB_0041007a:
    local_10 = local_10 + 1;
    local_18 = local_18 + 1;
    if (0xf < local_10) {
      iVar6 = FUN_0040c3b8(piVar8);
      if ((iVar6 < *(int *)(&DAT_00522598 + iVar7)) && (iVar6 = FUN_0040ba64(piVar8), iVar6 != 0)) {
        uVar9 = 1;
        uVar3 = FUN_0040fc14(param_1,iVar6);
        FUN_004101d4(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),uVar3,local_8
                     ,uVar9);
      }
      return;
    }
  } while( true );
}

