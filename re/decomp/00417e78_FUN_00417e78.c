// FUN_00417e78 @ 00417e78 size=147 sig=undefined FUN_00417e78() cc=unknown
// callers: FUN_004180b0
// callees: 

void FUN_00417e78(int param_1,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  (&DAT_00533405)[param_2 * 0x146] = 0;
  if ((&DAT_0059f162)[*(char *)(param_1 + 8) * 0x2d8] == PTR_DAT_004d5988[2]) {
    (&DAT_00533404)[param_2 * 0x146] = 1;
  }
  else {
    (&DAT_00533404)[param_2 * 0x146] = 0;
  }
  *(undefined4 *)(&DAT_00533400 + param_2 * 0x146) = param_3;
  iVar2 = 0;
  puVar1 = (undefined4 *)((int)&DAT_005332d8 + param_2 * 0x146);
  do {
    iVar2 = iVar2 + 1;
    *puVar1 = 0;
    puVar1 = puVar1 + 8;
  } while (iVar2 < 10);
  return;
}

