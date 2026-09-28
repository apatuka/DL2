// FUN_0047ca98 @ 0047ca98 size=58 sig=undefined FUN_0047ca98() cc=unknown
// callers: FUN_00485668,_MovePopulation,FUN_0047cb74
// callees: 

undefined4 FUN_0047ca98(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &DAT_00654804;
  do {
    if (*piVar1 == 0) {
      *piVar1 = param_1;
      piVar1[2] = param_3;
      piVar1[1] = param_2;
      return 1;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 7;
  } while (iVar2 < 0x32);
  return 0;
}

