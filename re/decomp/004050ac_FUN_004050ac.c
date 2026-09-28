// FUN_004050ac @ 004050ac size=277 sig=undefined FUN_004050ac() cc=unknown
// callers: RaceInit,FUN_00474718,ChCht,FUN_0047958c
// callees: memset,FUN_00404e00,FUN_00404e94

void FUN_004050ac(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  char *local_24;
  undefined4 *local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  
  memset(&DAT_00522168,0,0xc4);
  memset(&DAT_005220a4,0,0xc4);
  local_14 = (undefined4 *)&DAT_005220a4;
  local_18 = (undefined4 *)&DAT_00522168;
  local_24 = &DAT_0059f161;
  for (iVar5 = 0; iVar5 < DAT_004d5aec; iVar5 = iVar5 + 1) {
    if (('\x02' < *local_24) || ((DAT_004d5aa0 != '\0' && (iVar5 != DAT_0058f1f4)))) {
      pcVar3 = &DAT_0059f162;
      local_1c = local_18;
      puVar2 = local_14;
      for (iVar4 = 0; iVar4 < DAT_004d5aec; iVar4 = iVar4 + 1) {
        *puVar2 = *(undefined4 *)(&DAT_004b56fc + *pcVar3 * 4 + local_24[1] * 0x1c);
        if (DAT_004d5a94 == 0) {
          uVar1 = FUN_00404e94(iVar5,iVar4);
          *puVar2 = uVar1;
        }
        else {
          uVar1 = FUN_00404e00(iVar5,iVar4);
          *puVar2 = uVar1;
        }
        uVar1 = *puVar2;
        puVar2 = puVar2 + 1;
        *local_1c = uVar1;
        local_1c = local_1c + 1;
        pcVar3 = pcVar3 + 0x2d8;
      }
    }
    local_14 = local_14 + 7;
    local_18 = local_18 + 7;
    local_24 = local_24 + 0x2d8;
  }
  return;
}

