// FUN_00420cb8 @ 00420cb8 size=113 sig=undefined FUN_00420cb8() cc=unknown
// callers: CheckColonyAssistant,FUN_00420e34
// callees: FUN_00476238,FUN_0049eb44

void FUN_00420cb8(void)

{
  *(byte *)(DAT_0053b8b8 + 0x9ae) =
       *(byte *)(DAT_0053b8b8 + 0x9ae) ^ '\x01' << ((char)DAT_0053b8ac - 0x16U & 0x1f);
  FUN_00476238(DAT_0053b8b8);
  if ((1 << ((char)DAT_0053b8ac - 0x16U & 0x1f) & (int)*(char *)(DAT_0053b8b8 + 0x9ae)) != 0) {
    FUN_0049eb44(DAT_004b7a14,7,1,0xb,1,0);
    return;
  }
  FUN_0049eb44(DAT_004b7a14,7,1,0xb,0,0);
  return;
}

