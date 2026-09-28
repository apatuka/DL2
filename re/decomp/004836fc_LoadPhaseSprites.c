// LoadPhaseSprites @ 004836fc size=221 sig=undefined LoadPhaseSprites() cc=unknown
// callers: FUN_004658a8,LoadCombatSprites,FUN_004837dc,FUN_00465ac8
// callees: FUN_0048307c,FUN_004418ec,FUN_004419c8,HeapValidate,FUN_00483224,LoadPhaseSpriteFile,FUN_00483538,FUN_0048e5f8,GetProcessHeap
// strings: \"Invalid Heap in Load Phase Sprites\"|\"Phase Sprite\"

/* Loads the sprite set of a game phase (Settlement/Control/Combat) */

undefined4 LoadPhaseSprites(uint *param_1,int param_2)

{
  int iVar1;
  HANDLE hHeap;
  BOOL BVar2;
  undefined4 uVar3;
  uint *puVar4;
  int iVar5;
  DWORD dwFlags;
  LPCVOID lpMem;
  int local_8;
  
  do {
    local_8 = 0;
    iVar5 = 0;
    puVar4 = param_1;
    if (0 < param_2) {
      do {
        if ((*(uint *)(&DAT_00657e60 + (*puVar4 & 0xfffffffc)) & 1 << ((byte)*puVar4 & 3)) == 0) {
          iVar1 = FUN_0048307c(*puVar4);
          local_8 = local_8 + iVar1;
        }
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
      } while (iVar5 < param_2);
    }
    if (local_8 == 0) {
      return 1;
    }
    lpMem = (LPCVOID)0x0;
    dwFlags = 0;
    hHeap = GetProcessHeap();
    BVar2 = HeapValidate(hHeap,dwFlags,lpMem);
    if (BVar2 == 0) {
      FUN_0048e5f8(s_Invalid_Heap_in_Load_Phase_Sprit_004dcf7b);
    }
    iVar5 = FUN_004418ec(s_Phase_Sprite_004dcf9e,param_2 * 4 + local_8);
    if (iVar5 != 0) {
      iVar1 = FUN_00483224(iVar5,local_8 + iVar5,param_1,param_2);
      if (iVar1 != 0) {
        return 1;
      }
      FUN_004419c8(iVar5);
    }
    iVar5 = FUN_00483538(1);
  } while (iVar5 != 0);
  uVar3 = LoadPhaseSpriteFile(param_1,param_2,local_8);
  return uVar3;
}

