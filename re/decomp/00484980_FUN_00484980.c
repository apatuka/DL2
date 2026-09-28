// FUN_00484980 @ 00484980 size=472 sig=undefined FUN_00484980() cc=unknown
// callers: @TransferDialog$qqspvuiuil
// callees: DestroyWindow,sprintf,SetDlgItemTextA,SendDlgItemMessageA,SetWindowTextA,GetDlgItem,FUN_004727dc,FUN_0046d180,SetDlgItemInt,FUN_00484864,SetFocus
// strings: \"Transferring Materials\"|\"Transferring %s from %s to %s.\"|\"Price per unit:\"|\"Selling Materials\"|\"Offering to sell some of our %s in %s to the %s.\"|\"Sale price offered:\"

void FUN_00484980(HWND param_1,int param_2)

{
  HWND pHVar1;
  CHAR local_104 [256];
  
  DAT_0065e024 = DAT_00583d74;
  DAT_0065e01c = &DAT_005a43d0 + DAT_00583d78 * 0xadc;
  DAT_0065e020 = &DAT_005a43d0 + param_2 * 0xadc;
  DAT_0065e018 = FUN_004727dc(DAT_0065e01c,DAT_0065e020);
  if (DAT_0065e01c[0x20] == DAT_0065e020[0x20]) {
    SetWindowTextA(param_1,PTR_s_Transferring_Materials_00509a40);
    sprintf(local_104,PTR_s_Transferring__s_from__s_to__s__00509a44,
            (&PTR_s_credits_00509098)[DAT_0065e024],DAT_0065e01c,DAT_0065e020);
    SetDlgItemTextA(param_1,8,local_104);
    SetDlgItemInt(param_1,0xc9,0,0);
    SetDlgItemTextA(param_1,0xf,PTR_s_Price_per_unit__00509a48);
    SetDlgItemInt(param_1,0xb,DAT_0065e018,0);
    FUN_00484864(param_1);
    pHVar1 = GetDlgItem(param_1,0xb);
    DestroyWindow(pHVar1);
    pHVar1 = GetDlgItem(param_1,0xf);
    DestroyWindow(pHVar1);
  }
  else {
    SetWindowTextA(param_1,PTR_s_Selling_Materials_00509a4c);
    sprintf(local_104,PTR_s_Offering_to_sell_some_of_our__s_i_00509a50,
            (&PTR_s_credits_00509098)[DAT_0065e024],DAT_0065e01c,
            (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(char)DAT_0065e020[0x20] * 0x2d8]]);
    SetDlgItemTextA(param_1,8,local_104);
    SetDlgItemInt(param_1,0xc9,0,0);
    SetDlgItemTextA(param_1,0xf,PTR_s_Sale_price_offered__00509a54);
    SetDlgItemInt(param_1,0xb,1,0);
    FUN_00484864(param_1);
  }
  pHVar1 = GetDlgItem(param_1,0xc9);
  SetFocus(pHVar1);
  SendDlgItemMessageA(param_1,0xc9,0xb1,0,-1);
  FUN_0046d180(param_1);
  return;
}

