// FUN_0041a14c @ 0041a14c size=183 sig=undefined FUN_0041a14c() cc=unknown
// callers: FUN_0044ae10
// callees: FUN_00419c88,FUN_004196e4,FUN_004593a4,FUN_004590f0

void FUN_0041a14c(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  cVar1 = FUN_00419c88(param_1,param_2,local_8,local_c);
  if (cVar1 != '\0') {
    if (DAT_005332b0 != '\0') {
      FUN_004196e4();
    }
    iVar4 = 0;
    pcVar5 = &DAT_00533405;
    for (iVar6 = 0; (iVar4 == 0 && (iVar6 != 100)); iVar6 = iVar6 + 1) {
      if (*pcVar5 == '\0') {
        piVar2 = (int *)(pcVar5 + -0x12d);
        for (iVar3 = 0; (iVar4 == 0 && (iVar3 != 10)); iVar3 = iVar3 + 1) {
          if (*piVar2 == 1) {
            iVar4 = piVar2[1];
          }
          piVar2 = piVar2 + 8;
        }
      }
      pcVar5 = pcVar5 + 0x146;
    }
    if (iVar4 != 0) {
      iVar4 = FUN_004593a4((int)*(char *)(iVar4 + 8),(int)*(char *)(iVar4 + 6));
      FUN_004590f0(DAT_004d5974,*(undefined4 *)(iVar4 + 8),param_1,param_2,
                   (int)*(short *)(iVar4 + 4),(int)*(short *)(iVar4 + 6),0,FUN_00419f50);
    }
  }
  return;
}

