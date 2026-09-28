// FUN_0046b910 @ 0046b910 size=71 sig=undefined FUN_0046b910() cc=unknown
// callers: FUN_0046bc28,FUN_0046ab18,FUN_0046b9a0,FUN_004489e0
// callees: 

int FUN_0046b910(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0;
  piVar2 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *piVar2;
    if (((iVar1 != 0) && (*(short *)(iVar1 + 0x14) == 0)) && ((*(byte *)(iVar1 + 2) & 4) != 0)) {
      iVar4 = iVar4 + (char)(&DAT_004f9dc8)[*(char *)(iVar1 + 4) * 0x32];
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 0xd;
  } while (iVar3 < 0x24);
  return iVar4;
}

