// FUN_004111ec @ 004111ec size=212 sig=undefined FUN_004111ec() cc=unknown
// callers: FUN_00411534
// callees: FUN_00411044,FUN_00410ed8,FUN_00411148,FUN_00411124,FUN_00410cbc,FUN_00410e38,FUN_00410e14

void FUN_004111ec(void)

{
  int iVar1;
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_00410ed8();
  FUN_00411124(*DAT_0053319e);
  FUN_00411124(DAT_0053319e[1]);
  FUN_00411124(DAT_0053319e[2]);
  while (DAT_005331a2 < DAT_005331aa) {
    if (DAT_005331e0 < 0x4000) {
      for (; DAT_005331d8 <= DAT_005331e0; DAT_005331d8 = DAT_005331d8 << 1) {
        DAT_005331d4 = DAT_005331d4 + 1;
      }
    }
    iVar1 = FUN_00411044(&local_8,&local_4);
    if (iVar1 == 0) {
      FUN_00410e14(DAT_0053319e[DAT_005331a2]);
      FUN_00411148(1);
    }
    else {
      FUN_00410e38(local_8,local_4);
      FUN_00411148(local_8);
    }
  }
  FUN_00410e38(3,0);
  FUN_00410cbc(DAT_005331c0);
  return;
}

