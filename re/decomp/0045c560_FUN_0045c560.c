// FUN_0045c560 @ 0045c560 size=283 sig=undefined FUN_0045c560() cc=unknown
// callers: FUN_0045ccf8
// callees: FUN_00418d18,FUN_00401ac0,FUN_00419684,FUN_0045965c,FUN_0044a000,FUN_00419678,FUN_004596d0,FUN_0042836c,FUN_00449dec
// strings: \"Missiles can only be launched into neutral or enemy territories.\"|\"Oolan's Advice\"

void FUN_0045c560(undefined *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = DAT_00583d80 * 0xadc;
  if (param_1 != &DAT_005a43d0 + iVar3) {
    for (puVar2 = (undefined4 *)&DAT_00645370; puVar2 < &DAT_00651cb0; puVar2 = puVar2 + 0x17) {
      if ((*(char *)((int)puVar2 + 6) != '\0') &&
         (((DAT_004d5aa0 != '\0' || (*(char *)(puVar2 + 2) == DAT_0058f1f4)) &&
          (&DAT_005a43d0 + iVar3 == (undefined *)puVar2[0xf])))) {
        if ((&DAT_005a43f1)[iVar3] == '\0') {
          iVar1 = FUN_0045965c(puVar2);
        }
        else {
          iVar1 = FUN_004596d0(puVar2);
        }
        if ((iVar1 == DAT_00583d7c) || (param_2 != 0)) {
          puVar2[0x11] = param_1;
          if ((((DAT_004d5aa0 == '\0') &&
               ((DAT_00583d7c == 4 && (param_1[0x20] == *(char *)(puVar2 + 2))))) &&
              (param_1 != (undefined *)puVar2[0xf])) &&
             ((param_1 != (undefined *)puVar2[0xe] && ((char)param_1[0x20] == DAT_0058f1f4)))) {
            FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,
                         PTR_s_Missiles_can_only_be_launched_in_005096b4,4,0,9);
            return;
          }
          FUN_00401ac0(puVar2,param_1,0);
        }
      }
    }
    if (DAT_004d59b4 == 0x22) {
      FUN_00419678();
      FUN_00419684();
      FUN_00418d18();
      FUN_0044a000();
    }
    FUN_00449dec();
  }
  return;
}

