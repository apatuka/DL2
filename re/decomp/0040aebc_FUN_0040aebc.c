// FUN_0040aebc @ 0040aebc size=77 sig=undefined FUN_0040aebc() cc=unknown
// callers: FUN_0040af0c,FUN_0040e6e4,FUN_0040b994,FUN_00460fa4
// callees: 

void FUN_0040aebc(int param_1)

{
  int *piVar1;
  int iVar2;
  short *psVar3;
  
  iVar2 = 0;
  psVar3 = (short *)(param_1 + 0x24);
  piVar1 = (int *)(param_1 + 0x44);
  do {
    if ((*piVar1 != 0) &&
       ((*(short *)*piVar1 != *psVar3 ||
        ((int)(char)((short *)*piVar1)[4] != (int)*(short *)(param_1 + 10))))) {
      *piVar1 = 0;
      *psVar3 = 0;
    }
    iVar2 = iVar2 + 1;
    psVar3 = psVar3 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 0x10);
  return;
}

