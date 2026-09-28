// FUN_0040a37c @ 0040a37c size=65 sig=undefined FUN_0040a37c() cc=unknown
// callers: FUN_0040cea4,FUN_0040a3c0
// callees: FUN_004412d4

undefined4 FUN_0040a37c(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  pcVar3 = &DAT_0059f19e;
  iVar2 = 0;
  while ((iVar1 = FUN_004412d4(param_1,iVar2,8), iVar1 == 0 || (*pcVar3 != param_2))) {
    iVar2 = iVar2 + 1;
    pcVar3 = pcVar3 + 0x2d8;
    if (6 < iVar2) {
      return 0;
    }
  }
  return 1;
}

