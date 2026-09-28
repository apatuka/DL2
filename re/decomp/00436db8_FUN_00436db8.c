// FUN_00436db8 @ 00436db8 size=248 sig=undefined FUN_00436db8() cc=unknown
// callers: FUN_0045ae78
// callees: FUN_0049eb44,FUN_00436d90,FUN_00449f5c,FUN_004a2004,FUN_004a3de6,FUN_00436978,FUN_00436a44,FUN_00414f04,FUN_004493dc

undefined4 FUN_00436db8(void)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  
  DAT_004c4664 = FUN_004a3de6(0,0x36303044);
  if (DAT_004c4664 == 0) {
    return 0;
  }
  FUN_004493dc(1);
  DAT_00558f28 = DAT_004d59b4;
  DAT_004d59b4 = 0xb;
  FUN_00414f04(DAT_004c4664);
  FUN_004a2004(DAT_004c4664);
  puVar1 = &DAT_005a43f6;
  DAT_00558eb4 = PTR_DAT_004d5988[0xb];
  puVar4 = &DAT_00558eb5;
  iVar3 = 0;
  do {
    *puVar4 = *puVar1;
    iVar3 = iVar3 + 1;
    puVar4 = puVar4 + 1;
    puVar1 = puVar1 + 0xadc;
  } while (iVar3 < 0x70);
  FUN_00436978(DAT_004c5b50);
  switch(PTR_DAT_004d5988[0xb]) {
  case 0:
    uVar2 = 7;
    break;
  case 1:
    uVar2 = 8;
    break;
  case 2:
    uVar2 = 9;
    break;
  case 3:
    uVar2 = 10;
    break;
  case 4:
    uVar2 = 0xb;
    break;
  case 5:
    uVar2 = 0xc;
    break;
  default:
    uVar2 = 10;
  }
  FUN_0049eb44(DAT_004c4664,uVar2,1,0xb,1,0);
  FUN_00436a44();
  FUN_00436d90();
  FUN_00449f5c();
  return 1;
}

