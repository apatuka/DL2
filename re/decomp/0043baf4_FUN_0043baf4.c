// FUN_0043baf4 @ 0043baf4 size=478 sig=undefined FUN_0043baf4() cc=unknown
// callers: FUN_0044930c
// callees: FUN_00421878,FUN_0042836c,FUN_0043b7e4,FUN_0043b83c,FUN_0045e7a4,FUN_0045ae78,FUN_004a2cb5,FUN_00473038,FUN_0045e554,FUN_0045ea44,FUN_0045e6d0,FUN_00418d18,FUN_0045e794,FUN_00418cf4,FUN_00419678,FUN_0045ef64,FUN_004197dc,FUN_00426594,FUN_0043b754,FUN_004158d0,FUN_0042b280,FUN_0045e6b4,FUN_0045e4f4,FUN_0045ad98,FUN_00423904,FUN_004164e8,FUN_0043a984,FUN_0043ba98,FUN_0045b304
// strings: \"You must be in the Settlement View in order to place buildings.\"|\"Building Button Disabled\"|\"The ALLOW ALLIANCES option was not selected during game setup phase.\"|\"Pacts Button Disabled\"

undefined8 FUN_0043baf4(void)

{
  int iVar1;
  int local_8;
  
  iVar1 = FUN_004a2cb5(DAT_004c48a0,&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004c48a0 + 100) == 0)) {
    switch(local_8) {
    case 3:
      FUN_00426594(&DAT_004d4d64);
      break;
    case 4:
      FUN_00419678();
      FUN_004197dc(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,0);
      FUN_00418d18();
      FUN_00418cf4();
      break;
    case 5:
      FUN_0045e7a4();
      break;
    case 6:
      FUN_004164e8();
      break;
    case 7:
      if (DAT_004d59b4 == 1) {
        FUN_0045ef64();
      }
      else {
        FUN_0042836c(PTR_s_Building_Button_Disabled_00509d68,
                     PTR_s_You_must_be_in_the_Settlement_Vi_00509d6c,4,0,9);
      }
      break;
    case 8:
      if (DAT_004d5af4 == 0) {
        FUN_0042836c(PTR_s_Pacts_Button_Disabled_00509d60,
                     PTR_s_The_ALLOW_ALLIANCES_option_was_n_00509d64,4,0,9);
      }
      else {
        FUN_0042b280();
      }
      break;
    case 9:
      FUN_00423904();
      break;
    case 10:
      FUN_0045e4f4();
      break;
    case 0xb:
      FUN_0045e6b4(0);
      break;
    case 0xc:
      FUN_0045ae78();
      FUN_0043b7e4();
      FUN_0043b754();
      break;
    case 0xd:
      FUN_0045ad98(&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
      break;
    case 0xe:
      FUN_0045e794();
      break;
    case 0xf:
      FUN_0043ba98();
      FUN_0045b304();
      FUN_0043b7e4();
      FUN_0043b754();
      break;
    case 0x10:
      FUN_0045e6d0();
      FUN_0043b7e4();
      FUN_0043b754();
      break;
    case 0x11:
      FUN_0043a984();
      break;
    case 0x12:
      FUN_00421878();
      break;
    case 0x13:
      FUN_004158d0();
      FUN_0043b7e4();
      FUN_0043b754();
      break;
    case 0x15:
      if (DAT_004d5aa0 == '\0') {
        FUN_0045e554();
      }
      else {
        FUN_00473038();
      }
      break;
    case 0x16:
      FUN_0043b83c();
      FUN_0043b7e4();
      FUN_0043b754();
      break;
    case 0x2e:
      FUN_0045ea44();
      break;
    case 0x2f:
      FUN_0045e6b4(1);
    }
  }
  return CONCAT44(local_8,iVar1);
}

