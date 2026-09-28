// FUN_0045ae78 @ 0045ae78 size=77 sig=undefined FUN_0045ae78() cc=unknown
// callers: FUN_0043baf4,FUN_0043be98
// callees: FUN_00436d84,FUN_00436db8,FUN_0042836c
// strings: \"You cannot set tax rates for a territory you do not own.\"|\"Oolan's Advice\"

void FUN_0045ae78(void)

{
  if ((char)(&DAT_005a43f0)[DAT_004c5b50 * 0xadc] != DAT_0058f1f4) {
    FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_You_cannot_set_tax_rates_for_a_t_00509794,4,0,9
                );
    return;
  }
  FUN_00436db8();
  FUN_00436d84();
  return;
}

