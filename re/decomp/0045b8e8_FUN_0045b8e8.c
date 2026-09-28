// FUN_0045b8e8 @ 0045b8e8 size=133 sig=undefined FUN_0045b8e8() cc=unknown
// callers: FUN_0045bc10
// callees: FUN_0041ccb0,FUN_00482f94,FUN_0042836c,FUN_00449dec
// strings: \"You are not able to change the production of your opponent's buildings.\\n\\nHowever, congratulations on your clever idea!\"|\"Oolan's Advice\"

void FUN_0045b8e8(int param_1)

{
  if ((param_1 == 0) || (*(char *)(param_1 + 4) != '&')) {
    if ((param_1 == 0) ||
       ((DAT_004d5aa0 == '\0' &&
        ((&DAT_005a4436)[DAT_0058f1f4 + *(short *)(param_1 + 8) * 0xadc] != '\x04')))) {
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_are_not_able_to_change_the_p_005096b0,4,0
                   ,9);
    }
    else if ((*(byte *)(param_1 + 2) & 2) != 0) {
      FUN_0041ccb0(param_1);
      FUN_00482f94(PTR_DAT_004d5988);
      FUN_00449dec();
    }
  }
  return;
}

