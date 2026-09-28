// Rectangle @ 004b42b7 size=6 sig=BOOL Rectangle(HDC hdc, int left, int top, int right, int bottom) cc=__stdcall
// callers: FUN_00464cbc,FUN_00465164
// callees: 

BOOL Rectangle(HDC hdc,int left,int top,int right,int bottom)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b42b7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = Rectangle(hdc,left,top,right,bottom);
  return BVar1;
}

