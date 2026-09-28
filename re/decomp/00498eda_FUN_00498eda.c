// FUN_00498eda @ 00498eda size=178 sig=undefined FUN_00498eda() cc=unknown
// callers: FUN_00498f8c
// callees: FUN_0048fbf8,FUN_0048fd38

short FUN_00498eda(int param_1,ushort param_2,undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  ushort uVar3;
  short sVar4;
  
  uVar3 = 0;
  sVar4 = 0;
  do {
    sVar4 = sVar4 + (ushort)DAT_0051e20c;
    for (; (DAT_0051e20c != 0 && (uVar3 < param_2)); uVar3 = uVar3 + 1) {
      *(byte *)(param_1 + (uint)uVar3) = DAT_0051e20d;
      DAT_0051e20c = DAT_0051e20c - 1;
    }
    if (DAT_0051e20c != 0) {
      return sVar4 - (ushort)DAT_0051e20c;
    }
    bVar1 = FUN_0048fd38(param_3);
    if ((bVar1 & 0xc0) == 0xc0) {
      DAT_0051e20c = bVar1 & 0x3f;
      DAT_0051e20d = FUN_0048fd38(param_3);
    }
    else {
      DAT_0051e20c = 1;
      DAT_0051e20d = bVar1;
    }
  } while (uVar3 < param_2);
  iVar2 = FUN_0048fbf8(param_3);
  if (iVar2 != 0) {
    sVar4 = 0;
  }
  return sVar4;
}

