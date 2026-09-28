// FUN_0041b908 @ 0041b908 size=43 sig=undefined FUN_0041b908() cc=unknown
// callers: FUN_0041db10,FUN_0041e26c,FUN_0041bd60,FUN_004213fc,FUN_0041c418,FUN_004217a0,FUN_00421178,FUN_0041e440,CheckColonyAssistant
// callees: 

void FUN_0041b908(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  piVar2 = &DAT_004b7760;
  do {
    iVar3 = 0;
    piVar1 = piVar2;
    do {
      if (*piVar1 == 1) {
        *piVar1 = 2;
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar3 < 0xd);
    iVar4 = iVar4 + 1;
    piVar2 = piVar2 + 0xd;
  } while (iVar4 < 4);
  return;
}

