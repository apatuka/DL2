// SelectObject @ 004b42ab size=6 sig=HGDIOBJ SelectObject(HDC hdc, HGDIOBJ h) cc=__stdcall
// callers: FUN_0046534c,FUN_00464a3c,FUN_00464cbc,FUN_004652f8,FUN_00464f80,FUN_00457bec,FUN_00465164,FUN_0048d391,FUN_0048d5c4,FUN_0048bdb0,FUN_00472f64,FUN_004652a8
// callees: 

HGDIOBJ SelectObject(HDC hdc,HGDIOBJ h)

{
  HGDIOBJ pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b42ab. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = SelectObject(hdc,h);
  return pvVar1;
}

