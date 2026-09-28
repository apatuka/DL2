// FUN_00445190 @ 00445190 size=60 sig=undefined FUN_00445190() cc=unknown
// callers: FUN_00480150
// callees: DrawSprite

int FUN_00445190(int param_1,int param_2)

{
  for (; (param_1 != 0 && (*(short *)(param_1 + 4) <= param_2)); param_1 = *(int *)(param_1 + 0x38))
  {
    DrawSprite(param_1);
    *(int *)(&DAT_00563fbc + DAT_004c50a8 * 4) = param_1;
    DAT_004c50a8 = DAT_004c50a8 + 1;
  }
  return param_1;
}

