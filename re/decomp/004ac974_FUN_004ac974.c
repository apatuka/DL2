// FUN_004ac974 @ 004ac974 size=148 sig=undefined FUN_004ac974() cc=unknown
// callers: FUN_004ac1c8,FUN_004ace78,FUN_004ac2cc,FUN_004ac4cc,FUN_004acf20
// callees: FUN_004b38b0,FUN_004b382c,memset,FUN_004ac964,FUN_004ac930,FUN_004b0b44,FUN_004b3890
// strings: \"allocating handle lock table\"|\"creating handle lock\"

void FUN_004ac974(int param_1)

{
  int iVar1;
  
  if ((DAT_0069f568 == 0) || (*(int *)(DAT_0069f568 + param_1 * 4) == 0)) {
    FUN_004ac930();
    if (DAT_0069f568 == 0) {
      iVar1 = DAT_00520194 << 2;
      DAT_0069f568 = FUN_004b0b44(iVar1);
      if (DAT_0069f568 == 0) {
        FUN_004b38b0(s_allocating_handle_lock_table_0052084c);
      }
      memset(DAT_0069f568,0,iVar1);
    }
    if (*(int *)(DAT_0069f568 + param_1 * 4) == 0) {
      FUN_004b382c(param_1 * 4 + DAT_0069f568,s_creating_handle_lock_00520869);
    }
    FUN_004ac964();
  }
  FUN_004b3890(*(undefined4 *)(DAT_0069f568 + param_1 * 4));
  return;
}

