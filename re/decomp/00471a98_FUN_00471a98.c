// FUN_00471a98 @ 00471a98 size=135 sig=undefined FUN_00471a98() cc=unknown
// callers: FUN_00472974
// callees: 

void FUN_00471a98(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (DAT_004d6330 <= iVar1) {
      (&DAT_006520a8)[iVar1 * 5] = (int)*(short *)(param_2 + 0x1a);
      (&DAT_006520ac)[iVar1 * 5] = (int)*(short *)(param_1 + 0x1a);
      (&DAT_006520b0)[iVar1 * 5] = param_3;
      (&DAT_006520b4)[iVar1 * 5] = param_4;
      (&DAT_006520b8)[iVar1 * 5] = param_5;
      DAT_004d6330 = DAT_004d6330 + 1;
      return;
    }
    if ((((int)*(short *)(param_2 + 0x1a) == (&DAT_006520a8)[iVar1 * 5]) &&
        ((int)*(short *)(param_1 + 0x1a) == (&DAT_006520ac)[iVar1 * 5])) &&
       ((&DAT_006520b0)[iVar1 * 5] == param_3)) break;
    iVar1 = iVar1 + 1;
  }
  (&DAT_006520b4)[iVar1 * 5] = (&DAT_006520b4)[iVar1 * 5] + param_4;
  (&DAT_006520b8)[iVar1 * 5] = (&DAT_006520b8)[iVar1 * 5] + param_5;
  return;
}

