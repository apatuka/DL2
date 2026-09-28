// CreateHit @ 0043d6e4 size=380 sig=undefined CreateHit() cc=unknown
// callers: FUN_0043d974,FUN_00455c88,FUN_0043d958
// callees: DebugMessage,FUN_0043d004,FUN_00482ac4,FUN_00444f20,FUN_0046ca40,FUN_004864c4,FUN_00444b74
// strings: \"NULL warrior in CreateHit\"

/* auto-named from string evidence: CreateHit */

void CreateHit(int param_1,int param_2,int param_3)

{
  char cVar1;
  char cVar2;
  ushort *puVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    DebugMessage(s_NULL_warrior_in_CreateHit_004c49b8);
  }
  else {
    puVar3 = (ushort *)
             FUN_00444f20(param_3,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),0)
    ;
    if (puVar3 != (ushort *)0x0) {
      FUN_004864c4(puVar3,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24));
      if ((*(char *)(param_1 + 0x1d) == '\0') || (*(int *)(param_1 + 0x38) == 0)) {
        FUN_00444b74(puVar3,0x7531);
      }
      else {
        iVar6 = *(int *)(param_1 + 0x38) + -0x561a34;
        if (iVar6 < 0) {
          iVar6 = *(int *)(param_1 + 0x38) + -0x5619f5;
        }
        puVar3[0x19] = (ushort)(iVar6 >> 6);
        *puVar3 = *puVar3 | 0x10;
        FUN_00444b74(puVar3,*(short *)(*(int *)(param_1 + 0x38) + 4) + 2);
      }
      if (param_3 == 0x195) {
        iVar6 = 0x6f;
      }
      else if (param_3 == 0x197) {
        iVar6 = 0x71;
      }
      else {
        cVar1 = (&DAT_004faf87)[*(int *)(param_2 + 4) * 0x24];
        cVar2 = (&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24];
        if (((cVar2 == '\v') || (cVar2 == '\x01')) || (cVar2 == '\x06')) {
          uVar4 = FUN_0046ca40();
          if (uVar4 % 100 == 0) {
            uVar4 = FUN_0046ca40();
            iVar6 = uVar4 % 3 + 0x55;
          }
          else {
            uVar4 = FUN_0046ca40();
            iVar6 = uVar4 % 9 + 0x5e;
          }
        }
        else {
          iVar6 = 0x7f;
          if (((cVar1 != '\v') && (cVar1 != '\x01')) && (cVar1 != '\x06')) {
            iVar6 = 0x80;
          }
        }
      }
      if ((puVar3 == (ushort *)0x0) || (*(int *)(puVar3 + 0xb) == 0)) {
        FUN_00482ac4(iVar6,0,1,0,0,0);
      }
      else {
        uVar7 = 0;
        uVar5 = FUN_0043d004((*(int *)(puVar3 + 3) >> 8) + (int)**(short **)(puVar3 + 0xb));
        FUN_00482ac4(iVar6,0,1,0,uVar5,uVar7);
      }
    }
  }
  return;
}

