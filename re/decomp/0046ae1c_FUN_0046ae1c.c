// FUN_0046ae1c @ 0046ae1c size=128 sig=undefined FUN_0046ae1c() cc=unknown
// callers: FUN_0046ab18,FUN_00436a44,FUN_0046c728
// callees: FUN_0046adac,FUN_0046a9d8,FUN_0044d1e4

int FUN_0046ae1c(char *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (((param_1 != (char *)0x0) && (param_2 != 0)) && (*param_1 == *(char *)(param_2 + 0x20))) {
    iVar2 = FUN_0046adac(param_1,param_2);
    iVar1 = FUN_0046a9d8((int)*(short *)(param_2 + 0x30));
    iVar2 = ((int)*(short *)(&DAT_00559f6c + param_1[2] * 2) *
            ((iVar1 * *(int *)(&DAT_004d5838 + iVar2 * 4)) / 100)) / 100;
    iVar1 = FUN_0044d1e4(param_2,9,0);
    if (iVar1 != -1) {
      iVar2 = iVar2 * 2;
    }
  }
  if (DAT_004d5b08 != 0) {
    iVar2 = iVar2 * 2;
  }
  return iVar2;
}

