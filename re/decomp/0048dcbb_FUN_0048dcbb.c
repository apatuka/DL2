// FUN_0048dcbb @ 0048dcbb size=218 sig=undefined FUN_0048dcbb() cc=unknown
// callers: FUN_0048e241,FUN_0048e169,FUN_0048e319,FUN_0048e1d5,FUN_0048e2ad,FUN_0048e385
// callees: FUN_0048dc22

undefined4
FUN_0048dcbb(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,int param_5)

{
  undefined2 uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  
  iVar5 = 0;
  iVar4 = DAT_0051c2f4;
  while( true ) {
    if (DAT_0051c2f8 <= iVar5) {
      return 0;
    }
    if (param_1 == (&DAT_0065e804)[iVar4 * 5]) break;
    iVar4 = iVar4 + -1;
    if (iVar4 < 0) {
      iVar4 = 0x13;
    }
    iVar5 = iVar5 + 1;
  }
  *param_3 = (&DAT_0065e814)[iVar4 * 5];
  *param_2 = (&DAT_0065e810)[iVar4 * 5];
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = (&DAT_0065e808)[iVar4 * 5];
  }
  if (param_5 != 0) {
    uVar1 = *(undefined2 *)(&DAT_0065e80c + iVar4 * 5);
    piVar2 = &DAT_0065e804 + iVar4 * 5;
    while (iVar5 = iVar5 + 1, iVar5 < DAT_0051c2f8) {
      iVar4 = iVar4 + -1;
      if (iVar4 < 0) {
        iVar4 = 0x13;
      }
      piVar6 = &DAT_0065e804 + iVar4 * 5;
      piVar7 = piVar2;
      for (iVar3 = 5; piVar2 = &DAT_0065e804 + iVar4 * 5, iVar3 != 0; iVar3 = iVar3 + -1) {
        *piVar7 = *piVar6;
        piVar6 = piVar6 + 1;
        piVar7 = piVar7 + 1;
      }
    }
    DAT_0051c2f8 = DAT_0051c2f8 + -1;
    FUN_0048dc22(CONCAT22((short)((uint)iVar4 >> 0x10),uVar1));
    if (DAT_0051c2f8 == 0) {
      DAT_0051c2fc = 0;
    }
  }
  return 1;
}

