// FUN_00440b34 @ 00440b34 size=52 sig=undefined FUN_00440b34() cc=unknown
// callers: FUN_00440b68,FUN_0045a91c
// callees: 

undefined1 FUN_00440b34(void)

{
  uint uVar1;
  undefined1 uVar2;
  
  uVar1 = 1 << ((byte)DAT_0058f1f4 & 0x1f);
  uVar2 = (uVar1 & (int)DAT_004fbe36) != 0;
  if ((uVar1 & (int)DAT_004fc4a8) != 0) {
    uVar2 = 2;
  }
  return uVar2;
}

