// FUN_00413eb4 @ 00413eb4 size=248 sig=undefined FUN_00413eb4() cc=unknown
// callers: FUN_0044930c,FUN_00413fe4
// callees: FUN_004669d8,FUN_00413bc8,FUN_004a2cb5,FUN_00413b3c,FUN_00413c70,FUN_0048db5d

longlong FUN_00413eb4(void)

{
  int iVar1;
  int iVar2;
  uint local_4;
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_00413c70();
  iVar2 = FUN_004a2cb5(DAT_004b7028,&local_4);
  iVar1 = DAT_006534c0;
  if (((iVar2 == 0) && (local_4 != 0)) && (*(int *)(DAT_004b7028 + 100) == 0)) {
    switch(local_4) {
    case 3:
      DAT_004d59a4 = 0;
      return CONCAT44(local_4,local_4);
    case 4:
      DAT_004d59a4 = 0;
      *(undefined2 *)(DAT_006534c0 + 8) = DAT_005331fc;
      *(undefined2 *)(iVar1 + 10) = DAT_005331fe;
      *(undefined2 *)(iVar1 + 6) = DAT_00533200;
      *(undefined2 *)(iVar1 + 0xc) = DAT_00533202;
      *(undefined2 *)(iVar1 + 0xe) = DAT_00533204;
      *(undefined1 *)(iVar1 + 4) = DAT_00533206;
      *(undefined2 *)(iVar1 + 2) = DAT_00533208;
      FUN_004669d8(0);
      return CONCAT44(local_4,local_4);
    case 0x11:
    case 0x13:
      FUN_00413b3c();
      break;
    case 0x16:
    case 0x18:
    case 0x1a:
    case 0x1c:
    case 0x1e:
    case 0x20:
    case 0x22:
      FUN_00413bc8(local_4);
    }
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

