// Local_unwind @ 004a80bd size=358 sig=undefined Local_unwind() cc=unknown
// callers: FUN_004a8228,_ExceptionHandler,FUN_004a823b
// callees: FUN_004a8c58,FUN_004a7c94,FUN_004010f9,FUN_004a747b,__assertfail
// strings: \"XX.CPP\"|\"xdrPtr && xdrPtr == *xdrLPP\"|\"bogus context in Local_unwind()\"|\"!\\\"bogus context in Local_unwind()\\\"\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* auto-named from string evidence: Local_unwind */

void Local_unwind(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  undefined1 *puVar4;
  undefined4 *unaff_ESI;
  uint uVar5;
  
  puVar4 = &stack0xfffffffc;
  uVar5 = (uint)*(ushort *)(param_1 + 0x10);
  while ((uVar3 = uVar5, uVar3 != 0 && (uVar3 != *(uint *)(puVar4 + 0xc)))) {
    uVar5 = (uint)*(ushort *)(*(int *)(puVar4 + -4) + uVar3);
    uVar2 = (uint)*(ushort *)(*(int *)(puVar4 + -4) + uVar3 + 2);
    *(ushort *)(*(int *)(puVar4 + 8) + 0x10) = *(ushort *)(*(int *)(puVar4 + -4) + uVar3);
    if (uVar2 == 0) {
      _DAT_0069f3ac = *(undefined4 *)(*(int *)(puVar4 + -4) + 4 + uVar3 + 4);
      *(undefined2 *)(*(int *)(puVar4 + 8) + 0x12) = 1;
      FUN_004a747b(uVar5,unaff_ESI,puVar4,uVar3);
      *(undefined2 *)(*(int *)(puVar4 + 8) + 0x12) = 0;
    }
    else if (2 < uVar2 - 1) {
      if (uVar2 == 4) {
        uVar1 = FUN_004010f9();
        *(undefined4 *)(puVar4 + -0x10) = uVar1;
        while ((unaff_ESI = (undefined4 *)**(int **)(puVar4 + -0x10), unaff_ESI != (undefined4 *)0x0
               && ((unaff_ESI[10] != *(int *)(puVar4 + 8) || (uVar3 != unaff_ESI[0xc]))))) {
          *(undefined4 **)(puVar4 + -0x10) = unaff_ESI;
        }
        if ((unaff_ESI == (undefined4 *)0x0) ||
           (unaff_ESI != (undefined4 *)**(int **)(puVar4 + -0x10))) {
          __assertfail(s_xdrPtr____xdrPtr_____xdrLPP_0051f4ea,s_XX_CPP_0051f506,0x84f);
        }
        **(undefined4 **)(puVar4 + -0x10) = *unaff_ESI;
        FUN_004a7c94(unaff_ESI);
        (*(code *)unaff_ESI[7])(unaff_ESI);
      }
      else if (uVar2 - 1 == 4) {
        uVar1 = FUN_004a8c58(*(undefined4 *)(*(int *)(puVar4 + -4) + uVar3 + 8),
                             *(int *)(*(int *)(puVar4 + -4) + uVar3 + 4) + *(int *)(puVar4 + -0xc),
                             *(undefined4 *)(puVar4 + 8),*(undefined4 *)(puVar4 + -8));
        *(undefined4 *)(puVar4 + -0xc) = uVar1;
      }
      else {
        __assertfail(s___bogus_context_in_Local_unwind__0051f52d,s_XX_CPP_0051f550,0x87e);
      }
    }
  }
  return;
}

