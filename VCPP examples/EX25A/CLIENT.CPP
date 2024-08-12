// client.cpp  pseudo-OLE QuickWin application
#include <afx.h>
#include "ship.h"


//----------Main Program--------------------------------------------
int main() // simulates OLE client program
{
    printf("Entering client main\n");
    IUnknown*      pUnk;  // If you declare these void*,
                          //  you lose type-safety.
    IMotion*       pMot;
    IVisual*       pVis;
    IClassFactory* pClf; 
    
    GetClassObject(CLSID_CSpaceship, IID_IClassFactory,
                  (void**) &pClf); 

    pClf->CreateInstance(IID_IUnknown, (void**) &pUnk);
    pUnk->QueryInterface(IID_IMotion,  (void**) &pMot);
    pMot->QueryInterface(IID_IVisual,  (void**) &pVis);
    // All three pointers should work.
    printf("main: pUnk = %p, pMot = %p, pDis = %p\n",
            pUnk, pMot, pVis);
    
    // Test all the interface virtual functions.
    pMot->Fly();
    int nPos = pMot->GetPosition();
    pVis->Display();

    pClf->Release();

    pUnk->Release();
    pMot->Release();
    pVis->Release();
    return 0;
}
