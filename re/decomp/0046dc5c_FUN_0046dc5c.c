// FUN_0046dc5c @ 0046dc5c size=76 sig=undefined FUN_0046dc5c() cc=unknown
// callers: FUN_00480d78,DrawSTileBuilding,FUN_0045a3e4
// callees: FUN_0044d1a4

undefined4 FUN_0046dc5c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0044d1a4(param_1,0xb,0);
  if ((iVar1 == -1) ||
     ((((1 << ((byte)DAT_0058f1f4 & 0x1f) & *(uint *)(param_1 + 0x8b0)) == 0 &&
       (DAT_004d5aa0 == '\0')) && (DAT_00583c20 == 0)))) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

