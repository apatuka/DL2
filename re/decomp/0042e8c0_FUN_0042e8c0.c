// FUN_0042e8c0 @ 0042e8c0 size=457 sig=undefined FUN_0042e8c0() cc=unknown
// callers: FUN_0042eaec,FUN_0042ebb8
// callees: FUN_0049eb44,GetHighScores,sprintf,FUN_004419c8

void FUN_0042e8c0(void)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *local_3c;
  undefined4 *local_38;
  undefined4 *local_34;
  undefined1 local_30 [32];
  
  iVar4 = 0;
  puVar3 = &DAT_004c37a8;
  puVar6 = &DAT_004c3780;
  local_3c = &DAT_004c37d0;
  puVar1 = &DAT_004c3758;
  do {
    FUN_0049eb44(DAT_004c3744,*puVar1,1,0xf,0,&DAT_004c37f8);
    FUN_0049eb44(DAT_004c3744,*puVar6,1,0xf,0,&DAT_004c37f8);
    FUN_0049eb44(DAT_004c3744,*puVar3,1,0xf,0,&DAT_004c37f8);
    FUN_0049eb44(DAT_004c3744,*local_3c,1,0xf,0,&DAT_004c37f8);
    local_3c = local_3c + 1;
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
    puVar6 = puVar6 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar4 < 10);
  iVar4 = GetHighScores();
  if (iVar4 != 0) {
    local_34 = &DAT_004c37d0;
    local_38 = &DAT_004c3780;
    iVar5 = 0;
    puVar3 = &DAT_004c37a8;
    puVar1 = &DAT_004c3758;
    piVar2 = (int *)(iVar4 + 0x26);
    do {
      if (*piVar2 != 0) {
        FUN_0049eb44(DAT_004c3744,*puVar1,1,0xf,0,iVar5 * 0x2a + iVar4);
        FUN_0049eb44(DAT_004c3744,*local_38,1,0xf,0,
                     (&PTR_s_ChCh_t_00509038)[*(char *)((int)piVar2 + -6)]);
        if (piVar2[-1] == 0) {
          FUN_0049eb44(DAT_004c3744,*puVar3,1,0xf,0,PTR_DAT_00508fb4);
        }
        else {
          FUN_0049eb44(DAT_004c3744,*puVar3,1,0xf,0,PTR_DAT_00508fb0);
        }
        sprintf(local_30,&DAT_004c37fa,*piVar2);
        FUN_0049eb44(DAT_004c3744,*local_34,1,0xf,0,local_30);
      }
      local_34 = local_34 + 1;
      local_38 = local_38 + 1;
      iVar5 = iVar5 + 1;
      puVar3 = puVar3 + 1;
      puVar1 = puVar1 + 1;
      piVar2 = (int *)((int)piVar2 + 0x2a);
    } while (iVar5 < 10);
    FUN_004419c8(iVar4);
  }
  return;
}

