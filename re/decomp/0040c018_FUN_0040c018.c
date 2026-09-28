// FUN_0040c018 @ 0040c018 size=318 sig=undefined FUN_0040c018() cc=unknown
// callers: FUN_0040c21c
// callees: FUN_0040b000,FUN_0040ab54,FUN_0040da78,FUN_0040be04,FUN_0040b0c0

void FUN_0040c018(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined2 *puVar4;
  int *piVar5;
  int local_c;
  
  local_c = 0;
  do {
    iVar3 = local_c * 0x5c;
    puVar4 = &DAT_00645370 + local_c * 0x2e;
    if (((((&DAT_00645376)[iVar3] != '\0') && ((char)(&DAT_00645378)[iVar3] == param_1)) &&
        (((&DAT_006453a6)[local_c * 0x2e] == 0 ||
         (iVar1 = FUN_0040ab54(&DAT_005224c0 +
                               param_1 * 0x2648 + (short)(&DAT_006453a6)[local_c * 0x2e] * 0xc4,
                               puVar4), iVar1 == 0)))) && ((&DAT_00645377)[iVar3] != '\t')) {
      if (((undefined2 *)(&DAT_006453b8)[local_c * 0x17] == (undefined2 *)0x0) ||
         ((&DAT_00645376)[iVar3] == '#')) {
        FUN_0040b0c0(&DAT_00522584 + param_1 * 0x2648,puVar4);
      }
      else {
        if ((&DAT_00645376)[iVar3] != '\f') {
          puVar4 = (undefined2 *)(&DAT_006453b8)[local_c * 0x17];
        }
        uVar2 = FUN_0040da78(param_1,*(undefined4 *)(puVar4 + 0x1c));
        uVar2 = FUN_0040be04(param_1,0xffffffff,0xffffffff,uVar2,9,
                             (int)(char)(&DAT_0059f219)[param_1 * 0x2d8]);
        FUN_0040b000(&DAT_00522584 + param_1 * 0x2648,uVar2);
        FUN_0040b0c0(uVar2,puVar4);
        iVar3 = 0;
        piVar5 = (int *)(puVar4 + 0x24);
        do {
          if (*piVar5 != 0) {
            FUN_0040b0c0(uVar2,*piVar5);
          }
          iVar3 = iVar3 + 1;
          piVar5 = piVar5 + 1;
        } while (iVar3 < 3);
      }
    }
    local_c = local_c + 1;
  } while (local_c < 0x230);
  return;
}

