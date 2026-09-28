// FUN_00445d30 @ 00445d30 size=432 sig=undefined FUN_00445d30() cc=unknown
// callers: SyncCreateUnit,FUN_004776e4,FUN_00431e58,FUN_00477724
// callees: FUN_004471c0,FUN_0044577c,FUN_00445b94,FUN_00445a04,sprintf,FUN_00447190,FUN_004a6b48,FUN_00477724
// strings: \"%s %s #%d\"

ushort * FUN_00445d30(int param_1,int param_2,int param_3,ushort param_4)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  ushort *puVar4;
  undefined1 local_110 [256];
  int local_10;
  int local_c;
  int local_8;
  
  puVar4 = (ushort *)0x0;
  local_10 = (int)(char)(&DAT_004faf87)[param_3 * 0x24];
  if (*(char *)(param_1 + 0x20) == param_2) {
    local_8 = param_1 + 0x76;
  }
  else {
    local_8 = param_1 + 0x7a;
  }
  local_c = param_1;
  iVar3 = FUN_00445b94(param_1,param_3);
  if (iVar3 != 0) {
    puVar4 = (ushort *)FUN_0044577c(local_8);
    if (puVar4 != (ushort *)0x0) {
      *puVar4 = param_4;
      puVar4[1] = 0;
      *(char *)(puVar4 + 3) = (char)param_3;
      *(undefined1 *)((int)puVar4 + 7) = (undefined1)local_10;
      *(undefined1 *)(puVar4 + 4) = (undefined1)param_2;
      uVar2 = FUN_00447190(puVar4);
      *(undefined1 *)(puVar4 + 5) = uVar2;
      *(undefined1 *)(puVar4 + 0x12) = 0;
      puVar4[0x1b] = 0;
      puVar4[0x14] = 0;
      puVar4[0x15] = 0;
      *(undefined1 *)((int)puVar4 + 0x25) = 0;
      *(undefined1 *)(puVar4 + 0x13) = 100;
      sprintf(local_110,s__s__s___d_004c533f,
              (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[(char)puVar4[4] * 0x2d8]],
              (&PTR_s_No_Unit_005095e4)[param_3],*puVar4 & 0x3ff);
      FUN_004a6b48((int)puVar4 + 0xb,local_110,0x18);
      *(int *)(puVar4 + 0x1c) = local_c;
      *(int *)(puVar4 + 0x20) = local_c;
      *(int *)(puVar4 + 0x1e) = local_c;
      if ((*(char *)(param_1 + 0x21) == '\0') && ((&DAT_004faf8d)[(char)puVar4[3] * 0x24] == '\x01')
         ) {
        FUN_00445a04(puVar4);
      }
      if (((char)puVar4[3] == '#') && (DAT_0058f1f4 == DAT_004d5a58)) {
        iVar3 = FUN_00477724(param_1,param_2,0x24);
        if (iVar3 != 0) {
          *(ushort **)(iVar3 + 0x48) = puVar4;
          *(int *)(puVar4 + 0x24) = iVar3;
        }
      }
      cVar1 = (&DAT_004faf87)[param_3 * 0x24];
      if ((((cVar1 == '\x06') || (cVar1 == '\v')) || (cVar1 == '\r')) ||
         ((cVar1 == '\x11' || (cVar1 == '\x04')))) {
        *(undefined1 *)(puVar4 + 0x12) = 0x1a;
      }
      if ((DAT_004d5aa0 != '\0') && ((char)puVar4[3] != '$')) {
        FUN_004471c0(param_1);
      }
    }
  }
  return puVar4;
}

