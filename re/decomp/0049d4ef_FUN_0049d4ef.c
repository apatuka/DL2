// FUN_0049d4ef @ 0049d4ef size=96 sig=undefined FUN_0049d4ef() cc=unknown
// callers: FUN_0049ee46
// callees: FUN_0049eafa,FUN_004954f9

undefined4 FUN_0049d4ef(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_0049eafa(param_2);
  if (((iVar1 == 2) || (*(int *)(param_2 + 0x94) == 0)) ||
     (iVar1 = FUN_004954f9(*(undefined4 *)(param_2 + 0x94),param_3), iVar1 == 0)) {
    return 2;
  }
  if ((*(byte *)(iVar1 + 0xc) & 0xc) != 0) {
    return 2;
  }
  if ((*(byte *)(iVar1 + 0xc) & 1) == 0) {
    return 0;
  }
  return 1;
}

