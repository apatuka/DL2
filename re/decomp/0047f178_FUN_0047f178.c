// FUN_0047f178 @ 0047f178 size=95 sig=undefined FUN_0047f178() cc=unknown
// callers: FUN_00480150
// callees: BlitSprite8

void FUN_0047f178(int param_1,int param_2,int param_3)

{
  short *psVar1;
  
  psVar1 = &DAT_004e245c + *(int *)(&DAT_004dccc0 + param_3 * 4) * 8;
  if ((&DAT_004e2464)[*(int *)(&DAT_004dccc0 + param_3 * 4) * 4] == 0) {
    psVar1 = &DAT_004e245c;
  }
  if (*(int *)(psVar1 + 4) != 0) {
    BlitSprite8(*(int *)(psVar1 + 4),param_1 + *psVar1 + 0x32,param_2 + psVar1[1] + 0x32,
                (int)psVar1[2],(int)psVar1[3],(int)psVar1[2],0);
  }
  return;
}

