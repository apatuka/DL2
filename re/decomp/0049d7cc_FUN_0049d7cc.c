// FUN_0049d7cc @ 0049d7cc size=40 sig=undefined FUN_0049d7cc() cc=unknown
// callers: FUN_004a43da
// callees: FUN_00495544

undefined4 FUN_0049d7cc(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_2 + 0x1c) == 6) && (*(int *)(param_2 + 0x94) != 0)) {
    uVar1 = FUN_00495544(*(undefined4 *)(param_2 + 0x94));
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

