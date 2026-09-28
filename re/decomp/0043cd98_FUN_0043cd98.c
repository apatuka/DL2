// FUN_0043cd98 @ 0043cd98 size=177 sig=undefined FUN_0043cd98() cc=unknown
// callers: CheckTechTree
// callees: LoadStringA,FUN_0043a568,FUN_0043c540

void FUN_0043cd98(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  CHAR local_8d4 [1064];
  CHAR local_4ac [1064];
  CHAR local_84 [128];
  
  iVar1 = 1;
  piVar2 = &DAT_004fbbf6;
  iVar3 = 0;
  do {
    if (param_1 == *piVar2) {
      iVar3 = iVar1;
    }
    iVar1 = iVar1 + 1;
    piVar2 = (int *)((int)piVar2 + 0x32);
  } while (iVar1 < 0x30);
  LoadStringA(DAT_0058f19c,(int)*(short *)(iVar3 * 0x24 + 0x4d2dc0),local_84,0x7f);
  LoadStringA(DAT_0058f19c,(int)*(short *)(iVar3 * 0x24 + 0x4d2dc2),local_4ac,0x427);
  LoadStringA(DAT_0058f19c,(int)*(short *)(iVar3 * 0x24 + 0x4d2dc4),local_8d4,0x427);
  FUN_0043a568(local_84,local_4ac,local_8d4,iVar3 + -1);
  FUN_0043c540();
  return;
}

