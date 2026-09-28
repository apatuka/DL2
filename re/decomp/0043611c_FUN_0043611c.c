// FUN_0043611c @ 0043611c size=101 sig=undefined FUN_0043611c() cc=unknown
// callers: FUN_0043632c
// callees: FUN_00436070,FUN_00488074,FUN_00494def,FUN_004a5b1c,FUN_004493dc,FUN_0042f0c4

void FUN_0043611c(void)

{
  undefined4 uVar1;
  int iVar2;
  
  FUN_004a5b1c();
  FUN_004493dc(1);
  uVar1 = DAT_004d59b4;
  DAT_004d59b4 = 0x32;
  FUN_00494def(0);
  iVar2 = FUN_00488074(0x54445243,0,0,1);
  if (iVar2 == 0) {
    FUN_00494def(1);
    FUN_0042f0c4(8,1);
  }
  else {
    FUN_00494def(1);
  }
  DAT_004d59b4 = uVar1;
  FUN_004493dc(0);
  FUN_00436070();
  return;
}

