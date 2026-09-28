// FUN_004393e8 @ 004393e8 size=671 sig=undefined FUN_004393e8() cc=unknown
// callers: FUN_004396a0
// callees: UpdateWindow,FUN_0042836c,sprintf,FUN_00488f76,FUN_004a2cb5,FUN_0049eb44,FUN_00436070,FUN_00438f04,FUN_00488a67,FUN_0048db5d,FUN_00436064,FUN_00438b9c,FUN_004a6b48,FUN_00438ef8
// strings: \"custom\\\\\"|\"maps\\\\\"|\"%s%s%s\"|\"'%s' already exists.  Do you want to overwrite it?\"|\"Save Game\"|\"Are you sure you want to delete '%s'?\"|\"Delete Saved Game\"

int FUN_004393e8(void)

{
  int iVar1;
  int local_27c;
  char local_278 [260];
  undefined1 local_174 [360];
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00438ef8();
  iVar1 = FUN_004a2cb5(DAT_004c4788,&local_27c);
  if (((iVar1 == 0) && (local_27c != 0)) && (*(int *)(DAT_004c4788 + 100) == 0)) {
    switch(local_27c) {
    case 5:
      FUN_0049eb44(DAT_004c4788,0xf,1,0xe,0x103,local_278);
      if (local_278[0] != '\0') {
        sprintf(&DAT_005595bd,s__s_s_s_004c47e7,&DAT_005594b4,local_278,&DAT_005595b8);
        iVar1 = FUN_00488f76(&DAT_005595bd);
        if (iVar1 == 0) {
          DAT_004d59a4 = 0;
          return local_27c;
        }
        sprintf(local_174,PTR_s___s__already_exists__Do_you_want_00509a30,local_278);
        iVar1 = FUN_0042836c(PTR_s_Save_Game_00509a2c,local_174,0x18,0,4);
        FUN_00436070();
        FUN_00436064();
        FUN_00438f04();
        FUN_00438ef8();
        if (DAT_004d5978 == (HWND)0x0) {
          UpdateWindow(DAT_004d5974);
        }
        else {
          UpdateWindow(DAT_004d5978);
        }
        if (iVar1 == 1) {
          DAT_004d59a4 = 0;
          return local_27c;
        }
      }
      break;
    case 6:
      FUN_0049eb44(DAT_004c4788,0xf,1,0xe,0x103,local_278);
      sprintf(&DAT_005595bd,s__s_s_s_004c47e7,&DAT_005594b4,local_278,&DAT_005595b8);
      sprintf(local_174,PTR_s_Are_you_sure_you_want_to_delete___00509a28,local_278);
      iVar1 = FUN_0042836c(PTR_s_Delete_Saved_Game_00509a24,local_174,0x18,0,4);
      FUN_00436070();
      FUN_00436064();
      FUN_00438f04();
      FUN_00438ef8();
      if (DAT_004d5978 == (HWND)0x0) {
        UpdateWindow(DAT_004d5974);
      }
      else {
        UpdateWindow(DAT_004d5978);
      }
      if (iVar1 == 1) {
        FUN_00488a67(&DAT_005595bd);
        FUN_00438b9c();
      }
      break;
    case 7:
      DAT_004d59a4 = 0;
      return local_27c;
    case 8:
      DAT_005596c4 = 0;
      FUN_004a6b48(&DAT_005594b4,s_custom__004c47b9,0x104);
      DAT_005595b8 = DAT_004c47c1;
      DAT_005595bc = DAT_004c47c5;
      FUN_00438b9c();
      break;
    case 10:
      DAT_005596c4 = 1;
      FUN_004a6b48(&DAT_005594b4,s_maps__004c47b3,0x104);
      DAT_005595b8 = DAT_004c47ae;
      DAT_005595bc = DAT_004c47b2;
      FUN_00438b9c();
    }
  }
  DAT_004d59a4 = 0;
  return 0;
}

