// FUN_00418e24 @ 00418e24 size=105 sig=undefined FUN_00418e24() cc=unknown
// callers: FUN_00418efc
// callees: FUN_0049eb44,FUN_00418d18,sprintf

void FUN_00418e24(void)

{
  undefined1 local_c8 [200];
  
  DAT_0053b250 = FUN_0049eb44(DAT_004b76b4,0x2c,1,0x22,0,0);
  sprintf(local_c8,&DAT_004b76c8,(&PTR_s_No_Mission_00509dcc)[(char)(&DAT_0053b218)[DAT_0053b250]]);
  FUN_0049eb44(DAT_004b76b4,0x2b,1,0xf,0,local_c8);
  FUN_00418d18();
  return;
}

