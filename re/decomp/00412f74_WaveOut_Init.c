// WaveOut_Init @ 00412f74 size=627 sig=undefined WaveOut_Init() cc=unknown
// callers: FUN_00412cd4
// callees: waveOutReset,FUN_004ae034,waveOutOpen,waveOutPrepareHeader,FUN_004ae068,waveOutPause,malloc,FUN_0041244c,waveOutWrite,FUN_00482a38,waveOutClose

/* WARNING: Removing unreachable block (ram,0x004130d2) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Opens waveOut device and prepares headers */

undefined4 WaveOut_Init(int *param_1)

{
  LPCWAVEFORMATEX pwfx;
  float fVar1;
  undefined4 uVar2;
  LPCWAVEFORMATEX pWVar3;
  MMRESULT MVar4;
  int iVar5;
  undefined1 *puVar6;
  LPWAVEHDR pwVar7;
  DWORD_PTR DVar8;
  DWORD local_20;
  LPCWAVEFORMATEX local_1c;
  int local_8;
  
  if (*param_1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    if (*(HWAVEOUT *)((int)param_1 + 0x1a) != (HWAVEOUT)0x0) {
      waveOutClose(*(HWAVEOUT *)((int)param_1 + 0x1a));
    }
    if (*(int *)((int)param_1 + 0x52) == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      if (*(int *)((int)param_1 + 0x16) == 0) {
        uVar2 = FUN_0041244c(*(int *)((int)param_1 + 0x52),*(undefined4 *)((int)param_1 + 0x56),
                             &local_8);
        *(undefined4 *)((int)param_1 + 0x16) = uVar2;
        local_8 = local_8 + -0x12;
        if (*(int *)((int)param_1 + 0x16) == 0) {
          return 0xfffffffe;
        }
      }
      pwfx = *(LPCWAVEFORMATEX *)((int)param_1 + 0x16);
      pWVar3 = pwfx + 1;
      FUN_00482a38();
      MVar4 = waveOutOpen((LPHWAVEOUT)((int)param_1 + 0x1a),0xffffffff,pwfx,0x413250,
                          (DWORD_PTR)param_1,0x30000);
      if (MVar4 == 0) {
        waveOutPause(*(HWAVEOUT *)((int)param_1 + 0x1a));
        fVar1 = (float)_DAT_004b6fe0;
        iVar5 = malloc((*(int *)((int)param_1 + 10) + 1) * 0x20);
        param_1[0xe] = iVar5;
        if (iVar5 == 0) {
          waveOutReset(*(HWAVEOUT *)((int)param_1 + 0x1a));
          waveOutClose(*(HWAVEOUT *)((int)param_1 + 0x1a));
          uVar2 = 0xfffffffc;
        }
        else {
          local_1c = pWVar3;
          for (DVar8 = 0; (int)DVar8 < *(int *)((int)param_1 + 10); DVar8 = DVar8 + 1) {
            pwVar7 = (LPWAVEHDR)(DVar8 * 0x20 + param_1[0xe]);
            FUN_004ae034((double)((1.0 / fVar1) * 1000.0));
            FUN_004ae068();
            iVar5 = FUN_004ae068();
            local_20 = iVar5 * ((int)(uint)pwfx->wBitsPerSample >> 3);
            puVar6 = (undefined1 *)((int)&pWVar3->wFormatTag + local_8);
            if (puVar6 <= (WORD *)((int)&local_1c->wFormatTag + local_20)) {
              local_20 = (int)puVar6 - (int)local_1c;
            }
            pwVar7->lpData = (LPSTR)local_1c;
            pwVar7->dwBufferLength = local_20;
            pwVar7->dwFlags = 0;
            pwVar7->dwUser = DVar8;
            param_1[0xc] = DVar8;
            MVar4 = waveOutPrepareHeader(*(HWAVEOUT *)((int)param_1 + 0x1a),pwVar7,0x20);
            if (MVar4 != 0) {
              waveOutClose(*(HWAVEOUT *)((int)param_1 + 0x1a));
              return 0xffffffff;
            }
            MVar4 = waveOutWrite(*(HWAVEOUT *)((int)param_1 + 0x1a),pwVar7,0x20);
            if (MVar4 != 0) {
              waveOutClose(*(HWAVEOUT *)((int)param_1 + 0x1a));
              return 0xffffffff;
            }
            local_1c = (LPCWAVEFORMATEX)((int)&local_1c->wFormatTag + local_20);
          }
          if (local_1c < (LPCWAVEFORMATEX)((int)&pWVar3->wFormatTag + local_8)) {
            pwVar7 = (LPWAVEHDR)(*(int *)((int)param_1 + 10) * 0x20 + param_1[0xe]);
            pwVar7->lpData = (LPSTR)local_1c;
            pwVar7->dwBufferLength = (int)pWVar3 + (local_8 - (int)local_1c);
            pwVar7->dwFlags = 0;
            param_1[0xc] = param_1[0xc] + 1;
            pwVar7->dwUser = param_1[0xc];
            MVar4 = waveOutPrepareHeader(*(HWAVEOUT *)((int)param_1 + 0x1a),pwVar7,0x20);
            if (MVar4 != 0) {
              waveOutClose(*(HWAVEOUT *)((int)param_1 + 0x1a));
              return 0xffffffff;
            }
            MVar4 = waveOutWrite(*(HWAVEOUT *)((int)param_1 + 0x1a),pwVar7,0x20);
            if (MVar4 != 0) {
              waveOutClose(*(HWAVEOUT *)((int)param_1 + 0x1a));
              return 0xffffffff;
            }
          }
          uVar2 = 0;
        }
      }
      else {
        uVar2 = 0xffffffff;
      }
    }
  }
  return uVar2;
}

