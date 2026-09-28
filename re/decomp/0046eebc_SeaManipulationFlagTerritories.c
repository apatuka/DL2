// SeaManipulationFlagTerritories @ 0046eebc size=546 sig=undefined SeaManipulationFlagTerritories() cc=unknown
// callers: FUN_0046f0e0
// callees: FUN_0046c9d8,FUN_0044134c
// strings: \"SeaManipulationFlagTerritories\"

/* WARNING: Type propagation algorithm not settling */
/* auto-named from string evidence: SeaManipulationFlagTerritories */

void SeaManipulationFlagTerritories(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined1 *puVar4;
  int *piVar5;
  char cVar6;
  int local_20;
  int local_1c [3];
  undefined4 local_10;
  int local_c;
  int local_8;
  
  cVar6 = '\x02';
  if (param_2 != 0x2b) {
    cVar6 = '\x03';
  }
  local_8 = 1;
  for (iVar1 = *(int *)(param_1 + 0x76); (local_8 != 0 && (iVar1 != 0));
      iVar1 = *(int *)(iVar1 + 0x54)) {
    if (((cVar6 == (&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24]) ||
        ((*(char *)(iVar1 + 6) == '\x1b' && (cVar6 == '\x02')))) &&
       ((param_3 == *(char *)(iVar1 + 8) ||
        (iVar2 = FUN_0044134c(param_3,(int)*(char *)(iVar1 + 8)), iVar2 != 0)))) {
      local_8 = 0;
    }
  }
  for (iVar1 = *(int *)(param_1 + 0x7a); (local_8 != 0 && (iVar1 != 0));
      iVar1 = *(int *)(iVar1 + 0x54)) {
    if (((cVar6 == (&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24]) ||
        ((*(char *)(iVar1 + 6) == '\x1b' && (cVar6 == '\x02')))) &&
       ((param_3 == *(char *)(iVar1 + 8) ||
        (iVar2 = FUN_0044134c(param_3,(int)*(char *)(iVar1 + 8)), iVar2 != 0)))) {
      local_8 = 0;
    }
  }
  if (param_2 == 0x2b) {
    if ((*(char *)(param_1 + 0x21) == '\0') && (local_8 != 0)) {
      local_c = *(char *)(param_1 + 0x995) + 0x19;
      local_10 = 0x32;
      if (local_c < 0x33) {
        puVar4 = (undefined1 *)&local_c;
      }
      else {
        puVar4 = (undefined1 *)&local_10;
      }
      *(undefined1 *)(param_1 + 0x995) = *puVar4;
      *(byte *)(param_1 + 0x998) = *(byte *)(param_1 + 0x998) | '\x01' << ((byte)param_3 & 0x1f);
    }
  }
  else if (param_2 == 0x2c) {
    if (local_8 != 0) {
      local_1c[2] = *(char *)(param_1 + 0x996) + 0x19;
      local_1c[1] = 0x32;
      if (local_1c[2] < 0x33) {
        piVar5 = local_1c + 2;
      }
      else {
        piVar5 = local_1c + 1;
      }
      *(char *)(param_1 + 0x996) = (char)*piVar5;
      *(byte *)(param_1 + 0x998) = *(byte *)(param_1 + 0x998) | '\x01' << ((byte)param_3 & 0x1f);
    }
    if ((param_3 == *(char *)(param_1 + 0x20)) ||
       (iVar1 = FUN_0044134c(param_3,(int)*(char *)(param_1 + 0x20)), iVar1 != 0)) {
      local_1c[0] = *(char *)(param_1 + 0x994) + 0x28;
      local_20 = 0x32;
      if (local_1c[0] < 0x33) {
        piVar5 = local_1c;
      }
      else {
        piVar5 = &local_20;
      }
      *(char *)(param_1 + 0x994) = (char)*piVar5;
      iVar1 = 0;
      do {
        iVar2 = FUN_0044134c(param_3,iVar1);
        if ((iVar2 == 0) && (iVar1 != param_3)) {
          *(byte *)(param_1 + 0x997) = *(byte *)(param_1 + 0x997) | '\x01' << ((byte)iVar1 & 0x1f);
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < 7);
    }
    else if ((param_4 != 0) &&
            ((*(char *)(param_1 + 0x21) != '\0' &&
             (uVar3 = FUN_0046c9d8(100,s_SeaManipulationFlagTerritories_004d5cf3), uVar3 < 0x28))))
    {
      *(undefined1 *)(param_1 + 0x999) = 1;
    }
  }
  return;
}

