// FUN_00423380 @ 00423380 size=66 sig=undefined FUN_00423380() cc=unknown
// callers: 
// callees: FUN_0042278c

int FUN_00423380(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0042278c(*param_1);
  iVar2 = FUN_0042278c(*param_2);
  iVar1 = (int)*(short *)(&DAT_004fc90c + iVar2 * 0x12) -
          (int)*(short *)(&DAT_004fc90c + iVar1 * 0x12);
  if (iVar1 == 0) {
    iVar1 = -1;
  }
  return iVar1;
}

