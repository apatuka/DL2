// FUN_00445ee0 @ 00445ee0 size=39 sig=undefined FUN_00445ee0() cc=unknown
// callers: DeleteUnit,FUN_0045c384
// callees: 

undefined4 FUN_00445ee0(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (param_1 == iVar1) break;
    iVar1 = *(int *)(iVar1 + 0x54);
  }
  return 1;
}

