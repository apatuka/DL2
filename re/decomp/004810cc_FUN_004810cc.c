// FUN_004810cc @ 004810cc size=201 sig=undefined FUN_004810cc() cc=unknown
// callers: FUN_004812f4,FUN_0048149c
// callees: FUN_0047f23c,FUN_0047edbc,FUN_0047ed54,FUN_0047eed8,FUN_0047f1d8

void FUN_004810cc(int param_1)

{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  if ((param_1 != 0) && (DAT_004dcc1c != 0)) {
    FUN_0047ed54();
    FUN_0047eed8();
    if (*(char *)(param_1 + 0x21) == '\x05') {
      FUN_0047f23c(param_1,0xb);
    }
    else {
      iVar4 = 0;
      piVar3 = &DAT_004dcd00;
      do {
        iVar2 = *piVar3;
        local_8 = iVar2 % 6;
        FUN_0047edbc(local_8,iVar2 / 6,&local_c,&local_10);
        uVar1 = *(ushort *)(iVar2 * 0x34 + param_1 + 0x142);
        if (((uVar1 & 0xff) != 0xff) && (uVar1 != 5)) {
          FUN_0047f1d8(local_c,local_10,0xb);
        }
        iVar4 = iVar4 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar4 < 0x24);
    }
  }
  return;
}

