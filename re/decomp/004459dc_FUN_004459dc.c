// FUN_004459dc @ 004459dc size=40 sig=undefined FUN_004459dc() cc=unknown
// callers: FUN_00445a04
// callees: 

undefined4 FUN_004459dc(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(param_1 + 0x48);
  do {
    if (param_2 == *piVar1) {
      return 1;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 3);
  return 0;
}

