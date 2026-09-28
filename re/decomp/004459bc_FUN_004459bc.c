// FUN_004459bc @ 004459bc size=32 sig=undefined FUN_004459bc() cc=unknown
// callers: FUN_00445a04
// callees: 

int FUN_004459bc(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0x48);
  do {
    if (*piVar2 == 0) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 3);
  return -1;
}

