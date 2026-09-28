// FUN_00432fc0 @ 00432fc0 size=1054 sig=undefined FUN_00432fc0() cc=unknown
// callers: FUN_00434f28
// callees: FUN_0049eb44,FUN_00432ec8,sprintf,FUN_00432f0c
// strings: \"%d Cr.\"

void FUN_00432fc0(void)

{
  char cVar1;
  int iVar2;
  undefined1 local_46c [80];
  undefined1 local_41c [1048];
  
  sprintf(local_46c,&DAT_004c458d,(&DAT_005a440e)[DAT_004c5b50 * 0x2b7]);
  FUN_0049eb44(DAT_004c42d4,0x15,1,0xf,0,local_46c);
  sprintf(local_46c,&DAT_004c458d,(&DAT_005a4412)[DAT_004c5b50 * 0x2b7]);
  FUN_0049eb44(DAT_004c42d4,0x1f,1,0xf,0,local_46c);
  sprintf(local_46c,&DAT_004c458d,*(undefined4 *)(&DAT_005a4416 + DAT_004c5b50 * 0xadc));
  FUN_0049eb44(DAT_004c42d4,0x29,1,0xf,0,local_46c);
  sprintf(local_46c,&DAT_004c458d,*(undefined4 *)(&DAT_005a441a + DAT_004c5b50 * 0xadc));
  FUN_0049eb44(DAT_004c42d4,0x33,1,0xf,0,local_46c);
  sprintf(local_46c,&DAT_004c458d,*(undefined4 *)(&DAT_005a441e + DAT_004c5b50 * 0xadc));
  FUN_0049eb44(DAT_004c42d4,0x3d,1,0xf,0,local_46c);
  sprintf(local_46c,&DAT_004c458d,*(undefined4 *)(&DAT_005a4426 + DAT_004c5b50 * 0xadc));
  FUN_0049eb44(DAT_004c42d4,0x51,1,0xf,0,local_46c);
  sprintf(local_46c,&DAT_004c458d,*(undefined4 *)(&DAT_005a4422 + DAT_004c5b50 * 0xadc));
  FUN_0049eb44(DAT_004c42d4,0x47,1,0xf,0,local_46c);
  sprintf(local_46c,&DAT_004c458d,*(undefined4 *)(&DAT_005a442a + DAT_004c5b50 * 0xadc));
  FUN_0049eb44(DAT_004c42d4,0x5b,1,0xf,0,local_46c);
  sprintf(local_46c,&DAT_004c458d,*(undefined4 *)(&DAT_005a442e + DAT_004c5b50 * 0xadc));
  FUN_0049eb44(DAT_004c42d4,0x65,1,0xf,0,local_46c);
  sprintf(local_46c,&DAT_004c458d,*(undefined4 *)(&DAT_005a4432 + DAT_004c5b50 * 0xadc));
  FUN_0049eb44(DAT_004c42d4,0x6f,1,0xf,0,local_46c);
  sprintf(local_46c,s__d_Cr__004c4599,(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6]);
  FUN_0049eb44(DAT_004c42d4,2,1,0xf,0,local_46c);
  FUN_0049eb44(DAT_004c42d4,0x72,1,0xe,0,local_46c);
  cVar1 = FUN_00432ec8(DAT_00558d54);
  if (cVar1 == '\0') {
    sprintf(local_41c,local_46c,&DAT_004c45cc);
  }
  else {
    sprintf(local_41c,local_46c,&DAT_004c45c7);
  }
  FUN_0049eb44(DAT_004c42d4,0x72,1,0xf,0,local_41c);
  if (DAT_00558d54 == -1) {
    sprintf(local_46c,&DAT_004c458d,0);
    FUN_0049eb44(DAT_004c42d4,0x79,1,0xf,0,local_46c);
  }
  else {
    iVar2 = FUN_00432f0c(DAT_00558d54);
    sprintf(local_46c,&DAT_004c458d,
            *(undefined4 *)(&DAT_005a440a + iVar2 * 4 + DAT_004c5b50 * 0xadc));
    FUN_0049eb44(DAT_004c42d4,0x79,1,0xf,0,local_46c);
  }
  return;
}

