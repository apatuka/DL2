// FUN_00495bb1 @ 00495bb1 size=61 sig=undefined FUN_00495bb1() cc=unknown
// callers: FUN_0046ff98
// callees: 

undefined4 FUN_00495bb1(void)

{
  int iVar1;
  
  if (DAT_0051e07c != 0) {
    iVar1 = 0;
    do {
      if ((&DAT_0065edc4)[iVar1 * 3] != 0) {
        (*(code *)(&DAT_0065edc4)[iVar1 * 3])();
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
    DAT_0051e07c = 0;
  }
  return 1;
}

