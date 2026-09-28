// FUN_0043210c @ 0043210c size=517 sig=undefined FUN_0043210c() cc=unknown
// callers: CheckSubUnit,CheckSubInfo
// callees: FUN_004312fc,FUN_0049eb44,FUN_00431398,FUN_0042836c,FUN_0043239c,FUN_004a3de6,FUN_00432d30,FUN_004a2004,FUN_00414f04,sprintf,FUN_00431534
// strings: \"%d Cr.\"|\"Lately our sources have not supplied us with any new technologies.  We promise that this situation will change.  Please contact us again.\"|\"No Technologies Are Available\"

void FUN_0043210c(void)

{
  char cVar1;
  undefined1 local_64 [80];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004c42dc = FUN_004a3de6(0,0x31313944);
  FUN_00414f04(DAT_004c42dc);
  DAT_00558d58 = 2;
  FUN_004a2004(DAT_004c42dc);
  FUN_00432d30();
  FUN_0049eb44(DAT_004c42dc,0xb,1,0xb,1,0);
  FUN_0049eb44(DAT_004c42dc,1,1,7,0,FUN_00431258);
  if ((DAT_004c42e8 == 0) ||
     ((((DAT_004d5ac4 == 0 && (DAT_004d5ab0 != 0)) && (DAT_004d5aa8 != 0)) && (DAT_004d59ac != 0))))
  {
    FUN_0049eb44(DAT_004c42dc,3,1,0xf,0,&DAT_004c4588);
  }
  else {
    FUN_0049eb44(DAT_004c42dc,3,1,0xf,0,DAT_004c42e8);
  }
  cVar1 = FUN_0043239c();
  if (cVar1 == '\0') {
    FUN_0049eb44(DAT_004c42dc,0xc,1,10,1,0);
  }
  else {
    FUN_0049eb44(DAT_004c42dc,0xc,1,10,0,0);
  }
  FUN_00431398();
  sprintf(local_64,s__d_Cr__004c4599,(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6]);
  FUN_0049eb44(DAT_004c42dc,2,1,0xf,0,local_64);
  if ((DAT_004c42e4 != 0) && (DAT_004c42ec == 0)) {
    local_14 = 10000;
    local_10 = 10000;
    local_c = 0x27d8;
    local_8 = 0x27d8;
    FUN_0049eb44(DAT_004c42dc,0xd,1,0xd,0,&local_14);
  }
  if (DAT_00558e60 == 0) {
    DAT_004c4504 = 0xffffffff;
    FUN_0042836c(PTR_s_No_Technologies_Are_Available_00509568,
                 PTR_s_Lately_our_sources_have_not_supp_0050956c,4,0,0x15);
  }
  else {
    FUN_0049eb44(DAT_004c42dc,0x14,1,7,0,FUN_004316d8);
    FUN_004312fc();
    FUN_00431534(DAT_00558de0);
    FUN_0049eb44(DAT_004c42dc,0x14,1,0x1b,0,0);
  }
  return;
}

