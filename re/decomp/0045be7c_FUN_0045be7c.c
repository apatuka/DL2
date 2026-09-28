// FUN_0045be7c @ 0045be7c size=212 sig=undefined FUN_0045be7c() cc=unknown
// callers: FUN_0044a7c8
// callees: FUN_00459068,FUN_0045bde4,FUN_0045b970,FUN_0047ee9c,GetKeyState,FUN_0045b8a8

void FUN_0045be7c(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  int local_c;
  int local_8;
  
  FUN_00459068();
  if ('\x02' < *(char *)(DAT_00657de0 + 0x66 + DAT_0058f1f4)) {
    uVar1 = GetKeyState(0x10);
    FUN_0047ee9c(param_1,param_2,&local_8,&local_c);
    if ((((local_8 < 0) || (5 < local_8)) || (local_c < 0)) || (5 < local_c)) {
      iVar2 = FUN_0045b970(param_1,param_2,0);
      if ((iVar2 != -1) && (iVar2 == DAT_00583d90)) {
        FUN_0045bde4(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,iVar2);
      }
    }
    else {
      local_8 = local_c * 6 + local_8;
      if (((local_8 == DAT_00583d98) && ((uVar1 & 0x8000) != 0)) &&
         (*(char *)(DAT_00657de0 + 0x21) != '\0')) {
        FUN_0045b8a8(local_8);
      }
    }
  }
  return;
}

