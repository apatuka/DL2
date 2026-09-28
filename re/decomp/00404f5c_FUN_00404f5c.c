// FUN_00404f5c @ 00404f5c size=336 sig=undefined FUN_00404f5c() cc=unknown
// callers: FUN_0047c730
// callees: FUN_00404e00,FUN_00404e94

void FUN_00404f5c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  char *pcVar5;
  undefined4 *local_14;
  undefined4 *local_10;
  int local_8;
  
  pcVar5 = &DAT_0059f162;
  local_14 = (undefined4 *)(&DAT_00522168 + param_1 * 4);
  puVar4 = (undefined4 *)(&DAT_005220a4 + param_1 * 4);
  local_10 = (undefined4 *)(&DAT_00522168 + param_1 * 0x1c);
  puVar3 = (undefined4 *)(&DAT_005220a4 + param_1 * 0x1c);
  iVar1 = param_1 * 0x2d8;
  for (local_8 = 0; local_8 < DAT_004d5aec; local_8 = local_8 + 1) {
    if ('\x02' < (char)(&DAT_0059f161)[iVar1]) {
      *puVar3 = *(undefined4 *)(&DAT_004b56fc + *pcVar5 * 4 + (char)(&DAT_0059f162)[iVar1] * 0x1c);
      if (DAT_004d5a94 == 0) {
        uVar2 = FUN_00404e94(param_1,local_8);
        *puVar3 = uVar2;
      }
      else {
        uVar2 = FUN_00404e00(param_1,local_8);
        *puVar3 = uVar2;
      }
      *local_10 = *puVar3;
    }
    if ('\x02' < pcVar5[-1]) {
      *puVar4 = *(undefined4 *)(&DAT_004b56fc + (char)(&DAT_0059f162)[iVar1] * 4 + *pcVar5 * 0x1c);
      if (DAT_004d5a94 == 0) {
        uVar2 = FUN_00404e94(local_8,param_1);
        *puVar4 = uVar2;
      }
      else {
        uVar2 = FUN_00404e00(local_8,param_1);
        *puVar4 = uVar2;
      }
      *local_14 = *puVar4;
    }
    local_14 = local_14 + 7;
    local_10 = local_10 + 1;
    puVar4 = puVar4 + 7;
    puVar3 = puVar3 + 1;
    pcVar5 = pcVar5 + 0x2d8;
  }
  return;
}

