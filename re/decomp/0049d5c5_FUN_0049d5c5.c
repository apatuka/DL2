// FUN_0049d5c5 @ 0049d5c5 size=24 sig=undefined FUN_0049d5c5() cc=unknown
// callers: FUN_004a43da
// callees: 

undefined4 FUN_0049d5c5(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_2 + 0x70) == 0) {
    uVar1 = *(undefined4 *)(param_2 + 0x18);
  }
  else {
    uVar1 = *(undefined4 *)(param_2 + 0x70);
  }
  return uVar1;
}

