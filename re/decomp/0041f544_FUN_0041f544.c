// FUN_0041f544 @ 0041f544 size=442 sig=undefined FUN_0041f544() cc=unknown
// callers: FUN_0041f740
// callees: FUN_0041ed78,FUN_0048db5d,FUN_0041f354,FUN_0041ed44,FUN_004a2cb5,FUN_0041edd8,FUN_0041f198

longlong FUN_0041f544(void)

{
  int iVar1;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_0041f354();
  iVar1 = FUN_004a2cb5(DAT_004b7974,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b7974 + 100) == 0)) {
    switch(local_4) {
    case 0xc:
      FUN_0041f198(0x1f);
      DAT_0053b8a8 = 0x1f;
      FUN_0041ed78();
      break;
    case 0xd:
      FUN_0041f198(0x20);
      DAT_0053b8a8 = 0x20;
      FUN_0041ed78();
      break;
    case 0xe:
      FUN_0041f198(0x21);
      DAT_0053b8a8 = 0x21;
      FUN_0041ed78();
      break;
    case 0xf:
      FUN_0041f198(0x22);
      DAT_0053b8a8 = 0x22;
      FUN_0041ed78();
      break;
    case 0x10:
      FUN_0041f198(0x23);
      DAT_0053b8a8 = 0x23;
      FUN_0041ed78();
      break;
    case 0x11:
      FUN_0041f198(0x24);
      DAT_0053b8a8 = 0x24;
      FUN_0041ed44();
      break;
    case 0x13:
      DAT_0053b88c = (uint)(DAT_0053b88c == 0);
      break;
    case 0x14:
      DAT_0053b890 = (uint)(DAT_0053b890 == 0);
      break;
    case 0x15:
      DAT_0053b894 = (uint)(DAT_0053b894 == 0);
      break;
    case 0x16:
      DAT_0053b898 = (uint)(DAT_0053b898 == 0);
      break;
    case 0x17:
      DAT_0053b89c = (uint)(DAT_0053b89c == 0);
      break;
    case 0x18:
      DAT_0053b8a0 = (uint)(DAT_0053b8a0 == 0);
      break;
    case 0x19:
      DAT_0053b8a4 = (uint)(DAT_0053b8a4 == 0);
      break;
    case 0x1a:
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    case 0x1b:
      FUN_0041edd8();
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

