// FUN_00483224 @ 00483224 size=284 sig=undefined FUN_00483224() cc=unknown
// callers: LoadPhaseSprites
// callees: FUN_00483098,FUN_00482fc8,FUN_004831ac,CreateFileA,CloseHandle
// strings: \"SPRITENW.DAT\"

undefined4 FUN_00483224(int param_1,uint *param_2,uint *param_3,int param_4)

{
  HANDLE hObject;
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *local_18;
  int local_c;
  
  hObject = CreateFileA(s_SPRITENW_DAT_004dcf5c,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,
                        (HANDLE)0xffffffff);
  if (hObject == (HANDLE)0xffffffff) {
    uVar1 = 0;
  }
  else {
    iVar4 = 0;
    local_c = param_1;
    iVar3 = 0;
    local_18 = param_2;
    if (0 < param_4) {
      do {
        if ((*(uint *)(&DAT_00657e60 + (*param_3 & 0xfffffffc)) & 1 << ((byte)*param_3 & 3)) == 0) {
          iVar2 = FUN_00483098(hObject,(&PTR_DAT_004d02f4)[*param_3 * 3],local_c);
          local_c = local_c + iVar2;
          if (local_c == 0) goto LAB_00483311;
          iVar4 = iVar4 + 1;
          *local_18 = *param_3;
          local_18 = local_18 + 1;
          *(uint *)(&DAT_00657e60 + (*param_3 & 0xfffffffc)) =
               *(uint *)(&DAT_00657e60 + (*param_3 & 0xfffffffc)) | 1 << ((byte)*param_3 & 3);
        }
        iVar3 = iVar3 + 1;
        param_3 = param_3 + 1;
      } while (iVar3 < param_4);
    }
    CloseHandle(hObject);
    iVar3 = FUN_004831ac(param_1,param_2,iVar4);
    if (iVar3 == 0) {
LAB_00483311:
      CloseHandle(hObject);
      iVar3 = 0;
      if (0 < iVar4) {
        do {
          FUN_00482fc8(*param_2);
          iVar3 = iVar3 + 1;
          param_2 = param_2 + 1;
        } while (iVar3 < iVar4);
      }
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

