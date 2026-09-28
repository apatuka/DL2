// FUN_0049d58b @ 0049d58b size=58 sig=undefined FUN_0049d58b() cc=unknown
// callers: FUN_004a43da
// callees: FUN_00491a2b,FUN_0049eb9f,FUN_00491ace

int FUN_0049d58b(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 0x6c);
  if (iVar1 == 0) {
    FUN_00491a2b(0);
    FUN_0049eb9f(param_2,0);
    iVar1 = DAT_0065ebfc + DAT_0065ec00 + 4;
    FUN_00491ace();
  }
  return iVar1;
}

