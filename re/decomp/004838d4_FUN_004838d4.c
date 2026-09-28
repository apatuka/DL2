// FUN_004838d4 @ 004838d4 size=40 sig=undefined FUN_004838d4() cc=unknown
// callers: FUN_0043c540,FUN_0043cc5c,FUN_004838fc
// callees: 

int FUN_004838d4(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 1;
  while( true ) {
    if (param_1 == (int *)0x0) {
      return 0;
    }
    if (param_2 == *param_1) break;
    param_1 = (int *)param_1[1];
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

