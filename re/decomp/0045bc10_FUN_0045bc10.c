// FUN_0045bc10 @ 0045bc10 size=237 sig=undefined FUN_0045bc10() cc=unknown
// callers: FUN_0044a92c,FUN_0045bd00,FUN_0044a8bc
// callees: FUN_0045ac80,FUN_0045b970,FUN_0045b8e8,FUN_0047ee9c,FUN_0045aed4,FUN_0045bb88,FUN_0045b8a8

void FUN_0045bc10(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  cVar1 = *(char *)(DAT_00657de0 + 0x66 + DAT_0058f1f4);
  FUN_0047ee9c(param_1,param_2,&local_8,&local_c);
  if ((((local_8 < 0) || (5 < local_8)) || (local_c < 0)) || (5 < local_c)) {
    iVar2 = FUN_0045b970(param_1,param_2,0);
    if ((iVar2 == -1) || (iVar2 != DAT_00583d94)) {
      FUN_0045ac80();
    }
    else {
      FUN_0045bb88(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,iVar2);
    }
  }
  else if ((('\x02' < cVar1) && (iVar2 = local_c * 6 + local_8, iVar2 == DAT_00583d9c)) &&
          ('\x01' < cVar1)) {
    iVar3 = FUN_0045aed4(iVar2);
    if ((*(char *)(DAT_00657de0 + 0x21) == '\0') || (iVar3 != 0)) {
      if (((cVar1 == '\x04') || (DAT_004d5aa0 != '\0')) && (iVar3 != 0)) {
        FUN_0045b8e8(iVar3,DAT_0058f1a4);
      }
    }
    else {
      FUN_0045b8a8(iVar2);
    }
  }
  return;
}

