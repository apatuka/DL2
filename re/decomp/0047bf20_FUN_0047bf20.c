// FUN_0047bf20 @ 0047bf20 size=86 sig=undefined FUN_0047bf20() cc=unknown
// callers: FUN_0047c53c
// callees: memcpy

void FUN_0047bf20(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = (&DAT_0059f19a)[DAT_0058f1f4 * 0xb6];
  memcpy(&DAT_0059f160,param_1,0x13e8);
  (&DAT_0059f19a)[DAT_0058f1f4 * 0xb6] = uVar1;
  return;
}

