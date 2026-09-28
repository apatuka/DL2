// CreateBldgHit @ 0043dae0 size=167 sig=undefined CreateBldgHit() cc=unknown
// callers: FUN_00455c88
// callees: DebugMessage,FUN_0043d004,FUN_00482ac4,FUN_00444f20,FUN_004864c4,FUN_00444b74
// strings: \"NULL building in CreateBldgHit\"

/* auto-named from string evidence: CreateBldgHit */

void CreateBldgHit(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_1 == 0) {
    DebugMessage(s_NULL_building_in_CreateBldgHit_004c49d2);
  }
  else {
    iVar2 = FUN_00444f20(0xb5,*(undefined4 *)(param_1 + 6),*(undefined4 *)(param_1 + 10),0);
    if (iVar2 != 0) {
      FUN_004864c4(iVar2,*(undefined4 *)(param_1 + 6),*(undefined4 *)(param_1 + 10));
      FUN_00444b74(iVar2,0x7531);
      cVar1 = (&DAT_004faf87)[param_2 * 0x24];
      if (((cVar1 == '\v') || (cVar1 == '\x01')) || (cVar1 == '\x06')) {
        uVar4 = 0;
        uVar3 = FUN_0043d004((int)*(short *)(iVar2 + 0xe));
        FUN_00482ac4(0x42,0,1,0,uVar3,uVar4);
      }
      else {
        uVar4 = 0;
        uVar3 = FUN_0043d004((int)*(short *)(iVar2 + 0xe));
        FUN_00482ac4(0x43,0,1,0,uVar3,uVar4);
      }
    }
  }
  return;
}

