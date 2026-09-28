// FUN_0040b000 @ 0040b000 size=114 sig=undefined FUN_0040b000() cc=unknown
// callers: FUN_00401ac0,FUN_0040c018,FUN_0040beb4
// callees: 

void FUN_0040b000(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 1;
  piVar2 = (int *)(param_1 + 0x88);
  do {
    if (*piVar2 == 0) {
      *piVar2 = (param_2 - (int)(&DAT_00522584 + *(short *)(param_2 + 10) * 0x2648)) / 0xc4 + 1;
      break;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0x10);
  *(int *)(param_2 + 0x84) =
       (param_1 - (int)(&DAT_00522584 + *(short *)(param_1 + 10) * 0x2648)) / 0xc4 + 1;
  return;
}

