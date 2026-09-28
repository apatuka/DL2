// FUN_00411b54 @ 00411b54 size=270 sig=undefined FUN_00411b54() cc=unknown
// callers: 
// callees: free,malloc,FUN_00411c64,FUN_00411808,memcpy,strlen,FUN_00411adc

undefined4 FUN_00411b54(int param_1,undefined1 *param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  uint *puVar7;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  uint *local_14;
  undefined4 local_10;
  undefined1 local_c [4];
  int local_8;
  
  uVar2 = strlen(param_2);
  if (uVar2 < 2) {
    uVar3 = 0;
  }
  else {
    local_18 = *param_2;
    local_17 = param_2[1];
    local_16 = 0x4e;
    local_15 = 0;
    iVar4 = FUN_00411adc(*(undefined4 *)(param_1 + 0x18),&local_18,&local_10);
    if (iVar4 == 0) {
      uVar3 = 0;
    }
    else {
      puVar5 = (uint *)FUN_00411c64(param_1,param_2,local_c);
      if (puVar5 == (uint *)0x0) {
        uVar3 = 0;
      }
      else {
        local_8 = malloc(local_10);
        if (local_8 == 0) {
          uVar3 = 0;
        }
        else {
          memcpy(local_8,iVar4,local_10);
          puVar7 = puVar5 + 1;
          for (uVar2 = 0; uVar2 < *puVar5; uVar2 = uVar2 + 8) {
            uVar1 = *puVar7;
            puVar7 = (uint *)((int)puVar7 + 1);
            uVar6 = 0;
            do {
              if (((1 << (7U - (char)uVar6 & 0x1f) & (uint)(byte)uVar1) != 0) &&
                 (uVar6 + uVar2 < *puVar5)) {
                *(byte *)(local_8 + uVar6 + uVar2) = (byte)*puVar7;
                puVar7 = (uint *)((int)puVar7 + 1);
              }
              uVar6 = uVar6 + 1;
            } while (uVar6 < 8);
          }
          local_14 = puVar5;
          uVar3 = FUN_00411808(param_1,local_8);
          free(local_8);
        }
      }
    }
  }
  return uVar3;
}

