// NetBreakPact @ 00476970 size=255 sig=undefined NetBreakPact() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: sprintf,FUN_00475048,FUN_00407248,FUN_00425364,FUN_004415d0,FUN_0042836c,FUN_004503f4
// strings: \"Error in NetBreakPact.\"|\"The %s have broken their %s pact with you\"|\"Pact Broken\"

/* auto-named from string evidence: NetBreakPact */

undefined4 NetBreakPact(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined1 local_88 [128];
  uint local_8;
  
  local_8 = (uint)*(ushort *)(param_1 + 0x18);
  uVar4 = (uint)*(ushort *)(param_1 + 0x1a);
  uVar3 = (uint)*(ushort *)(param_1 + 0x1c);
  iVar1 = FUN_004415d0(uVar4,uVar3,local_8);
  if (iVar1 == 0) {
    FUN_00475048(s_Error_in_NetBreakPact__004dc17d,param_1);
    uVar2 = 0;
  }
  else {
    if (((char)(&DAT_0059f161)[uVar3 * 0x2d8] < '\x03') || (DAT_0058f1f4 != DAT_004d5a58)) {
      if (uVar3 == DAT_0058f1f4) {
        sprintf(local_88,PTR_s_The__s_have_broken_their__s_pact_00509c20,
                (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[uVar4 * 0x2d8]],
                (&PTR_DAT_00508fb8)[local_8]);
        FUN_0042836c(PTR_s_Pact_Broken_00509c18,local_88,4,0,0x14);
        uVar5 = 0;
        uVar2 = FUN_004503f4((int)(char)(&DAT_0059f162)[uVar4 * 0x2d8],0x14,0xffffffff);
        FUN_00425364(uVar2,uVar5);
      }
    }
    else {
      FUN_00407248(uVar3,uVar4,local_8,0);
    }
    uVar2 = 1;
  }
  return uVar2;
}

