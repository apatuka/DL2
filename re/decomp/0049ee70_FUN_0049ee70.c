// FUN_0049ee70 @ 0049ee70 size=31 sig=undefined FUN_0049ee70() cc=unknown
// callers: FUN_0049f4c2
// callees: 

undefined4 FUN_0049ee70(int param_1)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 0x1c) == 4) || (*(int *)(param_1 + 0x1c) == 6)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

