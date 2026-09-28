// FUN_004848cc @ 004848cc size=180 sig=undefined FUN_004848cc() cc=unknown
// callers: @TransferDialog$qqspvuiuil
// callees: EndDialog,FUN_0042836c,FUN_00484864,GetDlgItemInt
// strings: \"You may transfer materials between territories.  Simply indicate how much you wish to transfer.  The transport cost will be shown.  \\n\\nYou may also offer to sell materials to another player by dragging the materials to their territory.  If the buyer accepts, they will pay the cost of transport, in addition to your price.\"|\"Oolan's Advice\"

void FUN_004848cc(HWND param_1,ushort param_2)

{
  UINT *pUVar1;
  BOOL local_c;
  UINT local_8;
  
  local_8 = 0;
  if (param_2 < 10) {
    if (param_2 == 9) {
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_may_transfer_materials_betwe_00509a3c,4,0
                   ,9);
    }
    else if (param_2 == 1) {
      local_8 = GetDlgItemInt(param_1,0xc9,&local_c,0);
      pUVar1 = (UINT *)(DAT_0065e024 * 4 + DAT_0065e01c + 0x3a);
      if ((int)local_8 < (int)*pUVar1) {
        pUVar1 = &local_8;
      }
      local_8 = *pUVar1;
      EndDialog(param_1,local_8);
    }
    else if (param_2 == 2) {
      EndDialog(param_1,0);
    }
  }
  else if ((param_2 == 0xb) || (param_2 == 0xc9)) {
    FUN_00484864(param_1);
  }
  return;
}

