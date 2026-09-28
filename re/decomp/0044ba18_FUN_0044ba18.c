// FUN_0044ba18 @ 0044ba18 size=38 sig=undefined FUN_0044ba18() cc=unknown
// callers: FUN_0041db10,FUN_004021e0,FUN_0044f3f0,FUN_0044bddc,GetBuildingTasks,FUN_0045cd88,FUN_00448700,FUN_0047d068,FUN_004038c4,FUN_00403970,MoveLaborToHousingNoNet,FUN_0040668c,FUN_00480be0,FUN_0044c320,FUN_004068f8,_MovePopulation,FUN_0040548c,FUN_0045b448,FUN_0044c8ac,FUN_004483d0,FUN_0046bdfc,FUN_0044c2c0,MoveHousingLabor,FUN_0040f584,FUN_004067d0,FUN_00406538,FUN_004522c6,MoveLaborToHousing,FUN_004020c4
// callees: 

int FUN_0044ba18(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = 0;
    iVar3 = 0;
    piVar2 = (int *)(param_1 + 0x18);
    do {
      iVar1 = iVar1 + *piVar2;
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < 5);
  }
  return iVar1;
}

