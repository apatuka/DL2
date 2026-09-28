// FUN_004a8257 @ 004a8257 size=69 sig=undefined FUN_004a8257() cc=unknown
// callers: 
// callees: FUN_004a7502

int * FUN_004a8257(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(param_1 + 8);
  while( true ) {
    if (*piVar2 == 0) {
      return (int *)0x0;
    }
    if (piVar2[1] == 0) break;
    iVar1 = FUN_004a7502(*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),piVar2[1],
                         *(undefined4 *)(param_2 + 0xc),0);
    if (iVar1 != 0) {
      return piVar2;
    }
    piVar2 = piVar2 + 5;
  }
  return piVar2;
}

