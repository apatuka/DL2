// FUN_00416af0 @ 00416af0 size=311 sig=undefined FUN_00416af0() cc=unknown
// callers: ChCht,FUN_00467fc0,FUN_0043be24
// callees: FUN_004167b0,FUN_0049eb44,FUN_004169e8,FUN_00416810,FUN_004169b0

int FUN_00416af0(byte param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00416810();
  if (iVar1 == 0) {
    iVar2 = -1;
  }
  else {
    FUN_0049eb44(DAT_004b769c,4,1,10,1,0);
    FUN_0049eb44(DAT_004b769c,5,1,10,1,0);
    FUN_0049eb44(DAT_004b769c,6,1,10,1,0);
    FUN_0049eb44(DAT_004b769c,7,1,10,1,0);
    FUN_0049eb44(DAT_004b769c,8,1,10,1,0);
    FUN_0049eb44(DAT_004b769c,9,1,10,1,0);
    FUN_0049eb44(DAT_004b769c,10,1,10,1,0);
    iVar1 = 0;
    do {
      if (('\x01' << ((byte)iVar1 & 0x1f) & param_1) != 0) {
        FUN_0049eb44(DAT_004b769c,iVar1 + 4,1,10,0,0);
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 7);
    if (DAT_004d5aa0 != '\0') {
      DAT_005332ac = (int)(char)PTR_DAT_004d5988[2];
      FUN_0049eb44(DAT_004b769c,DAT_005332ac + 4,1,0xb,1,0);
    }
    FUN_004167b0();
    do {
      iVar1 = FUN_004169e8();
    } while (iVar1 == 0);
    FUN_004169b0();
    iVar2 = DAT_005332ac;
    if (iVar1 != 0xb) {
      iVar2 = -1;
    }
  }
  return iVar2;
}

