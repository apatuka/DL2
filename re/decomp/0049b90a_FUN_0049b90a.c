// FUN_0049b90a @ 0049b90a size=69 sig=undefined FUN_0049b90a() cc=unknown
// callers: FUN_0049cb2f,FUN_004a43da
// callees: 

undefined4 FUN_0049b90a(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (((param_3 == 0) || (param_2 == 0)) || (*(int *)(param_2 + 0x1c) != 9)) {
    uVar1 = 0;
  }
  else {
    *(undefined4 *)(param_3 + 8) = *(undefined4 *)(param_2 + 0xe8);
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)(param_2 + 0xec);
    *(undefined4 *)(param_3 + 4) = *(undefined4 *)(param_2 + 0x48);
    *(undefined4 *)(param_3 + 0x10) = *(undefined4 *)(param_2 + 0xf4);
    uVar1 = 1;
  }
  return uVar1;
}

