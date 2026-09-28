// FUN_0046f26c @ 0046f26c size=406 sig=undefined FUN_0046f26c() cc=unknown
// callers: SeaManipulationEffects
// callees: DeleteUnit,FUN_0044134c,FUN_00423690,FUN_004237d0
// strings: \"downed\"

void FUN_0046f26c(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  char *local_c;
  
  cVar1 = *(char *)(*(int *)(param_1 + 0x3c) + 0x998);
  puVar4 = PTR_DAT_005098a8;
  if ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] == '\x03') {
    puVar4 = PTR_s_downed_005098a4;
  }
  local_c = &DAT_0059f162;
  iVar3 = 0;
  do {
    if ((1 << ((byte)iVar3 & 0x1f) & (int)cVar1) != 0) {
      if (iVar3 == *(char *)(param_1 + 8)) {
        FUN_00423690(iVar3,0x79,*(undefined4 *)(param_1 + 0x3c),puVar4,
                     (&PTR_s_No_Unit_004faf7c)[*(char *)(param_1 + 6) * 9],0);
      }
      else {
        iVar2 = FUN_0044134c((int)*(char *)(param_1 + 8),iVar3);
        if (iVar2 == 0) {
          FUN_004237d0(iVar3,0x77,*(undefined4 *)(param_1 + 0x3c),puVar4,
                       (&PTR_s_No_Unit_004faf7c)[*(char *)(param_1 + 6) * 9],
                       (&PTR_s_ChCh_t_00509038)
                       [(char)(&DAT_0059f162)[*(char *)(param_1 + 8) * 0x2d8]],
                       (int)*(char *)(param_1 + 8),0);
          FUN_004237d0((int)*(char *)(param_1 + 8),0x7a,
                       (&PTR_s_No_Unit_004faf7c)[*(char *)(param_1 + 6) * 9],puVar4,
                       *(undefined4 *)(param_1 + 0x3c),(&PTR_s_ChCh_t_00509038)[*local_c],iVar3,0);
        }
        else {
          FUN_004237d0(iVar3,0x78,*(undefined4 *)(param_1 + 0x3c),puVar4,
                       (&PTR_s_No_Unit_004faf7c)[*(char *)(param_1 + 6) * 9],
                       (&PTR_s_ChCh_t_00509038)
                       [(char)(&DAT_0059f162)[*(char *)(param_1 + 8) * 0x2d8]],
                       (int)*(char *)(param_1 + 8),0);
          FUN_004237d0((int)*(char *)(param_1 + 8),0x7a,
                       (&PTR_s_No_Unit_004faf7c)[*(char *)(param_1 + 6) * 9],puVar4,
                       *(undefined4 *)(param_1 + 0x3c),(&PTR_s_ChCh_t_00509038)[*local_c],iVar3,0);
        }
      }
    }
    iVar3 = iVar3 + 1;
    local_c = local_c + 0x2d8;
  } while (iVar3 < 7);
  DeleteUnit(param_1);
  return;
}

