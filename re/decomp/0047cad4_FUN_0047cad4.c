// FUN_0047cad4 @ 0047cad4 size=47 sig=undefined FUN_0047cad4() cc=unknown
// callers: CreateRandomEvents
// callees: 

undefined4 FUN_0047cad4(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = &DAT_00654804;
  do {
    if (*piVar1 == 0) {
      *piVar1 = param_1;
      piVar1[2] = 0;
      return 1;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 7;
  } while (iVar2 < 0x32);
  return 0;
}

