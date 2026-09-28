// CheckColonyAssistant @ 00420fa0 size=278 sig=undefined CheckColonyAssistant() cc=unknown
// callers: FUN_0044930c
// callees: FUN_0041ff24,FUN_00448d94,FUN_0041ff18,FUN_00420e34,FUN_00420734,FUN_0041f7c8,DebugMessage,FUN_00420d34,FUN_00426594,FUN_004a2cb5,FUN_00420d2c,FUN_0041b908,FUN_0041ff98,FUN_0041fd38,FUN_00420cb8,FUN_0041ffd4
// strings: \"gpColonyAssistant NULL in CheckColonyAssistant()\"

/* auto-named from string evidence: CheckColonyAssistant */

longlong CheckColonyAssistant(void)

{
  int iVar1;
  int iVar2;
  uint local_8;
  
  if (DAT_004b7a14 == 0) {
    DebugMessage(s_gpColonyAssistant_NULL_in_CheckC_004b7ad0);
    return (ulonglong)local_8 << 0x20;
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  iVar1 = FUN_004a2cb5(DAT_004b7a14,&local_8);
  if (((iVar1 == 0) && (local_8 != 0)) && (*(int *)(DAT_004b7a14 + 100) == 0)) {
    switch(local_8) {
    case 3:
      FUN_00426594(&DAT_004d4b48);
      break;
    case 4:
      FUN_00420d2c();
      DAT_004d59a4 = 0;
      return (ulonglong)local_8 << 0x20;
    case 5:
      FUN_00448d94(DAT_0053b8b8);
      FUN_00420734();
      FUN_0041ff24();
      FUN_0041ff18();
      break;
    case 7:
      FUN_00420cb8();
      FUN_0041ff98();
      FUN_0041ffd4();
      break;
    case 8:
      FUN_00420e34();
      break;
    case 9:
      FUN_00420d34();
      break;
    case 0xd:
    case 0xf:
    case 0x11:
    case 0x13:
    case 0x15:
    case 0x17:
    case 0x19:
    case 0x1b:
    case 0x1d:
    case 0x1f:
    case 0x21:
    case 0x23:
    case 0x25:
    case 0x27:
    case 0x29:
    case 0x2b:
    case 0x2d:
    case 0x2f:
    case 0x31:
    case 0x33:
    case 0x35:
    case 0x37:
    case 0x39:
    case 0x3b:
      FUN_0041b908();
      iVar2 = (int)(local_8 - 0xd) >> 1;
      if (iVar2 < 0) {
        iVar2 = iVar2 + (uint)((local_8 - 0xd & 1) != 0);
      }
      FUN_0041fd38((&DAT_004b7a20)[iVar2],1);
      FUN_0041ff24();
      FUN_0041ff18();
      break;
    case 0x3e:
      FUN_0041f7c8();
    }
  }
  DAT_004d59a4 = 0;
  return CONCAT44(local_8,iVar1);
}

