// FUN_004753dc @ 004753dc size=94 sig=undefined FUN_004753dc() cc=unknown
// callers: FUN_004782ec
// callees: 

void FUN_004753dc(int param_1)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  char *pcVar5;
  int local_8;
  
  if ((DAT_0058f1fc != 0) && (DAT_0058f1f4 != DAT_004d5a58)) {
    piVar4 = (int *)&DAT_005220a4;
    local_8 = 0;
    pcVar5 = (char *)(param_1 + 0x18);
    do {
      iVar2 = 0;
      pcVar1 = pcVar5;
      piVar3 = piVar4;
      do {
        *piVar3 = (int)*pcVar1;
        iVar2 = iVar2 + 1;
        piVar3 = piVar3 + 1;
        pcVar1 = pcVar1 + 1;
      } while (iVar2 < 7);
      local_8 = local_8 + 1;
      pcVar5 = pcVar5 + 7;
      piVar4 = piVar4 + 7;
    } while (local_8 < 7);
  }
  return;
}

