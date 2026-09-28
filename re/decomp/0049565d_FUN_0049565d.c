// FUN_0049565d @ 0049565d size=42 sig=undefined FUN_0049565d() cc=unknown
// callers: FUN_00495687
// callees: 

int * FUN_0049565d(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0x34);
  while( true ) {
    if ((piVar1 == (int *)0x0) || (*piVar1 == 0)) {
      return (int *)0x0;
    }
    if ((piVar1[5] <= param_2) && (param_2 <= piVar1[6])) break;
    piVar1 = piVar1 + 8;
  }
  return piVar1;
}

