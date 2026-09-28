// FUN_0045e4f4 @ 0045e4f4 size=93 sig=undefined FUN_0045e4f4() cc=unknown
// callers: FUN_0043baf4,FUN_0043be98
// callees: FUN_004878a8,FUN_004748dc,FUN_0043ca24,FUN_00483cbc,FUN_0042836c
// strings: \"We have researched all of the technologies we can.  The planet will soon be ours!\"|\"Good News!\"

void FUN_0045e4f4(void)

{
  int iVar1;
  
  if ((DAT_004d5aa0 != '\0') && (iVar1 = FUN_004748dc(), iVar1 != 0)) {
    return;
  }
  if (((DAT_004d5aa0 == '\0') && (PTR_DAT_004d5988[0x3e] == '\0')) &&
     (iVar1 = FUN_00483cbc(PTR_DAT_004d5988,0), iVar1 == 0)) {
    FUN_0042836c(PTR_s_Good_News__0050974c,PTR_s_We_have_researched_all_of_the_te_005096f0,4,0,5);
    return;
  }
  FUN_004878a8();
  FUN_0043ca24();
  return;
}

