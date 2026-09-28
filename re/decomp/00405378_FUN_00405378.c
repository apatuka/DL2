// FUN_00405378 @ 00405378 size=181 sig=undefined FUN_00405378() cc=unknown
// callers: WinMain
// callees: memset,FUN_0047549c

void FUN_00405378(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  int iVar5;
  int *piVar6;
  int *local_14;
  
  memset(&DAT_00522248,0,0x1c);
  memset(&DAT_00522264,0,0x1c);
  if ((DAT_0058f1fc == 0) || (DAT_0058f1f4 == DAT_004d5a58)) {
    local_14 = (int *)&DAT_005220a4;
    piVar6 = (int *)&DAT_00522168;
    pcVar4 = &DAT_0059f161;
    for (iVar5 = 0; iVar5 < DAT_004d5aec; iVar5 = iVar5 + 1) {
      if ('\x02' < *pcVar4) {
        piVar1 = local_14;
        piVar3 = piVar6;
        for (iVar2 = 0; iVar2 < DAT_004d5aec; iVar2 = iVar2 + 1) {
          if (*piVar1 < *piVar3) {
            *piVar1 = *piVar1 + 1;
          }
          else if (*piVar3 < *piVar1) {
            *piVar1 = *piVar1 + -1;
          }
          piVar3 = piVar3 + 1;
          piVar1 = piVar1 + 1;
        }
      }
      local_14 = local_14 + 7;
      piVar6 = piVar6 + 7;
      pcVar4 = pcVar4 + 0x2d8;
    }
    if (DAT_0058f1fc != 0) {
      FUN_0047549c();
    }
  }
  return;
}

