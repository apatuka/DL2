// FUN_0042d574 @ 0042d574 size=83 sig=undefined FUN_0042d574() cc=unknown
// callers: FUN_0042e080
// callees: FUN_0049eb44
// strings: \"(Fair Fight) The normal level.  There are no modifications to your play at this level and your score is calculated without adjustments.\"

void FUN_0042d574(void)

{
  if (DAT_004d5aa0 != '\0') {
    FUN_0049eb44(DAT_004c3668,0x13,1,0xf,0,
                 (&PTR_s__Hog_Tied__The_most_difficult_le_005093f8)[DAT_004c3670]);
    return;
  }
  FUN_0049eb44(DAT_004c3668,0x13,1,0xf,0,
               (&PTR_s__Hog_Tied__The_most_difficult_le_005093f8)
               [(char)(&DAT_005a0548)[DAT_00557c7c]]);
  return;
}

