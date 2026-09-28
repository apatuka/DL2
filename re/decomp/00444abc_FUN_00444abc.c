// FUN_00444abc @ 00444abc size=39 sig=undefined FUN_00444abc() cc=unknown
// callers: FUN_00444ae4,FUN_00444fd4
// callees: 

undefined4 FUN_00444abc(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_00561a30;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (param_1 == iVar1) break;
    iVar1 = *(int *)(iVar1 + 0x38);
  }
  return 1;
}

