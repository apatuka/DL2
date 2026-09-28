// FUN_004a54b0 @ 004a54b0 size=53 sig=undefined FUN_004a54b0() cc=unknown
// callers: FUN_004a54e5
// callees: FUN_004989de

void FUN_004a54b0(short *param_1)

{
  short *psVar1;
  int iVar2;
  
  psVar1 = param_1 + 6;
  iVar2 = (int)*param_1;
  while (iVar2 != 0) {
    if (*(int *)(psVar1 + 2) != 0) {
      FUN_004989de(*(undefined4 *)(psVar1 + 2));
      psVar1[2] = 0;
      psVar1[3] = 0;
    }
    psVar1 = psVar1 + 4;
    iVar2 = iVar2 + -1;
  }
  return;
}

