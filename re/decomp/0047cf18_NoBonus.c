// NoBonus @ 0047cf18 size=129 sig=undefined NoBonus() cc=unknown
// callers: 
// callees: FUN_0047cb04,FUN_0046681c,FUN_0046c9d8,FUN_00423690
// strings: \"NoBonus\"|\"NoBonus2\"

/* auto-named from string evidence: NoBonus, NoBonus2 */

void NoBonus(int param_1)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  
  if (*(int *)(param_1 + 4) == 0) {
    iVar1 = FUN_0046c9d8((int)DAT_004d5b18,s_NoBonus_004dcaf2);
    puVar3 = &DAT_005a43d0 + (iVar1 + 1) * 0xadc;
  }
  else {
    puVar3 = *(undefined **)(param_1 + 4);
  }
  if (*(short *)(puVar3 + 0x30) != 0) {
    iVar1 = FUN_0046c9d8(5,s_NoBonus2_004dcafa);
    iVar2 = FUN_0046681c(puVar3,*(undefined4 *)(&DAT_004dca4c + iVar1 * 4));
    if (iVar2 != 0) {
      FUN_00423690((int)(char)puVar3[0x20],0x67,(&PTR_s_iron_deposit_00509304)[iVar1],puVar3,0,0);
    }
  }
  FUN_0047cb04(param_1);
  return;
}

