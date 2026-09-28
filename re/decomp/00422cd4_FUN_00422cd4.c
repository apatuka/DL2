// FUN_00422cd4 @ 00422cd4 size=48 sig=undefined FUN_00422cd4() cc=unknown
// callers: FUN_00423104,FUN_00423960,FUN_00422d18
// callees: 

void FUN_00422cd4(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  puVar2 = &DAT_00540ce0;
  do {
    *puVar2 = 0;
    iVar3 = 0;
    puVar1 = puVar2 + -0x47fc;
    do {
      *puVar1 = 0;
      iVar3 = iVar3 + 1;
      puVar1 = puVar1 + 6;
    } while (iVar3 < 0xc00);
    iVar4 = iVar4 + 1;
    puVar2 = puVar2 + 0x4802;
  } while (iVar4 < 6);
  return;
}

