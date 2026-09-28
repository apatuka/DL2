// NetMakePact @ 00476b1c size=58 sig=undefined NetMakePact() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00475048,FUN_00441700
// strings: \"Error in NetMakePact.\"

/* auto-named from string evidence: NetMakePact */

bool NetMakePact(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00441700(*(undefined2 *)(param_1 + 0x1a),*(undefined2 *)(param_1 + 0x1c),
                       *(undefined2 *)(param_1 + 0x18));
  if (iVar1 == 0) {
    FUN_00475048(s_Error_in_NetMakePact__004dc194,param_1);
  }
  return iVar1 != 0;
}

