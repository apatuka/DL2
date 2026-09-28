// FUN_004023dc @ 004023dc size=37 sig=undefined FUN_004023dc() cc=unknown
// callers: FUN_0044c754,MoveLaborToHousingNoNet,FUN_004489e0,FUN_0040668c,FUN_004067d0,FUN_00403a10,FUN_004484fc,FUN_004020c4,FUN_0044c8ac,FUN_0040548c,FUN_0044bacc,FUN_00406538,MoveHousingLabor,FUN_004487b8,FUN_00402010,FUN_0046bdfc,FUN_00403970,FUN_004031b0,FUN_0040552c,MoveLaborToHousing,FUN_00448700,FUN_004021e0,FUN_004068f8,FUN_004485e8,FUN_0041ccb0,FUN_0044b7d8,FUN_0040854c,FUN_0044bea8
// callees: 

int FUN_004023dc(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = 0;
  pcVar2 = (char *)(param_1 + 0x2c);
  do {
    if (param_2 == *pcVar2) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 1;
  } while (iVar1 < 5);
  return -1;
}

