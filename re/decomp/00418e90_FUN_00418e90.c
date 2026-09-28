// FUN_00418e90 @ 00418e90 size=105 sig=undefined FUN_00418e90() cc=unknown
// callers: FUN_00418f3c
// callees: FUN_0049eb44,FUN_00418d18,sprintf

void FUN_00418e90(void)

{
  undefined1 local_c8 [200];
  
  DAT_0053b254 = FUN_0049eb44(DAT_004b76b4,0x28,1,0x22,0,0);
  sprintf(local_c8,&DAT_004b76c8,
          (&PTR_s_Attack_Units_Only_00509e38)[(char)(&DAT_0053b233)[DAT_0053b254]]);
  FUN_0049eb44(DAT_004b76b4,0x27,1,0xf,0,local_c8);
  FUN_00418d18();
  return;
}

