// FUN_004748dc @ 004748dc size=65 sig=undefined FUN_004748dc() cc=unknown
// callers: FUN_0042b280,FUN_00438b14,FUN_0045e4f4,FUN_0041b280,FUN_004164e8,FUN_004148ec,FUN_0043be24,FUN_004166f4
// callees: FUN_0049117e,FUN_0042836c
// strings: \"Oolan's Advice\"

undefined4 FUN_004748dc(void)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  iVar3 = 0;
  pcVar1 = &DAT_0059f161;
  do {
    if (*pcVar1 != '\0') {
      return 0;
    }
    iVar3 = iVar3 + 1;
    pcVar1 = pcVar1 + 0x2d8;
  } while (iVar3 < 7);
  uVar6 = 5;
  uVar5 = 0;
  uVar4 = 4;
  uVar2 = FUN_0049117e(0,0x54494445,5);
  FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,uVar2,uVar4,uVar5,uVar6);
  return 1;
}

