// FUN_00424590 @ 00424590 size=924 sig=undefined FUN_00424590() cc=unknown
// callers: FUN_00424994
// callees: FUN_00482f6c,FUN_004243dc,FUN_00424360,FUN_004a2cb5,FUN_00424474,FUN_004a5e12,FUN_0048db5d,FUN_00482f3c,FUN_0049eb44,FUN_00482940

int FUN_00424590(void)

{
  int iVar1;
  int local_18;
  undefined1 local_14 [4];
  int local_10;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00424474();
  iVar1 = FUN_004a2cb5(DAT_004b7c3c,&local_18);
  if (((iVar1 == 0) && (local_18 != 0)) && (*(int *)(DAT_004b7c3c + 100) == 0)) {
    switch(local_18) {
    case 4:
      DAT_00557500 = 1;
      break;
    case 5:
      DAT_00557500 = 2;
      break;
    case 6:
      DAT_00557500 = 4;
      break;
    case 7:
      DAT_00557504 = 0;
      break;
    case 8:
      DAT_00557504 = 1;
      break;
    case 9:
      DAT_00557504 = 2;
      break;
    case 0xb:
      DAT_00557508 = 0;
      break;
    case 0xc:
      DAT_00557508 = 1;
      break;
    case 0xe:
      DAT_0055751c = FUN_0049eb44(DAT_004b7c3c,0xe,1,0xc,0,0);
      if (DAT_0055751c == 0) {
        FUN_0049eb44(DAT_004b7c3c,0x13,1,0x28,0,local_14);
        DAT_004b7c50 = local_10;
        FUN_00482f6c(0xffffd8f0);
        FUN_0049eb44(DAT_004b7c3c,0x13,1,10,1,0);
      }
      else {
        FUN_0049eb44(DAT_004b7c3c,0x13,1,0x28,0,local_14);
        FUN_00482f6c((local_10 * 3000) / 100 + -3000);
        FUN_0049eb44(DAT_004b7c3c,0x13,1,10,0,0);
      }
      FUN_00482940(DAT_0055751c);
      break;
    case 0xf:
      DAT_00557520 = FUN_0049eb44(DAT_004b7c3c,0xf,1,0xc,0,0);
      if (DAT_00557520 == 0) {
        FUN_0049eb44(DAT_004b7c3c,0x14,1,0x28,0,local_14);
        DAT_004b7c54 = local_10;
        FUN_00482f3c(0xffffd8f0);
        FUN_0049eb44(DAT_004b7c3c,0x14,1,10,1,0);
      }
      else {
        FUN_0049eb44(DAT_004b7c3c,0x14,1,0x28,0,local_14);
        FUN_00482f3c((local_10 * 3000) / 100 + -3000);
        FUN_0049eb44(DAT_004b7c3c,0x14,1,10,0,0);
      }
      break;
    case 0x10:
      DAT_00557524 = FUN_0049eb44(DAT_004b7c3c,0x10,1,0xc,0,0);
      break;
    case 0x11:
      DAT_00557528 = FUN_0049eb44(DAT_004b7c3c,0x11,1,0xc,0,0);
      break;
    case 0x13:
      FUN_0049eb44(DAT_004b7c3c,0x13,1,0x28,0,local_14);
      FUN_00482f6c((local_10 * 3000) / 100 + -3000);
      break;
    case 0x14:
      FUN_0049eb44(DAT_004b7c3c,0x14,1,0x28,0,local_14);
      FUN_00482f3c((local_10 * 3000) / 100 + -3000);
      break;
    case 0x16:
      DAT_004d5ac8 = 1;
      FUN_004a5e12(1);
      break;
    case 0x17:
      DAT_004d5ac8 = 0;
      FUN_004a5e12(0);
      break;
    case 0x18:
      FUN_00424360();
      DAT_004d59a4 = 0;
      return local_18;
    case 0x19:
      FUN_004243dc();
      DAT_004d59a4 = 0;
      return local_18;
    case 0x1b:
      DAT_0055750c = 2;
      break;
    case 0x1c:
      DAT_0055750c = 1;
      break;
    case 0x1d:
      DAT_0055750c = 0;
    }
  }
  DAT_004d59a4 = 0;
  return 0;
}

