// FUN_00445a04 @ 00445a04 size=110 sig=undefined FUN_00445a04() cc=unknown
// callers: FUN_00446084,FUN_00445d30,FUN_00431e58
// callees: FUN_00445940,FUN_004459dc,FUN_004459bc,FUN_0040cd0c

undefined4 FUN_00445a04(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00445940(param_1);
  if (iVar1 != 0) {
    iVar2 = FUN_004459dc(iVar1,param_1);
    if (iVar2 != 0) {
      return 1;
    }
    if ((*(short *)(iVar1 + 0x36) != *(short *)(param_1 + 0x36)) && (DAT_0058f1f4 == DAT_004d5a58))
    {
      FUN_0040cd0c(iVar1,param_1);
    }
    iVar2 = FUN_004459bc(iVar1);
    if (iVar2 != -1) {
      *(undefined4 *)(param_1 + 0x44) = 0;
      *(int *)(param_1 + 0x48) = iVar1;
      *(int *)(iVar1 + 0x48 + iVar2 * 4) = param_1;
      return 1;
    }
  }
  return 0;
}

