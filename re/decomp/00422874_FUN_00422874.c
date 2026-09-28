// FUN_00422874 @ 00422874 size=94 sig=undefined FUN_00422874() cc=unknown
// callers: FUN_004228d4
// callees: 

void FUN_00422874(int param_1,undefined4 param_2)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = 0;
  (&DAT_00540ce0)[param_1 * 0x4802] = 1;
  for (pcVar1 = &DAT_0053c4e4 + param_1 * 0x4802; *pcVar1 == '\x01'; pcVar1 = pcVar1 + 6) {
    iVar2 = iVar2 + 1;
  }
  (&DAT_0053c4e4)[iVar2 * 6 + param_1 * 0x4802] = 1;
  *(undefined4 *)(&DAT_0053c4e0 + iVar2 * 6 + param_1 * 0x4802) = param_2;
  return;
}

