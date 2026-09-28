// FUN_00441bf4 @ 00441bf4 size=49 sig=undefined FUN_00441bf4() cc=unknown
// callers: FUN_00427854,FUN_00485668,FUN_00427ab0
// callees: 

int FUN_00441bf4(int param_1)

{
  short *psVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = 0;
  psVar1 = (short *)(param_1 + 0x142);
  do {
    if ((*psVar1 != 0xff) && (*psVar1 != 5)) {
      iVar3 = iVar3 + 1;
    }
    iVar2 = iVar2 + 1;
    psVar1 = psVar1 + 0x1a;
  } while (iVar2 < 0x24);
  return iVar3;
}

