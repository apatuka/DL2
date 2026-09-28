// SetRetreat @ 00451928 size=470 sig=undefined SetRetreat() cc=unknown
// callers: FUN_00451b68
// callees: FUN_00446bf0,DebugMessage,FUN_00445b94,FUN_004412d4,FUN_00448284
// strings: \"Invalid plane parent or parent territory in SetRetreat()\"

/* auto-named from string evidence: SetRetreat */

uint SetRetreat(int *param_1)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ushort *local_1c;
  int local_14;
  ushort local_e;
  int local_c;
  
  iVar3 = param_1[1];
  if ((((iVar3 == 0x17) || ((&DAT_004faf87)[iVar3 * 0x24] == '\n')) ||
      ((&DAT_004faf87)[iVar3 * 0x24] == '\t')) || (iVar3 = FUN_00448284(param_1), iVar3 != 0)) {
    return 0xffffffff;
  }
  bVar1 = *(byte *)((int)param_1 + 0x1e);
  if ((&DAT_004faf8d)[param_1[1] * 0x24] == '\x03') {
    iVar3 = *param_1;
    if ((iVar3 != 0) && (*(int *)(iVar3 + 0x38) != 0)) {
      return CONCAT22((short)((uint)iVar3 >> 0x10),*(undefined2 *)(*(int *)(*param_1 + 0x38) + 0x1a)
                     );
    }
    DebugMessage(s_Invalid_plane_parent_or_parent_t_004d0243);
    return 0xffffffff;
  }
  local_1c = (ushort *)(*(int *)(DAT_0057cdf8 + 4) + 0x890);
  local_c = 0;
  do {
    local_e = *local_1c;
    for (local_14 = 0; (local_e != 0 && (local_14 < 0x10)); local_14 = local_14 + 1) {
      if ((local_e & 1) != 0) {
        iVar3 = local_c * 0x10 + local_14;
        iVar5 = iVar3 * 0xadc;
        if ((((((int)(char)(&DAT_005a43f0)[iVar5] == (uint)bVar1) &&
              ((&DAT_005a444e)[iVar5] != '\0')) &&
             (((*(byte *)((int)&DAT_005a43ec + iVar5 + 1) & 1) == 0 &&
              (iVar4 = FUN_00445b94(&DAT_005a43d0 + iVar5,param_1[1]), iVar4 != 0)))) &&
            (((&DAT_004faf87)[param_1[1] * 0x24] != '\x03' ||
             ((int)(char)(&DAT_005a443d)[(uint)*(byte *)((int)param_1 + 0x1e) + iVar5] <= param_1[1]
             )))) && (((&DAT_004faf87)[param_1[1] * 0x24] != '\r' ||
                      ((char)(&DAT_005a443d)[(uint)*(byte *)((int)param_1 + 0x1e) + iVar5] < '\v')))
           ) {
          bVar2 = false;
          iVar5 = *(int *)(&DAT_005a444a + iVar5);
          while ((iVar5 != 0 && (!bVar2))) {
            iVar4 = FUN_00446bf0(iVar5);
            if ((iVar4 == 0) &&
               (iVar4 = FUN_004412d4((uint)bVar1,(int)*(char *)(iVar5 + 8),2), iVar4 == 0)) {
              bVar2 = true;
            }
            iVar5 = *(int *)(iVar5 + 0x54);
          }
          if (!bVar2) {
            return (uint)(ushort)(&DAT_005a43ea)[iVar3 * 0x56e];
          }
        }
      }
      local_e = (short)local_e >> 1;
    }
    local_c = local_c + 1;
    local_1c = local_1c + 1;
    if (6 < local_c) {
      return 0xffffffff;
    }
  } while( true );
}

