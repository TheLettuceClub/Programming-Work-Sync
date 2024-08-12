// ship.cpp  pseudo-OLE QuickWin application
#include <afx.h>
#include "ship.h"

CSpaceshipFactory NEAR factory;

//----------Member Functions----------------------------------------
BOOL CSpaceshipFactory::XClassFactory::QueryInterface(
                      const long& lRid, void** ppvObj)
{
    printf("Entering CSpaceshipFactory::XClassFactory::\
 QueryInterface -- lRid = %d\n", lRid);
    METHOD_PROLOGUE(CSpaceshipFactory,
                    ClassFactory) // makes pThis
    if (lRid == IID_IUnknown || lRid == IID_IClassFactory) {
      *ppvObj = this;
      pThis->InternalAddRef ();   // Client can’t release
                                  //  the factory object.
      return TRUE;
    }
    return FALSE;
}                               

BOOL CSpaceshipFactory::XClassFactory::CreateInstance(
                      const long& lRid, void** ppvObj)
{
    printf("Entering CSpaceshipFactory::XClassFactory::\
 CreateInstance\n");
    METHOD_PROLOGUE(CSpaceshipFactory,
                    ClassFactory) // makes pThis
    ASSERT(lRid == IID_IUnknown);
    CSpaceship* pObj = new CSpaceship();
    if (pObj->InternalQueryInterface(lRid, ppvObj)) {
      pObj->InternalRelease(); // balance reference count
      return TRUE;
    }
    return FALSE;
}

DWORD CSpaceshipFactory::XClassFactory::Release()
{
    printf("Entering CSpaceshipFactory::XClassFactory::Release\n");
    METHOD_PROLOGUE(CSpaceshipFactory,
                    ClassFactory) // makes pThis
    return pThis->InternalRelease();
    // delegate to CSimulatedCmdTarget
}                               

DWORD CSpaceshipFactory::XClassFactory::AddRef ()
{
    printf("Entering CSpaceshipFactory::XClassFactory::AddRef\n");
    METHOD_PROLOGUE(CSpaceshipFactory,
                    ClassFactory) // makes pThis
    return pThis->InternalAddRef ();
    // delegate to CSimulatedCmdTarget
}                               

BOOL CSpaceship::InternalQueryInterface(const long& lRid,
                                        void** ppvObj)
{
    printf("Entering CSpaceship::InternalQueryInterface --\
 lRid = %d\n", lRid);
    switch (lRid) {
    case IID_IUnknown:
    case IID_IMotion:
        *ppvObj = &m_xMotion;     // both IMotion and IVisual are
                                  //  derived from IUnknown, so
                                  //  either pointer will do
        break;
    case IID_IVisual:
        *ppvObj = &m_xVisual;
        break;
    default:
        *ppvObj = NULL;
        return FALSE;
    }
    InternalAddRef ();
    return TRUE;
}                               

BOOL CSpaceship::XMotion::QueryInterface(const long& lRid,
                                         void** ppvObj)
{
    printf("Entering CSpaceship::XMotion::QueryInterface --\
 lRid = %d\n", lRid);
    METHOD_PROLOGUE(CSpaceship,
                    Motion)       // makes pThis
    return pThis->InternalQueryInterface(lRid, ppvObj);
    // delegate to CSpaceship
}                               

DWORD CSpaceship::XMotion::Release()
{
    printf("Entering CSpaceship::XMotion::Release\n");
    METHOD_PROLOGUE(CSpaceship,
                    Motion)       // makes pThis
    return pThis->InternalRelease();
    // delegate to CSimulatedCmdTarget
}                               

DWORD CSpaceship::XMotion::AddRef ()
{
    printf("Entering CSpaceship::XMotion::AddRef\n");
    METHOD_PROLOGUE(CSpaceship,
                    Motion)       // makes pThis
    return pThis->InternalAddRef ();
    // delegate to CSimulatedCmdTarget
}                               

void CSpaceship::XMotion::Fly()
{
    printf("Entering CSpaceship::XMotion::Fly\n");
    METHOD_PROLOGUE(CSpaceship,
                    Motion)       // makes pThis
    printf("this = %p, pThis = %p\n", this, pThis);
    printf("m_nPosition = %d\n", pThis->m_nPosition);
    printf("m_nAcceleration = %d\n", m_nAcceleration);
}

int& CSpaceship::XMotion::GetPosition()
{
    printf("Entering CSpaceship::XMotion::GetPosition\n");
    METHOD_PROLOGUE(CSpaceship,
                    Motion)       // makes pThis
    printf("this = %p, pThis = %p\n", this, pThis);
    printf("m_nPosition = %d\n", pThis->m_nPosition);
    printf("m_nAcceleration = %d\n", m_nAcceleration);
    return pThis->m_nPosition;
}

BOOL CSpaceship::XVisual::QueryInterface(const long& lRid,
                                         void** ppvObj)
{
    printf("Entering CSpaceship::XVisual::QueryInterface --\
 lRid = %d\n", lRid);
    METHOD_PROLOGUE(CSpaceship,
                    Visual)       // makes pThis
    return pThis->InternalQueryInterface(lRid, ppvObj);
    // delegate to CSpaceship
}

DWORD CSpaceship::XVisual::Release()
{
    printf("Entering CSpaceship::XVisual::Release\n");
    METHOD_PROLOGUE(CSpaceship,
                    Visual)       // makes pThis
    return pThis->InternalRelease();
    // delegate to CSimulatedCmdTarget
}                               

DWORD CSpaceship::XVisual::AddRef ()
{
    printf("Entering CSpaceship::XVisual::AddRef\n");
    METHOD_PROLOGUE(CSpaceship,
                    Visual)       // makes pThis
    return pThis->InternalAddRef ();
    // delegate to CSimulatedCmdTarget
}                               

void CSpaceship::XVisual::Display()
{
    printf("Entering CSpaceship::XVisual::Display\n");
    METHOD_PROLOGUE(CSpaceship,
                    Visual)       // makes pThis
    printf("this = %p, pThis = %p\n", this, pThis);
    printf("m_nPosition = %d\n", pThis->m_nPosition);
    printf("m_nColor = %d\n", m_nColor);
}

//----------simulates OLE server -----------------------------------
// In real OLE, this would be DllGetClassObject, which would
//  be called whenever a client called CoGetClassObject.
    
BOOL GetClassObject(const long& lClsid, const long& lRid,
                    void** ppvObj)
{
    ASSERT(lClsid == CLSID_CSpaceship &&
           lRid == IID_IClassFactory);
    return factory.m_pUnknown->QueryInterface(IID_IClassFactory,
                                              ppvObj);
}
