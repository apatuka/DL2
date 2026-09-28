// FUN_0045cff4 @ 0045cff4 size=917 sig=undefined FUN_0045cff4() cc=unknown
// callers: FUN_0044ae10
// callees: FUN_00459230,FUN_0043edd8,FUN_00459ea8,FUN_004590f0,FUN_0045bf78

void FUN_0045cff4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  if (DAT_004d5ad0 == 0) {
    FUN_00459ea8(param_3,param_4,&local_8,&local_c);
  }
  else {
    FUN_0043edd8(param_3,param_4,&local_8,&local_c);
  }
  if ((((-1 < local_8) && (local_8 < DAT_004d5b1a)) && (-1 < local_c)) && (local_c < DAT_004d5b1b))
  {
    uVar2 = FUN_0045bf78(local_8,local_c,param_3,param_4,0);
    if ((uVar2 == 0xffffffff) || (uVar2 != DAT_00583d90)) {
      if (DAT_00583d64 != 0) {
        DAT_00583d64 = 0;
      }
    }
    else if ((int)DAT_004d5b18 < (int)uVar2) {
      if ((DAT_004d59b0 == 0) ||
         ((&DAT_005a4436)
          [DAT_0058f1f4 + (short)(&DAT_005a0552)[local_c * 200 + local_8 * 5] * 0xadc] != '\x04')) {
        if ((999 < (int)uVar2) && ((int)uVar2 < 9000)) {
          switch(uVar2) {
          case 1000:
            local_10 = 1;
            DAT_00583d7c = 0;
            break;
          case 0x3e9:
            if ((&DAT_005a43f1)[(short)(&DAT_005a0552)[local_c * 200 + local_8 * 5] * 0xadc] == '\0'
               ) {
              local_10 = 6;
            }
            else {
              local_10 = 0;
            }
            DAT_00583d7c = 1;
            break;
          case 0x3ea:
            local_10 = 2;
            DAT_00583d7c = 2;
            break;
          case 0x3eb:
            if ((&DAT_005a43f1)[(short)(&DAT_005a0552)[local_c * 200 + local_8 * 5] * 0xadc] == '\0'
               ) {
              local_10 = 3;
            }
            else {
              local_10 = 4;
            }
            DAT_00583d7c = 3;
            break;
          case 0x3ec:
            local_10 = 5;
            DAT_00583d7c = 4;
            break;
          case 0x3ed:
            local_10 = 7;
            DAT_00583d7c = 1;
          }
          DAT_00583d80 = (int)(short)(&DAT_005a43ea)
                                     [(short)(&DAT_005a0552)[local_c * 200 + local_8 * 5] * 0x56e];
          FUN_00459230(DAT_004d5974,0x31304955,(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] + 1000,
                       local_10,param_1,param_2,0x10,0x10,0,FUN_0045ccf8);
        }
      }
      else {
        DAT_00583d74 = (&DAT_004c5ab8)[(uVar2 & 0xff) * 4];
        iVar3 = (&DAT_004c5abc)[(uVar2 & 0xff) * 4] * 0x10;
        DAT_00583d78 = (int)(short)(&DAT_005a0552)[local_c * 200 + local_8 * 5];
        FUN_004590f0(DAT_004d5974,*(undefined4 *)(&DAT_004e2b34 + iVar3),param_1,param_2,
                     (int)*(short *)(&DAT_004e2b30 + iVar3),(int)*(short *)(&DAT_004e2b32 + iVar3),0
                     ,FUN_0045ca3c);
      }
    }
    else {
      puVar1 = (&PTR_DAT_004d078c)
               [(char)(&DAT_0059f162)[(char)(&DAT_005a43f0)[uVar2 * 0xadc] * 0x2d8] * 3];
      DAT_00583d70 = uVar2;
      FUN_004590f0(DAT_004d5974,*(undefined4 *)(puVar1 + 8),param_1,param_2,
                   (int)*(short *)(puVar1 + 4),(int)*(short *)(puVar1 + 6),0,FUN_0045c704);
    }
  }
  return;
}

