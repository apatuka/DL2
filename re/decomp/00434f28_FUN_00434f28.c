// FUN_00434f28 @ 00434f28 size=1684 sig=undefined FUN_00434f28() cc=unknown
// callers: CheckSubUnit,CheckSubTech,CheckSubInfo,FUN_00435e64
// callees: FUN_00430b94,FUN_00432cf4,FUN_0049eb44,FUN_0043239c,FUN_004a3de6,FUN_00432d30,FUN_004a2004,FUN_00414f04,sprintf,FUN_00431f58,FUN_00430b1c,FUN_00432fc0
// strings: \"%d Cr.\"

void FUN_00434f28(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_3c [40];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_00558d58 = 0;
  DAT_004c42d4 = FUN_004a3de6(0,0x39303944);
  FUN_00414f04(DAT_004c42d4);
  FUN_004a2004(DAT_004c42d4);
  FUN_00432d30();
  FUN_0049eb44(DAT_004c42d4,0x73,1,7,0,&LAB_00414a6c);
  FUN_0049eb44(DAT_004c42d4,9,1,0xb,1,0);
  FUN_0049eb44(DAT_004c42d4,1,1,7,0,FUN_00431258);
  if ((DAT_004c42e4 != 0) && (*(char *)(DAT_004c42e4 + 0x3c) == '\0')) {
    FUN_0049eb44(DAT_004c42d4,0x73,1,10,0,0);
  }
  if (DAT_004c42ec != 0) {
    local_10 = 7;
    local_14 = 10;
    local_8 = 0xcf;
    local_c = 0xd2;
    FUN_0049eb44(DAT_004c42d4,0xd,1,0xd,0,&local_14);
  }
  if ((DAT_004c42e8 == 0) ||
     ((((DAT_004d5ac4 == 0 && (DAT_004d5ab0 != 0)) && (DAT_004d5aa8 != 0)) && (DAT_004d59ac != 0))))
  {
    FUN_0049eb44(DAT_004c42d4,3,1,0xf,0,&DAT_004c4588);
  }
  else {
    FUN_0049eb44(DAT_004c42d4,3,1,0xf,0,DAT_004c42e8);
  }
  cVar1 = FUN_00431f58();
  if (cVar1 == '\0') {
    FUN_0049eb44(DAT_004c42d4,0xb,1,10,1,0);
  }
  else {
    FUN_0049eb44(DAT_004c42d4,0xb,1,10,0,0);
  }
  cVar1 = FUN_0043239c();
  if (cVar1 == '\0') {
    FUN_0049eb44(DAT_004c42d4,0xc,1,10,1,0);
  }
  else {
    FUN_0049eb44(DAT_004c42d4,0xc,1,10,0,0);
  }
  uVar2 = FUN_00430b1c(1);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x14,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(1);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x13,1,0xf,0,local_3c);
  uVar2 = FUN_00430b1c(2);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x1e,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(2);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x1d,1,0xf,0,local_3c);
  uVar2 = FUN_00430b1c(3);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x28,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(3);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x27,1,0xf,0,local_3c);
  uVar2 = FUN_00430b1c(4);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x32,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(4);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x31,1,0xf,0,local_3c);
  uVar2 = FUN_00430b1c(5);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x3c,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(5);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x3b,1,0xf,0,local_3c);
  uVar2 = FUN_00430b1c(6);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x46,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(6);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x45,1,0xf,0,local_3c);
  uVar2 = FUN_00430b1c(7);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x50,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(7);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x4f,1,0xf,0,local_3c);
  uVar2 = FUN_00430b1c(8);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x5a,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(8);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x59,1,0xf,0,local_3c);
  uVar2 = FUN_00430b1c(9);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,100,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(9);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,99,1,0xf,0,local_3c);
  uVar2 = FUN_00430b1c(10);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x6e,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(10);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x6d,1,0xf,0,local_3c);
  DAT_00558d54 = 0;
  iVar3 = FUN_00430b94(1);
  if ((int)(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6] / iVar3 < 100) {
    sprintf(local_3c,&DAT_004c458d,(int)(&DAT_0059f16c)[DAT_0058f1f4 * 0xb6] / iVar3);
  }
  else {
    sprintf(local_3c,&DAT_004c458d,100);
  }
  FUN_0049eb44(DAT_004c42d4,0x73,1,0xf,0,local_3c);
  uVar2 = FUN_00430b94(1);
  sprintf(local_3c,s__d_Cr__004c4599,uVar2);
  FUN_0049eb44(DAT_004c42d4,0x77,1,0xf,0,local_3c);
  iVar3 = FUN_00430b94(1);
  sprintf(local_3c,s__d_Cr__004c4599,iVar3 * 100);
  FUN_0049eb44(DAT_004c42d4,0x7b,1,0xf,0,local_3c);
  FUN_0049eb44(DAT_004c42d4,0x16,1,0xb,1,0);
  FUN_00432fc0();
  FUN_00432d30();
  FUN_00432cf4();
  return;
}

