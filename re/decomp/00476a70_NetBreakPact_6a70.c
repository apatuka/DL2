// NetBreakPact_6a70 @ 00476a70 size=58 sig=undefined NetBreakPact_6a70() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00475048,FUN_00441590
// strings: \"Error in NetBreakPact.\"

/* auto-named from string evidence: NetBreakPact */

bool NetBreakPact_6a70(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00441590(*(undefined2 *)(param_1 + 0x1a),*(undefined2 *)(param_1 + 0x1c),
                       *(undefined2 *)(param_1 + 0x18));
  if (iVar1 == 0) {
    FUN_00475048(s_Error_in_NetBreakPact__004dc17d,param_1);
  }
  return iVar1 != 0;
}

