// FUN_0043bd5c @ 0043bd5c size=152 sig=undefined FUN_0043bd5c() cc=unknown
// callers: FUN_0043be98,FUN_0047361c
// callees: FUN_0042836c,FUN_0042e2f8,FUN_00449dec,FUN_00474718
// strings: \"You cannot create a landing site on another race's territory.\"|\"Add Race Error\"|\"There are already 7 races in this scenario.\"|\"That territory is not suitable as a landing site.\"

void FUN_0043bd5c(void)

{
  int iVar1;
  undefined4 local_c;
  
  iVar1 = FUN_0042e2f8(&local_c,0xffffffff);
  if ((iVar1 != -1) &&
     (iVar1 = FUN_00474718(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,iVar1,local_c), iVar1 != 0)) {
    if (iVar1 == 1) {
      FUN_0042836c(PTR_s_Add_Race_Error_00509bcc,PTR_s_You_cannot_create_a_landing_site_00509bd0,4,0
                   ,9);
    }
    else if (iVar1 == 2) {
      FUN_0042836c(PTR_s_Add_Race_Error_00509bcc,PTR_s_That_territory_is_not_suitable_a_00509bd8,4,0
                   ,9);
    }
    else if (iVar1 == 3) {
      FUN_0042836c(PTR_s_Add_Race_Error_00509bcc,PTR_s_There_are_already_7_races_in_thi_00509bd4,4,0
                   ,9);
    }
  }
  FUN_00449dec();
  return;
}

