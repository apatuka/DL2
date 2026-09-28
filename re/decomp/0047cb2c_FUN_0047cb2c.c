// FUN_0047cb2c @ 0047cb2c size=72 sig=undefined FUN_0047cb2c() cc=unknown
// callers: FUN_0047cb74
// callees: 

int FUN_0047cb2c(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = 0;
  piVar3 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *piVar3;
    if ((((iVar1 != 0) && ((*(ushort *)(iVar1 + 2) & 2) != 0)) &&
        ((*(ushort *)(iVar1 + 2) & 4) != 0)) &&
       ((*(short *)(iVar1 + 0x14) == 0 && (*(char *)(iVar1 + 4) == '\x11')))) {
      iVar4 = iVar4 + 1;
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 0xd;
  } while (iVar2 < 0x24);
  return iVar4;
}

