// FUN_004234d4 @ 004234d4 size=444 sig=undefined FUN_004234d4() cc=unknown
// callers: FUN_004600d0,FUN_00423690
// callees: FUN_004412d4,FUN_0042278c,DebugMessage,FUN_004a6b48,FUN_004233e0,FUN_004503f4
// strings: \"Not enough memory to log event.\"

int FUN_004234d4(undefined4 param_1,int param_2,int param_3)

{
  short sVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int local_c;
  
  iVar3 = FUN_0042278c(param_2);
  sVar1 = *(short *)(&DAT_004fc90c + iVar3 * 0x12);
  param_3 = param_3 + 1;
  do {
    puVar2 = PTR_DAT_004b7b54;
    if (PTR_DAT_004b7b54 + param_3 < &DAT_0053c4db) {
      (&DAT_00651cb8)[DAT_0065209c * 5] = PTR_DAT_004b7b54;
      PTR_DAT_004b7b54 = PTR_DAT_004b7b54 + param_3;
      FUN_004a6b48(puVar2,param_1,param_3);
      *(undefined1 *)((&DAT_00651cb8)[DAT_0065209c * 5] + -1 + param_3) = 0;
      (&DAT_00651cb4)[DAT_0065209c * 5] = param_2;
      iVar3 = FUN_0042278c(param_2);
      if (*(short *)(&DAT_004fc918 + iVar3 * 0x12) < 0) {
        *(undefined4 *)(&DAT_00651cbc + DAT_0065209c * 0x14) = 0;
      }
      else {
        uVar5 = 0xffffffff;
        if (*(short *)(&DAT_004fc918 + iVar3 * 0x12) == 7) {
          iVar8 = 0;
          iVar7 = 0;
          local_c = 0;
          piVar6 = &DAT_0065e3cc;
          do {
            if ((iVar7 == DAT_0058f1f4) ||
               (iVar4 = FUN_004412d4(DAT_0058f1f4,iVar7,0x10), iVar4 != 0)) {
              if (local_c < *piVar6) {
                local_c = *piVar6;
              }
            }
            else if (iVar8 < *piVar6) {
              iVar8 = *piVar6;
            }
            iVar7 = iVar7 + 1;
            piVar6 = piVar6 + 1;
          } while (iVar7 < 7);
          if (iVar8 < local_c) {
            uVar5 = 0;
          }
          else if (iVar8 == local_c) {
            uVar5 = 1;
          }
          else if ((param_2 == 0x43) || (param_2 == 0x42)) {
            uVar5 = 3;
          }
          else {
            uVar5 = 2;
          }
        }
        uVar5 = FUN_004503f4((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],
                             (int)*(short *)(&DAT_004fc918 + iVar3 * 0x12),uVar5);
        *(undefined4 *)(&DAT_00651cbc + DAT_0065209c * 0x14) = uVar5;
      }
      iVar3 = DAT_0065209c;
      DAT_0065209c = DAT_0065209c + 1;
      return iVar3;
    }
    iVar3 = FUN_004233e0((int)sVar1);
  } while (iVar3 != 0);
  DebugMessage(s_Not_enough_memory_to_log_event__004b7bdf);
  return -1;
}

