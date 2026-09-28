// FUN_0040e994 @ 0040e994 size=94 sig=undefined FUN_0040e994() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_0040c668,FUN_0040e8f0,FUN_0040bbf4,FUN_0040bfb4,FUN_0040beb4

void FUN_0040e994(int param_1)

{
  int iVar1;
  
  FUN_0040bfb4(param_1,1);
  FUN_0040bfb4(param_1,0xf);
  iVar1 = FUN_0040c668(param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_0040e8f0(param_1,iVar1);
    *(int *)(param_1 + 0x10) = iVar1;
    if ((iVar1 == 0) || (*(int *)(iVar1 + 0x978 + *(short *)(param_1 + 10) * 4) != -1)) {
      FUN_0040beb4(param_1);
    }
    else {
      FUN_0040bbf4(param_1,0,0);
    }
  }
  return;
}

