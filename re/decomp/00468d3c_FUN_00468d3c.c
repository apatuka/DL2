// FUN_00468d3c @ 00468d3c size=100 sig=undefined FUN_00468d3c() cc=unknown
// callers: 
// callees: FUN_00468da0,FUN_0043a1f8,FUN_004719a0
// strings: \".\\\\deadlock.ini\"

void FUN_00468d3c(void)

{
  undefined1 local_e4 [4];
  undefined1 local_e0 [128];
  undefined1 local_60 [64];
  undefined1 local_20 [32];
  
  if (DAT_004d59a8 == '\0') {
    FUN_0043a1f8(0);
    DAT_004d59a8 = '\0';
  }
  else {
    FUN_004719a0(s___deadlock_ini_004d5277,1,local_e4,&DAT_004d5140,local_e0,0x80,local_20,0x20,
                 local_60,0x40);
    FUN_00468da0(local_e0);
  }
  return;
}

