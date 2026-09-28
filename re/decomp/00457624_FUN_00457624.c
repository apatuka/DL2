// FUN_00457624 @ 00457624 size=574 sig=undefined FUN_00457624() cc=unknown
// callers: WinMain
// callees: FUN_00456214,FUN_004571d4,FUN_004412d4,FUN_0046c9cc,FUN_0045727c,FUN_00450fa8,FUN_004237d0,FUN_00456c10,FUN_00446bf0,FUN_00446084
// strings: \"Combat\"

void FUN_00457624(void)

{
  undefined4 uVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  
  DAT_004cf850 = 0;
  FUN_004571d4();
  iVar6 = 0;
  DAT_005649d0 = DAT_0059f154;
  puVar4 = &DAT_0057bd38;
  do {
    uVar1 = FUN_0046c9cc(s_Combat_004d02af);
    *puVar4 = uVar1;
    iVar6 = iVar6 + 1;
    puVar4 = (undefined4 *)((int)puVar4 + 0x86);
  } while (iVar6 < 0x20);
  FUN_0045727c();
  for (puVar4 = &DAT_005a4eac; puVar4 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar4 = puVar4 + 0x2b7) {
    uVar5 = 0;
    for (puVar2 = (undefined2 *)FUN_00456214(*(undefined4 *)((int)puVar4 + 0x7a),0xffffffff);
        puVar2 != (undefined2 *)0x0;
        puVar2 = (undefined2 *)FUN_00456214(*(undefined4 *)((int)puVar4 + 0x7a),*puVar2)) {
      iVar6 = FUN_00446bf0(puVar2);
      if ((iVar6 == 0) && (iVar6 = FUN_00450fa8(puVar2), iVar6 == 0)) {
        for (puVar3 = (undefined2 *)FUN_00456214(*(undefined4 *)((int)puVar4 + 0x7a),*puVar2);
            puVar3 != (undefined2 *)0x0;
            puVar3 = (undefined2 *)FUN_00456214(*(undefined4 *)((int)puVar4 + 0x7a),*puVar3)) {
          iVar6 = FUN_00446bf0(puVar3);
          if ((((iVar6 == 0) && (iVar6 = FUN_00450fa8(puVar3), iVar6 == 0)) &&
              (puVar3 != (undefined2 *)0x0)) &&
             ((*(char *)(puVar3 + 4) != *(char *)(puVar2 + 4) &&
              (iVar6 = FUN_004412d4((int)*(char *)(puVar2 + 4),(int)*(char *)(puVar3 + 4),1),
              iVar6 != 0)))) {
            if ((1 << (*(byte *)(puVar2 + 4) & 0x1f) & uVar5) == 0) {
              FUN_004237d0((int)(char)*(byte *)(puVar2 + 4),0x23,
                           (&PTR_s_ChCh_t_00509038)
                           [(char)(&DAT_0059f162)[*(char *)(puVar3 + 4) * 0x2d8]],puVar4,0,0,0,0);
            }
            uVar5 = uVar5 | 1 << (*(byte *)(puVar2 + 4) & 0x1f);
            if ((1 << (*(byte *)(puVar3 + 4) & 0x1f) & uVar5) == 0) {
              FUN_004237d0((int)(char)*(byte *)(puVar3 + 4),0x23,
                           (&PTR_s_ChCh_t_00509038)
                           [(char)(&DAT_0059f162)[*(char *)(puVar2 + 4) * 0x2d8]],puVar4,0,0,0,0);
            }
            uVar5 = uVar5 | 1 << (*(byte *)(puVar3 + 4) & 0x1f);
          }
        }
      }
    }
    if (uVar5 != 0) {
      for (puVar2 = (undefined2 *)FUN_00456214(*(undefined4 *)((int)puVar4 + 0x7a),0xffffffff);
          puVar2 != (undefined2 *)0x0;
          puVar2 = (undefined2 *)FUN_00456214(*(undefined4 *)((int)puVar4 + 0x7a),*puVar2)) {
        iVar6 = FUN_00446bf0(puVar2);
        if (((iVar6 == 0) && (iVar6 = FUN_00450fa8(puVar2), iVar6 == 0)) &&
           ((1 << (*(byte *)(puVar2 + 4) & 0x1f) & uVar5) != 0)) {
          *(undefined4 *)(puVar2 + 0x22) = *(undefined4 *)(puVar2 + 0x1c);
          FUN_00446084(puVar2,*(undefined4 *)(puVar2 + 0x1c),0);
        }
      }
    }
    if (*(int *)((int)puVar4 + 0x7a) != 0) {
      FUN_00456c10(puVar4);
    }
  }
  return;
}

