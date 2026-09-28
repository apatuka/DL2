// FUN_0045c67c @ 0045c67c size=133 sig=undefined FUN_0045c67c() cc=unknown
// callers: RunAITurns
// callees: FUN_00401ac0,FUN_0046f89c

void FUN_0045c67c(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  FUN_0046f89c();
  iVar3 = 0;
  piVar2 = &DAT_005904dc;
  do {
    iVar1 = *piVar2;
    if (((((&DAT_00645376)[iVar1 * 0x5c] != '\0') && ((&DAT_006453b4)[iVar1 * 0x17] != 0)) &&
        ((&DAT_006453ac)[iVar1 * 0x17] != (&DAT_006453b4)[iVar1 * 0x17])) &&
       ((char)(&DAT_0059f161)[(char)(&DAT_00645378)[iVar1 * 0x5c] * 0x2d8] < '\x03')) {
      FUN_00401ac0(&DAT_00645370 + iVar1 * 0x2e,(&DAT_006453b4)[iVar1 * 0x17],0);
    }
    if ((&DAT_006453ac)[iVar1 * 0x17] == (&DAT_006453b4)[iVar1 * 0x17]) {
      (&DAT_006453b4)[iVar1 * 0x17] = 0;
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar3 < 0x230);
  return;
}

