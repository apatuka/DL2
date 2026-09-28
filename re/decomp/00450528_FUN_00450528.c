// FUN_00450528 @ 00450528 size=166 sig=undefined FUN_00450528() cc=unknown
// callers: FUN_00450b4c
// callees: FUN_00425364,FUN_004503f4

void FUN_00450528(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  
  pcVar4 = &DAT_0059f161;
  iVar3 = 0;
  cVar1 = (&DAT_0059f162)[param_1 * 0x2d8];
  do {
    if ((1 << ((byte)iVar3 & 0x1f) & param_2) != 0) {
      if (iVar3 == DAT_0058f1f4) {
        uVar5 = 0;
        uVar2 = FUN_004503f4((int)cVar1,param_3,param_4);
        FUN_00425364(uVar2,uVar5);
      }
      else if ((DAT_0058f1f4 == DAT_004d5a58) && (-1 < *pcVar4 + -3)) {
        (*(code *)(&PTR_FUN_004b5080)[(*pcVar4 + -3) * 6])(iVar3,param_1,param_3,param_4);
      }
    }
    iVar3 = iVar3 + 1;
    pcVar4 = pcVar4 + 0x2d8;
  } while (iVar3 < 7);
  return;
}

