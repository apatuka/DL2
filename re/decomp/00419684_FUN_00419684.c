// FUN_00419684 @ 00419684 size=96 sig=undefined FUN_00419684() cc=unknown
// callers: FUN_0045bde4,FUN_0045c560,FUN_00419eac,FUN_00419924,FUN_00419f50,FUN_00419c08
// callees: FUN_0049eb44,FUN_00417404,FUN_00417dc8,FUN_00418524,sprintf

void FUN_00419684(void)

{
  undefined1 local_cc [200];
  
  DAT_005332bc = FUN_00417404();
  FUN_00418524(DAT_005332bc);
  FUN_00417dc8();
  sprintf(local_cc,&DAT_004b76c8,&DAT_005a43d0 + DAT_004c5b50 * 0xadc);
  FUN_0049eb44(DAT_004b76b0,6,1,0xf,0,local_cc);
  return;
}

