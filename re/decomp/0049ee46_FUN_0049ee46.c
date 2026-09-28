// FUN_0049ee46 @ 0049ee46 size=42 sig=undefined FUN_0049ee46() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049d4ef

undefined4 FUN_0049ee46(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_2 + 0x1c) == 4) || (*(int *)(param_2 + 0x1c) != 6)) {
    uVar1 = 2;
  }
  else {
    uVar1 = FUN_0049d4ef(param_1,param_2,param_3);
  }
  return uVar1;
}

