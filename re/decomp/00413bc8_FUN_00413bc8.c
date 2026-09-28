// FUN_00413bc8 @ 00413bc8 size=116 sig=undefined FUN_00413bc8() cc=unknown
// callers: FUN_00413eb4
// callees: FUN_004669d8,FUN_00413980,FUN_00413b3c

void FUN_00413bc8(undefined4 param_1)

{
  ushort uVar1;
  int iVar2;
  
  uVar1 = 0;
  switch(param_1) {
  case 0x16:
    uVar1 = 0;
    break;
  case 0x18:
    uVar1 = 2;
    break;
  case 0x1a:
    uVar1 = 3;
    break;
  case 0x1c:
    uVar1 = 4;
    break;
  case 0x1e:
    uVar1 = 1;
    break;
  case 0x20:
    uVar1 = 0xff;
    break;
  case 0x22:
    uVar1 = 5;
  }
  *(ushort *)(DAT_006534c0 + 2) = uVar1 | *(ushort *)(DAT_006534c0 + 2) & 0xff00;
  FUN_00413b3c();
  FUN_004669d8(0);
  iVar2 = 0;
  do {
    FUN_00413980(iVar2);
    iVar2 = iVar2 + 1;
  } while ((short)iVar2 < 5);
  return;
}

