// FUN_0044ba40 @ 0044ba40 size=136 sig=undefined FUN_0044ba40() cc=unknown
// callers: FUN_0041db10,FUN_004021e0,FUN_0041c418,FUN_00448700,FUN_0041c258,FUN_0041bd60,FUN_0044eb4c,FUN_004038c4,FUN_0044c9a0,FUN_00402548,FUN_0040552c,MoveLaborToHousingNoNet,FUN_0040668c,FUN_0044bacc,FUN_00480be0,FUN_0041e0a8,FUN_0044c320,FUN_004068f8,FUN_0044be88,FUN_0041c814,FUN_0040548c,FUN_0045b448,FUN_0044c8ac,FUN_004483d0,FUN_0044eeb4,FUN_0044c2c0,MoveHousingLabor,FUN_0044bea8,FUN_0040f584,FUN_0044b7d8,FUN_0041b71c,FUN_004067d0,FUN_00406538,MoveLaborToHousing,FUN_0041bfc0
// callees: 

int FUN_0044ba40(int param_1)

{
  int iVar1;
  
  if ((param_1 == 0) || (*(char *)(param_1 + 4) == '\0')) {
    iVar1 = 0;
  }
  else if (*(short *)(param_1 + 0x14) == 0) {
    iVar1 = (int)(char)(&DAT_004f9dc4)[*(char *)(param_1 + 4) * 0x32];
    if ((*(char *)(param_1 + 5) == '\x11') &&
       ((char)(&DAT_005a43f0)[*(short *)(param_1 + 8) * 0xadc] != -1)) {
      iVar1 = (*(short *)(&DAT_00559f50 +
                         (char)(&DAT_0059f162)
                               [(char)(&DAT_005a43f0)[*(short *)(param_1 + 8) * 0xadc] * 0x2d8] * 2)
              * iVar1) / 100;
    }
  }
  else {
    iVar1 = 4;
  }
  return iVar1;
}

