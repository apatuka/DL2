// FUN_00401558 @ 00401558 size=84 sig=undefined FUN_00401558() cc=unknown
// callers: FUN_00409964,FUN_0040a2a4,FUN_0040a5a4
// callees: 

int FUN_00401558(int param_1)

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
    if ((iVar1 != 0) && ((&DAT_004f9dc3)[*(char *)(iVar1 + 4) * 0x32] != '\x11')) {
      iVar4 = iVar4 + (char)(&DAT_004f9dc4)[*(char *)(iVar1 + 4) * 0x32];
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 0xd;
  } while (iVar2 < 0x24);
  return iVar4;
}

