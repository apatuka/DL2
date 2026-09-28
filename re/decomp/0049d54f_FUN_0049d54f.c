// FUN_0049d54f @ 0049d54f size=60 sig=undefined FUN_0049d54f() cc=unknown
// callers: FUN_004a43da
// callees: FUN_004954f9

int FUN_0049d54f(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (*(int *)(param_2 + 0x94) != 0) {
    for (iVar1 = FUN_004954f9(*(undefined4 *)(param_2 + 0x94),param_3);
        (iVar1 != 0 && ((*(byte *)(iVar1 + 0xc) & 1) == 0)); iVar1 = *(int *)(iVar1 + 4)) {
      param_3 = param_3 + 1;
    }
  }
  return param_3;
}

