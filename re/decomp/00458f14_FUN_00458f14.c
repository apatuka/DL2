// FUN_00458f14 @ 00458f14 size=340 sig=undefined FUN_00458f14() cc=unknown
// callers: FUN_0044ae10
// callees: FUN_00458d28,FUN_00459ea8,FUN_00449cc4,FUN_0043edd8,FUN_00458d80,FUN_00458c6c

undefined4 FUN_00458f14(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((DAT_00583d38 == 0) && (DAT_00583d58 == 0)) {
    uVar1 = 0;
  }
  else {
    FUN_00458c6c();
    iVar2 = (int)DAT_00583d44 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((DAT_00583d44 & 1) != 0);
    }
    DAT_00583d3c = param_1 - iVar2;
    if (DAT_00583d4c == 0) {
      iVar2 = (int)DAT_00583d48 >> 1;
      if (iVar2 < 0) {
        iVar2 = iVar2 + (uint)((DAT_00583d48 & 1) != 0);
      }
      DAT_00583d40 = param_2 - iVar2;
    }
    else if (DAT_00583d4c == 1) {
      DAT_00583d40 = param_2 - (DAT_00583d48 - 0x19);
    }
    else if (DAT_00583d4c == 2) {
      DAT_00583d40 = param_2 - (DAT_00583d48 - 0x32);
    }
    FUN_00458d28(DAT_00583d3c,DAT_00583d40);
    FUN_00458d80(DAT_00583d3c,DAT_00583d40);
    if (((DAT_004d59b4 == 0) || (DAT_004d59b4 == 0x22)) && (DAT_00583d2c == 0)) {
      FUN_00449cc4(param_1,param_2,&local_8,&local_c);
      if (DAT_004d5ad0 == 0) {
        FUN_00459ea8(local_8,local_c,&local_10,&local_14);
      }
      else {
        FUN_0043edd8(local_8,local_c,&local_10,&local_14);
      }
      if ((short)(&DAT_005a0552)[local_14 * 200 + local_10 * 5] != DAT_00583d80) {
        DAT_00583d2c = 1;
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

