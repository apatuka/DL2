// FUN_00401eb8 @ 00401eb8 size=140 sig=undefined FUN_00401eb8() cc=unknown
// callers: 
// callees: memset

void FUN_00401eb8(int param_1,int *param_2,int *param_3)

{
  short *psVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int local_8;
  
  memset(param_2,0,0x30);
  memset(param_3,0,0x30);
  local_8 = 0;
  do {
    iVar4 = 0;
    psVar1 = (short *)(&DAT_0059f1d0 + param_1 * 0x2d8 + local_8 * 0x5a);
    piVar2 = param_3;
    piVar3 = param_2;
    do {
      *piVar3 = *piVar3 + (int)*psVar1;
      *piVar2 = *piVar2 + (int)psVar1[0xc];
      iVar4 = iVar4 + 1;
      piVar2 = piVar2 + 1;
      piVar3 = piVar3 + 1;
      psVar1 = psVar1 + 1;
    } while (iVar4 < 0xc);
    local_8 = local_8 + 1;
  } while (local_8 < 6);
  return;
}

