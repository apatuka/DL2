// FUN_0045ccf8 @ 0045ccf8 size=142 sig=undefined FUN_0045ccf8() cc=unknown
// callers: 
// callees: FUN_0045c27c,FUN_00418d18,FUN_00418cf4,FUN_00419e0c,FUN_00419678,FUN_00418e00,FUN_0045c560,GetKeyState,FUN_004197dc

undefined4 FUN_0045ccf8(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  
  uVar2 = GetKeyState(0x12);
  iVar3 = FUN_0045c27c(param_1,param_2);
  if (iVar3 != 0) {
    if (((DAT_00583d2c == 0) && (DAT_004d59b4 != 1)) &&
       ((DAT_004d59b4 != 0x22 || (cVar1 = FUN_00418e00(), cVar1 != '\0')))) {
      if (DAT_004d59b4 != 0x22) {
        FUN_00419678();
        FUN_004197dc(iVar3,0);
      }
      FUN_00419e0c(DAT_00583d7c);
      FUN_00418d18();
      FUN_00418cf4();
    }
    else {
      FUN_0045c560(iVar3,(uVar2 & 0x8000) != 0);
    }
  }
  return 1;
}

