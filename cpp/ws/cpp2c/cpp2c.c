#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#define UNUSED(x) (void)(x)

static int s_count = 0;

/******************************************************************************/
/*** typedef to function pointers *********************************************/
/******************************************************************************/

typedef void (*dtor_func_t)(void *this);
typedef void (*display_func_t)(void *this);
typedef void (*print_count_func_t)(void);
typedef int (*get_id_func_t)(PublicTransport_t *this);
typedef void (*wash_func_t)(Minibus_t *this, int minutes);

/******************************************************************************/
/*** typedef to structs *******************************************************/
/******************************************************************************/

typedef struct {
    void *vtable;
    get_id_func_t GetID;
    int m_license_plate;
} PublicTransport_t;

typedef struct  {
    PublicTransport_t PublicTransport;
} Taxi_t;

typedef struct {
    PublicTransport_t PublicTransport;
    int m_numSeats;
} Minibus_t;

typedef struct {
    Taxi_t Taxi;
} SpecialTaxi_t;

typedef struct {
    PublicTransport_t PublicTransport;
    PublicTransport_t *m_pt1;
    PublicTransport_t *m_pt2;
    Minibus_t m_m;
    Taxi_t m_t;
} PublicConvoy_t;

/******************************************************************************/
/*** vtables ******************************************************************/
/******************************************************************************/

typedef struct {
    dtor_func_t dtor;
    display_func_t display;
    print_count_func_t print_count;
} vtable_PublicTransport_t;

typedef struct {
    dtor_func_t dtor;
    display_func_t display;
    print_count_func_t print_count;
} vtable_Taxi_t;

typedef struct {
    dtor_func_t dtor;
    display_func_t display;
    print_count_func_t print_count;
    wash_func_t wash;
} vtable_Minibus_t;

typedef struct {
    dtor_func_t dtor;
    display_func_t display;
    print_count_func_t print_count;
} vtable_SpecialTaxi_t;

typedef struct {
    dtor_func_t dtor;
    display_func_t display;
    print_count_func_t count;
} vtable_PublicConvoy_t;

vtable_PublicTransport_t vtable_PublicTransport;
vtable_Taxi_t vtable_Taxi;
vtable_Minibus_t vtable_Minibus;
vtable_SpecialTaxi_t vtable_SpecialTaxi;
vtable_PublicConvoy_t vtable_PublicConvoy;

/******************************************************************************/
/*** Ctors ********************************************************************/
/******************************************************************************/

void PublicTransportTCtor(PublicTransport_t *this)
{
    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::Ctor()\n");
}

void TaxiCtor(Taxi_t *this)
{
    PublicTransportTCtor((PublicTransport_t*)this);
    printf("Taxi::Ctor()\n");
}

void MinibusCtor(Minibus_t *this)
{
    PublicTransportTCtor((PublicTransport_t*)this);
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void SpecialTaxiCtor(Taxi_t *this)
{
    PublicTransportTCtor((PublicTransport_t*)this);
    printf("SpecialTaxi::Ctor()\n");
}

void PublicConvoyCtor(PublicConvoy_t *this)
{
    PublicTransportTCtor((PublicTransport_t*)this);

    this->m_pt1 = (Minibus_t*)malloc(sizeof(Minibus_t));
    MinibusCtor(this->m_pt1);

    this->m_pt2 = (Taxi_t*)malloc(sizeof(Taxi_t));
    TaxiCtor(this->m_pt2);
}

/******************************************************************************/
/*** Dtors ********************************************************************/
/******************************************************************************/

void PublicTransportTDtor(PublicTransport_t *this)
{
    --s_count;
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
}

void TaxiDtor(Taxi_t *this)
{
    printf("Taxi::Dtor()\n");

    /* Dtor to base (PublicTransport_t) */
    PublicTransportTDtor((PublicTransport_t*)this);
}

void MinibusDtor(Minibus_t *this)
{
    printf("Minibus::Dtor()\n");

    /* Dtor to base (PublicTransport_t) */
    PublicTransportTDtor((PublicTransport_t*)this);
}

void SpecialTaxiDtor(SpecialTaxi_t *this)
{
    printf("SpecialTaxi::Dtor()\n");

    /* Dtor to base (Taxi_t) */
    TaxiDtor((Taxi_t*)this);
}

void PublicConvoyDtor(PublicConvoy_t *this)
{
    Minibus_t* m_pt1 = (Minibus_t*)this->m_pt1;
    Taxi_t* m_pt2 = (Taxi_t*)this->m_pt2;

    /* Dtor to m_pt1 (malloc'd Minubus_t) */
    ((vtable_Minibus_t*)(m_pt1->PublicTransport.vtable))->dtor(m_pt1);
    free(m_pt1);
    this->m_pt1 = NULL;

    /* Dtor to m_pt2 (malloc'd Taxi_t) */
    ((vtable_Taxi_t*)(m_pt2->PublicTransport.vtable))->dtor(m_pt2);
    free(m_pt2);
    this->m_pt2 = NULL;

    /* Dtor to m_m (Minubus_t) */
    MinibusDtor(&this->m_m);

    /* Dtor to m_m (Taxi_t) */
    TaxiDtor(&this->m_t);

    /* Dtor to base (PublicTransport_t) */
    PublicTransportTDtor((PublicTransport_t*)this);
}

/******************************************************************************/
/*** CCtors *******************************************************************/
/******************************************************************************/

void PublicTransportTCCtor(PublicTransport_t *this, PublicTransport_t *other)
{
    UNUSED(other);

    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void MinibusCCtor(Minibus_t *this, Minibus_t *other)
{
    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void TaxiCCtor(Taxi_t *this, Taxi_t *other)
{
    UNUSED(other);

    printf("Taxi::CCtor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi_t *this, SpecialTaxi_t *other)
{
    UNUSED(other);

    printf("SpecialTaxi::CCtor()\n");
}

/******************************************************************************/
/*** methods and global functions *********************************************/
/******************************************************************************/

void InitVTables(void)
{
    vtable_PublicTransport.dtor = PublicTransportTDtor;
    vtable_PublicTransport.display = PublicTransportDisplay;

    vtable_Taxi.dtor = TaxiDtor;
    vtable_Taxi.display = TaxiDisplay;

    vtable_Minibus.dtor = MinibusDtor;
    vtable_Minibus.display = MinibusDisplay;
    vtable_Minibus.wash = MinibusWash;

    vtable_SpecialTaxi.dtor = SpecialTaxiDtor;
    vtable_SpecialTaxi.display = SpecialTaxiDisplay;

    vtable_PublicConvoy.dtor = PublicConvoyDtor;
    vtable_PublicConvoy.display = PublicConvoyDisplay;
}

int GetID(PublicTransport_t* this)
{
    return this->m_license_plate;
}

/* static member function - global in c */
static void PrintCount()
{
    printf("s_count: %d\n", s_count);
}

void MinibusWash(Minibus_t *this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n", minutes, get_ID((PublicTransport_t*)this));
}

void PublicTransportDisplay(PublicTransport_t *this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void MinibusDisplay(Minibus_t *this)
{
    printf("Minibus::display() ID: %d", get_ID((PublicTransport_t*)this));
    printf(" num seats: %d\n", this->m_numSeats);
}

void TaxiDisplay(Taxi_t *this)
{
    printf("Taxi::display() ID: %d\n", get_ID((PublicTransport_t*)this));
}

void SpecialTaxiDisplay(SpecialTaxi_t *this)
{
    printf("SpecialTaxi::display() ID: %d\n", get_ID((PublicTransport_t*)this));
}

void PublicConvoyDisplay(PublicConvoy_t *this)
{
    Minibus_t* m_pt1 = (Minibus_t*)this->m_pt1;
    Taxi_t* m_pt2 = (Taxi_t*)this->m_pt2;
    Minibus_t m_m = (Minibus_t)this->m_m;
    Taxi_t m_t = (Taxi_t)this->m_t;

    ((vtable_Minibus_t*)(m_pt1->PublicTransport.vtable))->display(m_pt1);
    ((vtable_Taxi_t*)(m_pt2->PublicTransport.vtable))->display(m_pt2);
    ((vtable_Minibus_t*)(m_m.PublicTransport.vtable))->display(&m_m);
    ((vtable_Taxi_t*)(m_t.PublicTransport.vtable))->display(&m_t);
}

void TaxiDisplayGlobal(Taxi_t s)
{
    ((vtable_Taxi_t*)(s.PublicTransport.vtable))->display(&s);
}

void PrintInfoPublicTransport(PublicTransport_t *a)
{
    ((vtable_PublicTransport_t*)(a->vtable))->display(a);
}

void PrintInfoCount()
{
    PrintCount();
}

void PrintInfoMinibus(Minibus_t *m)
{
    ((vtable_Minibus_t*)(m->PublicTransport.vtable))->wash(m, 3);
}

PublicTransport_t PrintInfoInt(int i)
{
    UNUSED(i);
    Minibus_t ret;
    MinibusCtor(&ret);
    printf("print_info(int i)\n");   
    ((vtable_Minibus_t*)(ret.PublicTransport.vtable))->display(&ret);
    return ret.PublicTransport;
}

int main()
{

    return 0;
}
