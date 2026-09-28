// SelectInit @ 00427008 size=247 sig=undefined SelectInit() cc=unknown
// callers: FUN_004272f8
// callees: FUN_00426cd8,FUN_0046c9d8,FUN_00426d54
// strings: \"SelectInit\"

/* auto-named from string evidence: SelectInit */

bool SelectInit(void)

{
  int iVar1;
  
  DAT_004d5a7c = 1;
  FUN_00426cd8();
  DAT_004b7d58 = PTR_s_Select_Landing_Sites_005095b8;
  DAT_00557784 = (uint)(DAT_004d5aa0 != '\0');
  DAT_00557578 = 0;
  if (DAT_004d5aa0 == '\0') {
    if (DAT_004d5a50 == 0) {
      if (((DAT_004d5b0c == 0) || (DAT_004d5b0c == 1)) || (DAT_004d5b0c == 2)) {
        iVar1 = DAT_004d5aec * 3;
        if (iVar1 < 0) {
          iVar1 = iVar1 + 3;
        }
        DAT_0055778c = iVar1 >> 2;
      }
      DAT_0055778c = FUN_0046c9d8(DAT_004d5aec,s_SelectInit_004b7d74);
    }
    else {
      DAT_0055778c = DAT_004d5aec + -1;
    }
  }
  else {
    DAT_0055778c = DAT_004d5aec + -1;
  }
  DAT_00557580 = *(int *)(&DAT_00557c54 + DAT_0055778c * 4);
  DAT_00557788 = DAT_00557580;
  FUN_00426d54();
  return DAT_00557788 == DAT_0058f1f4;
}

