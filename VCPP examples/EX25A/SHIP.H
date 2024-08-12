// ship.h
#include <stddef.h> // for offsetof in METHOD_PROLOGUE

//----------Definitions and Macros----------------------------------
#define IID_IUnknown            0
#define IID_IClassFactory       1
#define IID_IMotion             2
#define IID_IVisual             3
#define CLSID_CSpaceship        10

// this macro for 16-bit Windows only
#define METHOD_PROLOGUE(theClass, localClass) \
 theClass* pThis = ((theClass*)((char*)(this) - \
 offsetof(theClass, m_x##localClass))); \

//----------Interface Declarations----------------------------------
struct IUnknown
{
    IUnknown() {
        printf("Entering IUnknown constructor %p\n", this);
    }
    virtual BOOL QueryInterface(const long& lRid,
                                void** ppvObj) = 0;
    virtual DWORD Release() = 0;
    virtual DWORD AddRef() = 0;
};

struct IClassFactory : public IUnknown
{
    IClassFactory() {
        printf("Entering IClassFactory constructor %p\n", this);
    }
    virtual BOOL CreateInstance(const long& lRid,
                                void** ppvObj) = 0;
};

struct IMotion : public IUnknown
{
    IMotion() {
        printf("Entering IMotion constructor %p\n", this);
    }
    virtual void Fly() = 0;  // pure
    virtual int& GetPosition() = 0;
};

struct IVisual : public IUnknown
{
    IVisual() {
        printf("Entering IVisual constructor %p\n", this);
    }
    virtual void Display() = 0;
};

//----------Class Declarations--------------------------------------
class CSimulatedCmdTarget    // 'simulated' CSimulatedCmdTarget
{
public:
    IUnknown* m_pUnknown;    // not needed in real MFC
    DWORD     m_dwRef;

protected:
    CSimulatedCmdTarget() {
        printf("Entering CSimulatedCmdTarget constructor %p\n",
                this);
        m_dwRef = 1;         // implied first AddRef
    }
    virtual ~CSimulatedCmdTarget() {
        printf("Entering CSimulatedCmdTarget destructor %p\n",
                this);
    }
    DWORD InternalRelease() {
        printf("Entering CSimulatedCmdTarget::InternalRelease --\
 RefCount = %ld\n", m_dwRef);
        if (m_dwRef == 0)
          return 0;
        if (--m_dwRef == 0L) {
          printf("deleting\n");
          delete this;
          return 0;
        }
        return m_dwRef;
    }
    DWORD InternalAddRef() {
        return ++m_dwRef;
    }
};  

class CSpaceship;

class CSpaceshipFactory : public CSimulatedCmdTarget
{
public:
    CSpaceshipFactory() {
        printf("Entering CSpaceshipFactory constructor %p\n",
                this);
        m_pUnknown = &m_xClassFactory;
    }
    ~CSpaceshipFactory() {
        printf("Entering CSpaceshipFactory destructor %p\n",
                this);
    }
    class XClassFactory : public IClassFactory
    {
    public:
        XClassFactory() {
            printf("Entering XClassFactory constructor %p\n",
                    this);
        }
        virtual BOOL QueryInterface(const long& lRid,
                                    void** ppvObj);
        virtual DWORD Release();
        virtual DWORD AddRef();
        virtual BOOL  CreateInstance(const long& lRid,
                                     void** ppvObj);
    } m_xClassFactory;
    friend class XClassFactory;
};

class CSpaceship : public CSimulatedCmdTarget
{
private:
    int m_nPosition; // We can access this from all the interfaces.
public:
    BOOL InternalQueryInterface(const long& lRid,
                                void** ppvObj);
    CSpaceship() {
        printf("Entering CSpaceship constructor %p\n", this);
        m_nPosition = 100;
        m_pUnknown = &m_xMotion;
    }
    ~CSpaceship() {
        printf("Entering CSpaceship destructor %p\n", this);
    }
    class XMotion : public IMotion
    {
    private:
        int m_nAcceleration;
    public:
        XMotion() {
            printf("Entering XMotion constructor %p\n", this);
            m_nAcceleration = 101;
        }
        virtual BOOL QueryInterface(const long& lRid,
                                    void** ppvObj);
        virtual DWORD Release();
        virtual DWORD AddRef();
        virtual void  Fly();
        virtual int&  GetPosition();
    } m_xMotion;
    
    class XVisual : public IVisual
    {
    private:
        int m_nColor;
    public:
        XVisual() {
            printf("Entering XVisual constructor\n");
            m_nColor = 102;
        }
        virtual BOOL QueryInterface(const long& lRid,
                                    void** ppvObj);
        virtual DWORD Release();
        virtual DWORD AddRef();
        virtual void Display();
    } m_xVisual;

    friend class XVisual;  // These must be at the bottom!
    friend class XMotion;
    friend class CSpaceshipFactory::XClassFactory;
};

BOOL GetClassObject(const long& lClsid, const long& lRid,
                    void** ppvObj);

