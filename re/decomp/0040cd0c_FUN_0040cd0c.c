// FUN_0040cd0c @ 0040cd0c size=146 sig=undefined FUN_0040cd0c() cc=unknown
// callers: FUN_00445a04
// callees: RemoveArmyFromTaskForce,FUN_00475854,FUN_00416ca4,FUN_0040b0c0

void FUN_0040cd0c(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  
  if (*(short *)(param_1 + 0x36) != 0) {
    piVar3 = (int *)(&DAT_005224c0 +
                    *(char *)(param_1 + 8) * 0x2648 + *(short *)(param_1 + 0x36) * 0xc4);
    if ((((*piVar3 == 3) || (*piVar3 == 9)) &&
        ((cVar1 = *(char *)(param_2 + 7), cVar1 == '\x01' ||
         ((cVar1 == '\x02' || (cVar1 == '\x06')))))) ||
       ((*piVar3 == 4 && (iVar2 = FUN_00416ca4(param_2), iVar2 != 0)))) {
      RemoveArmyFromTaskForce(param_2);
      FUN_0040b0c0(piVar3,param_2);
    }
    else {
      RemoveArmyFromTaskForce(param_2);
      FUN_00475854(param_2);
    }
    return;
  }
  RemoveArmyFromTaskForce(param_2);
  FUN_00475854(param_2);
  return;
}

