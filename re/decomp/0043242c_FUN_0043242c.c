// FUN_0043242c @ 0043242c size=481 sig=undefined FUN_0043242c() cc=unknown
// callers: CheckSubTech,CheckSubInfo
// callees: FUN_00432014,FUN_0049eb44,FUN_0042836c,FUN_0043239c,FUN_004a3de6,FUN_00432d30,FUN_004a2004,FUN_00414f04,sprintf,FUN_00431f58,FUN_00431734
// strings: \"%d Cr.\"|\"Please accept our many regrets, but we have no units to sell you at this time.  Call us later.\"|\"No Units Are Available\"

void FUN_0043242c(void)

{
  char cVar1;
  undefined1 local_64 [80];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_004c42e0 = FUN_004a3de6(0,0x32313944);
  FUN_00414f04(DAT_004c42e0);
  DAT_00558d58 = 3;
  FUN_004a2004(DAT_004c42e0);
  FUN_00432d30();
  FUN_0049eb44(DAT_004c42e0,0xc,1,0xb,1,0);
  FUN_0049eb44(DAT_004c42e0,1,1,7,0,FUN_00431258);
  if ((DAT_004c42e8 == 0) ||
     ((((DAT_004d5ac4 == 0 && (DAT_004d5ab0 != 0)) && (DAT_004d5aa8 != 0)) && (DAT_004d59ac != 0))))
  {
    FUN_0049eb44(DAT_004c42e0,4,1,0xf,0,&DAT_004c4588);
  }
  else {
    FUN_0049eb44(DAT_004c42e0,4,1,0xf,0,DAT_004c42e8);
  }
  if ((DAT_004c42e4 != 0) && (DAT_004c42ec == 0)) {
    local_14 = 10000;
    local_10 = 10000;
    local_c = 0x27d8;
    local_8 = 0x27d8;
    FUN_0049eb44(DAT_004c42e0,0xd,1,0xd,0,&local_14);
  }
  cVar1 = FUN_00431f58();
  if (cVar1 == '\0') {
    FUN_0049eb44(DAT_004c42e0,0xb,1,10,1,0);
  }
  else {
    FUN_0049eb44(DAT_004c42e0,0xb,1,10,0,0);
  }
  FUN_0043239c();
  sprintf(local_64,s__d_Cr__004c4599,(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6]);
  FUN_0049eb44(DAT_004c42e0,3,1,0xf,0,local_64);
  if (DAT_00558e64 < 1) {
    FUN_0042836c(PTR_s_No_Units_Are_Available_00509430,
                 PTR_s_Please_accept_our_many_regrets__b_00509434,4,0,0x15);
  }
  else {
    FUN_00432014();
    FUN_00431734(0);
  }
  FUN_0049eb44(DAT_004c42e0,0xe,1,7,0,FUN_00431dfc);
  return;
}

