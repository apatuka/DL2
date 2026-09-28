// FUN_00401830 @ 00401830 size=165 sig=undefined FUN_00401830() cc=unknown
// callers: FUN_004018d8,FUN_004618e8,FUN_0047958c,FUN_00461078,RaceInit,ChCht,FUN_0047c730
// callees: memset,FUN_00408784

void FUN_00401830(int param_1)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  
  iVar3 = param_1 * 0x2d8;
  iVar1 = (int)(char)(&DAT_0059f161)[iVar3];
  if (2 < iVar1) {
    *(undefined **)(&DAT_0059f1a6 + iVar3) = (&PTR_DAT_004b502c)[iVar1 * 6];
    *(undefined **)(&DAT_0059f1aa + iVar3) = (&PTR_DAT_004b5030)[iVar1 * 6];
    *(undefined **)(&DAT_0059f1ae + iVar3) = (&PTR_DAT_004b5034)[iVar1 * 6];
    *(undefined **)(&DAT_0059f1b2 + iVar3) = (&PTR_DAT_004b5038)[iVar1 * 6];
    *(undefined4 *)(&DAT_0059f1b6 + iVar3) = *(undefined4 *)(&DAT_004b503c + iVar1 * 0x18);
    *(undefined4 *)(&DAT_0059f1ba + iVar3) = *(undefined4 *)(&DAT_004b5040 + iVar1 * 0x18);
    memset(&DAT_0059f1be + iVar3,0,0x21c);
    iVar1 = 0;
    puVar2 = &DAT_0059f1be + iVar3;
    do {
      *puVar2 = (char)iVar1;
      *(code **)(puVar2 + 2) = FUN_00401988;
      *(code **)(puVar2 + 6) = FUN_00401988;
      *(code **)(puVar2 + 10) = FUN_00401988;
      *(code **)(puVar2 + 0xe) = FUN_00401988;
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 0x5a;
    } while (iVar1 < 6);
    FUN_00408784(param_1);
  }
  return;
}

