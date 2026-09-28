// FUN_0049497a @ 0049497a size=301 sig=undefined FUN_0049497a() cc=unknown
// callers: FUN_00494def,FUN_004941f5
// callees: FUN_0049a93f,FUN_00494449,FUN_0048c434,FUN_004943ab,FUN_0049a9e7,FUN_00496cc3,FUN_00496e80,FUN_0049a8ed

void FUN_0049497a(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  uVar1 = DAT_0051bddc;
  if (DAT_0065ecac == &DAT_0065e644) {
    FUN_00494449();
  }
  else if ((((DAT_0065ec80 != 0) && (DAT_0065ec7c != 0)) && (DAT_0051dc9c != 0)) &&
          (DAT_0065ecac != (undefined *)0x0)) {
    iVar2 = FUN_0048c434(DAT_0065ecac);
    if (iVar2 != 0) {
      if (param_1 == 0) {
        FUN_0049a8ed();
        FUN_0049a9e7(DAT_0065ecac + 0x2c);
      }
      FUN_00496cc3(DAT_0065ecb0,DAT_0051dc78,0,DAT_0051dc70,&local_14);
      DAT_0065ec90 = local_10 + DAT_0065ec88;
      DAT_0065ec98 = local_8 + DAT_0065ec88;
      DAT_0065ec8c = local_14 + DAT_0065ec84;
      DAT_0065ec94 = local_c + DAT_0065ec84;
      if (param_2 != 0) {
        FUN_004943ab(0,&DAT_0065ec8c);
      }
      FUN_00496e80(DAT_0065ecb0,DAT_0051dc78,0,DAT_0051dc70,DAT_0065ec84,DAT_0065ec88,0xffffffff);
      if (param_1 == 0) {
        FUN_0049a93f();
      }
      FUN_0048c434(uVar1);
    }
  }
  return;
}

