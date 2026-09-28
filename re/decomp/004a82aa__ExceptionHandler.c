// _ExceptionHandler @ 004a82aa size=407 sig=undefined _ExceptionHandler() cc=unknown
// callers: 
// callees: FUN_004a71aa,@__unlockDebuggerData$qv,@__lockDebuggerData$qv,FUN_004a7502,FUN_004010f9,__assertfail,Local_unwind
// strings: \"bogus context in _ExceptionHandler()\"|\"XX.CPP\"|\"!\\\"bogus context in _ExceptionHandler()\\\"\"

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* auto-named from string evidence: _ExceptionHandler */

undefined4 _ExceptionHandler(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int unaff_EBP;
  undefined2 in_FS;
  
  *(undefined4 *)(unaff_EBP + -4) = *(undefined4 *)(unaff_EBP + 8);
  *(undefined4 *)(unaff_EBP + -8) = *(undefined4 *)(unaff_EBP + 0xc);
  *(undefined4 *)(unaff_EBP + -0xc) = *(undefined4 *)(unaff_EBP + 0x10);
  *(undefined4 *)(unaff_EBP + -0x10) = *(undefined4 *)(*(int *)(unaff_EBP + -4) + 0x1c);
  piVar5 = *(int **)(*(int *)(unaff_EBP + -8) + 8);
  *(int *)(unaff_EBP + -0x18) = *(int *)(unaff_EBP + -8) - piVar5[1];
  *(undefined4 *)(unaff_EBP + -0x1c) = *(undefined4 *)(*(int *)(unaff_EBP + -8) + 0xc);
  if ((*(byte *)(*(int *)(unaff_EBP + -4) + 4) & 6) == 0) {
    if ((**(int **)(unaff_EBP + -4) != 0xeefface) &&
       (iVar1 = FUN_004010f9(), **(int **)(iVar1 + 0xc) != 0)) {
      ___lockDebuggerData_qv();
      iVar1 = FUN_004010f9();
      *(undefined4 *)(*(int *)(iVar1 + 0x10) + 0x14) = 0xc;
      iVar1 = FUN_004010f9();
      *(undefined4 *)(*(int *)(iVar1 + 0x10) + 0x18) = 0;
      iVar1 = FUN_004010f9();
      *(undefined4 *)(*(int *)(iVar1 + 0x10) + 0x20) = *(undefined4 *)(unaff_EBP + 0xc);
      iVar1 = FUN_004010f9();
      *(undefined4 *)(*(int *)(iVar1 + 0x10) + 0x34) = **(undefined4 **)(unaff_EBP + -4);
      iVar1 = FUN_004010f9();
      (**(code **)(*(int *)(iVar1 + 0x10) + 0xc))();
      ___unlockDebuggerData_qv();
    }
    uVar6 = (uint)*(ushort *)(*(int *)(unaff_EBP + -8) + 0x10);
    while (uVar6 != 0) {
      *(uint *)(unaff_EBP + -0x14) = (uint)*(ushort *)((int)piVar5 + uVar6);
      *(uint *)(unaff_EBP + -0x20) = (uint)*(ushort *)((int)piVar5 + uVar6 + 2);
      iVar1 = uVar6 + 4;
      switch(*(undefined4 *)(unaff_EBP + -0x20)) {
      case 0:
      case 4:
      case 5:
        break;
      case 1:
        if (**(int **)(unaff_EBP + -4) != 0xeefface) {
          *(undefined4 *)(unaff_EBP + -0x34) = *(undefined4 *)(unaff_EBP + -4);
          *(undefined4 *)(unaff_EBP + -0x30) = *(undefined4 *)(unaff_EBP + -0xc);
          *(undefined4 *)(*(int *)(unaff_EBP + -8) + 0x14) = **(undefined4 **)(unaff_EBP + -4);
          *(int *)(*(int *)(unaff_EBP + -8) + 0x18) = unaff_EBP + -0x34;
          uRam0069f3b0 = *(undefined4 *)((int)piVar5 + iVar1);
          iVar4 = FUN_004a747b();
code_r0x004a85f5:
          if (iVar4 < 0) {
            if ((*(byte *)(*(int *)(unaff_EBP + -4) + 4) & 1) != 0) {
              *(undefined2 *)(*(int *)(unaff_EBP + -8) + 0x10) = *(undefined2 *)(unaff_EBP + -0x14);
            }
            return 0;
          }
          if (iVar4 != 0) {
            *(undefined4 *)(*(int *)(unaff_EBP + -8) + 0x18) = 0;
            uVar6 = *(uint *)(unaff_EBP + -0x14);
            *(uint *)(unaff_EBP + -0x2c) = uVar6;
            iVar4 = FUN_004010f9();
            if (**(int **)(iVar4 + 0xc) != 0) {
              ___lockDebuggerData_qv();
              iVar4 = FUN_004010f9();
              *(undefined4 *)(*(int *)(iVar4 + 0x10) + 0x14) = 0xd;
              iVar4 = FUN_004010f9();
              *(undefined4 *)(*(int *)(iVar4 + 0x10) + 0x18) = 0;
              iVar4 = FUN_004010f9();
              *(undefined4 *)(*(int *)(iVar4 + 0x10) + 0x20) = *(undefined4 *)(unaff_EBP + 0xc);
              iVar4 = FUN_004010f9();
              *(undefined4 *)(*(int *)(iVar4 + 0x10) + 0x34) = **(undefined4 **)(unaff_EBP + -4);
              iVar4 = FUN_004010f9();
              (**(code **)(*(int *)(iVar4 + 0x10) + 0xc))();
              ___unlockDebuggerData_qv();
            }
            uVar2 = *(undefined4 *)((int)piVar5 + iVar1 + 4);
code_r0x004a8493:
            FUN_004a7be0(*(undefined4 *)(unaff_EBP + -8),*(undefined4 *)(unaff_EBP + -4));
            Local_unwind(*(undefined4 *)(unaff_EBP + -8),uVar6);
            *(undefined2 *)(*(int *)(unaff_EBP + -8) + 0x10) = *(undefined2 *)(unaff_EBP + -0x2c);
            if (*(int *)(unaff_EBP + -0x20) == 3) {
              FUN_004a7df4(*(undefined4 *)(unaff_EBP + -0x24),*(undefined4 *)(unaff_EBP + -8),
                           *(undefined4 *)(unaff_EBP + -0x10),*(undefined4 *)(unaff_EBP + -0x28),
                           *(undefined4 *)(unaff_EBP + -0x18));
            }
            iVar1 = FUN_004010f9();
            if (**(int **)(iVar1 + 0xc) != 0) {
              ___lockDebuggerData_qv();
              iVar1 = FUN_004010f9();
              *(undefined4 *)(*(int *)(iVar1 + 0x10) + 0x14) = 2;
              iVar1 = FUN_004010f9();
              *(undefined4 *)(*(int *)(iVar1 + 0x10) + 0x18) = uVar2;
              uVar2 = FUN_004a90cc(*(undefined4 *)(*(int *)(unaff_EBP + -0x10) + 4));
              iVar1 = FUN_004010f9();
              *(undefined4 *)(*(int *)(iVar1 + 0x10) + 0x28) = uVar2;
              iVar1 = FUN_004010f9();
              if (*(char *)(*(int *)(unaff_EBP + -0x10) + 0x44) == '\0') {
                iVar4 = *(int *)(*(int *)(unaff_EBP + -0x10) + 0x40);
              }
              else {
                iVar4 = *(int *)(unaff_EBP + -0x10) + 0x46;
              }
              *(int *)(*(int *)(iVar1 + 0x10) + 0x1c) = iVar4;
              iVar1 = FUN_004010f9();
              (**(code **)(*(int *)(iVar1 + 0x10) + 0xc))();
              ___unlockDebuggerData_qv();
            }
            func_0x004a7484();
          }
        }
        break;
      case 2:
        if (**(int **)(unaff_EBP + -4) != 0xeefface) {
          *(undefined4 *)(*(int *)(unaff_EBP + -8) + 0x14) = **(undefined4 **)(unaff_EBP + -4);
          iVar4 = *(int *)((int)piVar5 + iVar1);
          goto code_r0x004a85f5;
        }
        break;
      case 3:
        if (**(int **)(unaff_EBP + -4) == 0xeefface) {
          *(undefined4 *)(unaff_EBP + -0x28) = *(undefined4 *)((int)piVar5 + iVar1);
          uVar2 = FUN_004a8257(*(undefined4 *)(unaff_EBP + -0x28),*(undefined4 *)(unaff_EBP + -0x10)
                              );
          *(undefined4 *)(unaff_EBP + -0x24) = uVar2;
          if (*(int *)(unaff_EBP + -0x24) != 0) {
            puVar3 = (undefined4 *)FUN_004010f9();
            **(undefined4 **)(unaff_EBP + -0x10) = *puVar3;
            puVar3 = (undefined4 *)FUN_004010f9();
            *puVar3 = *(undefined4 *)(unaff_EBP + -0x10);
            *(undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x28) = *(undefined4 *)(unaff_EBP + -8);
            *(undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0x2c) = *(undefined4 *)(unaff_EBP + -0x24)
            ;
            *(uint *)(*(int *)(unaff_EBP + -0x10) + 0x30) = uVar6 + 8;
            *(uint *)(unaff_EBP + -0x2c) = uVar6 + 8;
            uVar2 = **(undefined4 **)(unaff_EBP + -0x24);
            goto code_r0x004a8493;
          }
        }
        break;
      default:
        __assertfail(s___bogus_context_in__ExceptionHan_0051f57c,s_XX_CPP_0051f5a4,0xb78);
      }
      uVar6 = *(uint *)(unaff_EBP + -0x14);
    }
  }
  else {
    Local_unwind(*(undefined4 *)(unaff_EBP + -8),0);
    if ((**(int **)(unaff_EBP + -4) == 0xeefface) && (piVar5 = (int *)*piVar5, piVar5 != (int *)0x0)
       ) {
      for (; *piVar5 != 0; piVar5 = piVar5 + 1) {
        iVar1 = FUN_004a7502(*(undefined4 *)(*(int *)(unaff_EBP + -0x10) + 4),
                             *(undefined4 *)(*(int *)(unaff_EBP + -0x10) + 8),*piVar5,
                             *(undefined4 *)(*(int *)(unaff_EBP + -0x10) + 0xc),1);
        if (iVar1 != 0) {
          return 1;
        }
      }
      puVar3 = (undefined4 *)segment(in_FS,0);
      uVar2 = *puVar3;
      puVar3 = (undefined4 *)segment(in_FS,0);
      *puVar3 = **(undefined4 **)(unaff_EBP + -8);
      FUN_004a71aa();
      puVar3 = (undefined4 *)segment(in_FS,0);
      *puVar3 = uVar2;
    }
  }
  return 1;
}

