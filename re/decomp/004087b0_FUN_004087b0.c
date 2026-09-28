// FUN_004087b0 @ 004087b0 size=133 sig=undefined FUN_004087b0() cc=unknown
// callers: FUN_00408a88
// callees: FUN_0040233c

void FUN_004087b0(int param_1)

{
  if (((int)(&DAT_0065e3b0)[param_1] < DAT_0065e424) || (DAT_004d5b00 != '\0')) {
    if (((int)(&DAT_0065e3e8)[param_1] < DAT_004d5af8) || (DAT_004d5b00 != '\x02')) {
      if (*(int *)(&DAT_0052222c + param_1 * 4) == 0) {
        FUN_0040233c(param_1,&DAT_004b62f4,0);
      }
      else {
        FUN_0040233c(param_1,&DAT_004b6324,0);
      }
    }
    else {
      FUN_0040233c(param_1,&DAT_004b6384,0);
    }
  }
  else {
    FUN_0040233c(param_1,&DAT_004b6354,0);
  }
  return;
}

