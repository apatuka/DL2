// FUN_004326b0 @ 004326b0 size=371 sig=undefined FUN_004326b0() cc=unknown
// callers: FUN_00432824,FUN_00432ad0,CheckSubInfo
// callees: FUN_0049eb44,sprintf
// strings: \"%d Cr.\"

void FUN_004326b0(void)

{
  undefined4 local_108 [64];
  
  if (DAT_00558cc0 == -1) {
    local_108[0] = DAT_004c45b1;
  }
  else {
    sprintf(local_108,&DAT_004c458a,&DAT_005a43d0 + DAT_00558cc0 * 0xadc);
  }
  FUN_0049eb44(DAT_004c42d8,0x10,1,0xf,0,local_108);
  if (((char)(&DAT_005a4436)[DAT_0058f1f4 + DAT_00558cc0 * 0xadc] < '\x01') ||
     ((&DAT_005a43f0)[DAT_00558cc0 * 0xadc] == -1)) {
    local_108[0] = DAT_004c45b1;
  }
  else {
    sprintf(local_108,&DAT_004c458a,
            (&PTR_s_ChCh_t_00509038)
            [(char)(&DAT_0059f162)[(char)(&DAT_005a43f0)[DAT_00558cc0 * 0xadc] * 0x2d8]]);
  }
  FUN_0049eb44(DAT_004c42d8,0x12,1,0xf,0,local_108);
  sprintf(local_108,s__d_Cr__004c4599,100);
  FUN_0049eb44(DAT_004c42d8,0x14,1,0xf,0,local_108);
  sprintf(local_108,s__d_Cr__004c4599,(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6]);
  FUN_0049eb44(DAT_004c42d8,2,1,0xf,0,local_108);
  return;
}

