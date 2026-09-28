// FUN_004a7df4 @ 004a7df4 size=713 sig=undefined FUN_004a7df4() cc=unknown
// callers: 
// callees: memset,FUN_004a7c1f,FUN_004a9103,FUN_004a99f8,FUN_004a75c4,memcpy,__assertfail
// strings: \"XX.CPP\"|\"dscPtr->xdERRaddr == errPtr\"|\"dscPtr->xdHtabAdr == hdtPtr\"|\"dscPtr->xdArgCopy == 0\"|\"(dscPtr->xdMask & TM_IS_PTR) == 0\"|\"mask & TM_IS_PTR\"|\"dscPtr->xdMask & TM_IS_PTR\"|\"dscPtr->xdTypeID == dscPtr->xdBase\"|\"hdtPtr->HDcctrAddr\"|\"dscPtr->xdSize == size\"

void FUN_004a7df4(int param_1,int param_2,int param_3,int *param_4,int param_5)

{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  int *piVar6;
  bool bVar7;
  int *local_8;
  
  if (*(int *)(param_3 + 0x28) != param_2) {
    __assertfail(s_dscPtr_>xdERRaddr____errPtr_0051f3c1,s_XX_CPP_0051f3dd,0x6b7);
  }
  if (*(int *)(param_3 + 0x2c) != param_1) {
    __assertfail(s_dscPtr_>xdHtabAdr____hdtPtr_0051f3e4,s_XX_CPP_0051f400,0x6b8);
  }
  if (*(char *)(param_3 + 0x45) != '\0') {
    __assertfail(s_dscPtr_>xdArgCopy____0_0051f407,s_XX_CPP_0051f41e,0x6ba);
  }
  piVar6 = *(int **)(param_1 + 4);
  *(int **)(param_3 + 0x3c) = piVar6;
  if ((piVar6 != (int *)0x0) && ((*(byte *)(param_1 + 8) & 0x80) == 0)) {
    bVar7 = (*(byte *)(param_1 + 8) & 1) == 0;
    local_8 = (int *)(param_3 + 0x46);
    *(undefined1 *)(param_3 + 0x45) = 1;
    *(int *)(param_3 + 0x40) = *param_4 + param_5;
    uVar1 = *(ushort *)(piVar6 + 1);
    iVar2 = *piVar6;
    uVar5 = uVar1;
    if ((uVar1 & 0x30) != 0) {
      piVar6 = (int *)piVar6[2];
      uVar5 = *(ushort *)(piVar6 + 1);
    }
    if (((uVar1 & 0x10) == 0) || ((*(byte *)(param_3 + 0xc) & 1) == 0)) {
      if (((uVar5 & 1) == 0) || ((uVar1 & 0x30) == 0)) {
        if ((*(byte *)(param_3 + 0x18) & 1) == 0) {
          if ((uVar1 & 0x20) == 0) {
            if (iVar2 != *(int *)(param_3 + 0x10)) {
              __assertfail(s_dscPtr_>xdSize____size_0051f4cc,s_XX_CPP_0051f4e3,0x78d);
            }
            memcpy(*(undefined4 *)(param_3 + 0x40),local_8,iVar2);
          }
          else {
            memcpy(*(undefined4 *)(param_3 + 0x40),&local_8,iVar2);
            bVar7 = true;
          }
        }
        else {
          if (*(int *)(param_3 + 4) != *(int *)(param_3 + 0x14)) {
            __assertfail(s_dscPtr_>xdTypeID____dscPtr_>xdBa_0051f488,s_XX_CPP_0051f4ab,0x74b);
          }
          iVar4 = FUN_004a9103(*(undefined4 *)(param_3 + 0x14),piVar6);
          if (iVar4 == 0) {
            local_8 = (int *)FUN_004a99f8(local_8,*(undefined4 *)(param_3 + 0x14),piVar6);
          }
          bVar7 = iVar4 == 0 || bVar7;
          if ((*(byte *)(piVar6 + 3) & 1) == 0) {
            memcpy(*(undefined4 *)(param_3 + 0x40),local_8,iVar2);
          }
          else {
            if (*(int *)(param_1 + 0xc) == 0) {
              __assertfail(s_hdtPtr_>HDcctrAddr_0051f4b2,s_XX_CPP_0051f4c5,0x765);
            }
            FUN_004a75c4(*(undefined4 *)(param_3 + 0x40),local_8,*(undefined4 *)(param_1 + 0xc),
                         *(undefined4 *)(param_1 + 0x10));
            bVar7 = true;
          }
        }
      }
      else {
        if ((uVar1 & 0x20) == 0) {
          if ((uVar1 & 0x10) == 0) {
            __assertfail(s_mask___TM_IS_PTR_0051f44e,s_XX_CPP_0051f45f,0x72a);
          }
          if ((*(byte *)(param_3 + 0x18) & 0x10) == 0) {
            __assertfail(s_dscPtr_>xdMask___TM_IS_PTR_0051f466,s_XX_CPP_0051f481,0x72b);
          }
          local_8 = (int *)*local_8;
        }
        else {
          if ((*(byte *)(param_3 + 0x18) & 0x10) != 0) {
            __assertfail(s__dscPtr_>xdMask___TM_IS_PTR_____0_0051f425,s_XX_CPP_0051f447,0x717);
          }
          bVar7 = true;
        }
        iVar4 = FUN_004a9103(*(undefined4 *)(param_3 + 0x14),piVar6);
        piVar3 = local_8;
        if (iVar4 == 0) {
          local_8 = (int *)FUN_004a99f8(local_8,*(undefined4 *)(param_3 + 0x14),piVar6);
          if (local_8 != piVar3) {
            bVar7 = true;
          }
        }
        memcpy(*(undefined4 *)(param_3 + 0x40),&local_8,iVar2);
      }
    }
    else {
      memset(*(undefined4 *)(param_3 + 0x40),0,iVar2);
      bVar7 = true;
    }
    if (!bVar7) {
      if ((*(byte *)(piVar6 + 3) & 2) != 0) {
        FUN_004a7c1f(local_8,piVar6,piVar6[10],(short)piVar6[0xb]);
      }
      *(undefined1 *)(param_3 + 0x44) = 0;
    }
  }
  return;
}

