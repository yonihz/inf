#include <stdio.h>  /* printf */

#define UNUSED(x) (void)(x)

static int s_count = 0;

/******************************************************************************/
/*** typedef to function pointers *********************************************/
/******************************************************************************/

typedef void (*dtor_func_t)(void *this);
typedef void (*display_func_t)(void);
typedef void (*print_count_func_t)(void);
typedef int (*get_id_func_t)(PublicTransportation_t *this);
typedef void (*wash_func_t)(int minutes);

/******************************************************************************/
/*** typedef to structs *******************************************************/
/******************************************************************************/

typedef struct {
    void *vtable;
    get_id_func_t GetID;
    int m_license_plate;
} PublicTransportation_t;

typedef struct  {
    PublicTransportation_t PublicTransportation;
} Taxi_t;

typedef struct {
    PublicTransportation_t PublicTransportation;
    int m_numSeats;
} Minibus_t;

typedef struct {
    Taxi_t Taxi;
} SpecialTaxi_t;

typedef struct {
    PublicTransportation_t PublicTransportation;
    PublicTransportation_t *m_pt1;
    PublicTransportation_t *m_pt2;
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
} vtable_PublicTransportation_t;

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

vtable_PublicTransportation_t vtable_PublicTransportation;
vtable_Taxi_t vtable_Taxi;
vtable_Minibus_t vtable_Minibus;
vtable_SpecialTaxi_t vtable_SpecialTaxi;
vtable_PublicConvoy_t vtable_PublicConvoy;

/******************************************************************************/
/*** Ctors ********************************************************************/
/******************************************************************************/

void PublicTransportationTCtor(PublicTransportation_t *this)
{
    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::Ctor()\n");
}

void TaxiCtor(Taxi_t *this)
{
    PublicTransportationTCtor((PublicTransportation_t*)this);
    printf("Taxi::Ctor()\n");
}

void MinibusCtor(Minibus_t *this)
{
    PublicTransportationTCtor((PublicTransportation_t*)this);
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void SpecialTaxiCtor(Taxi_t *this)
{
    PublicTransportationTCtor((PublicTransportation_t*)this);
    printf("SpecialTaxi::Ctor()\n");
}

void PublicConvoyCtor(PublicConvoy_t *this)
{
    PublicTransportationTCtor((PublicTransportation_t*)this);

    this->m_pt1 = (Minibus_t*)malloc(sizeof(Minibus_t));
    MinibusCtor(this->m_pt1);

    this->m_pt2 = (Taxi_t*)malloc(sizeof(Taxi_t));
    TaxiCtor(this->m_pt2);
}

/******************************************************************************/
/*** Dtors ********************************************************************/
/******************************************************************************/

void PublicTransportationTDtor(PublicTransportation_t *this)
{
    --s_count;
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
}

void TaxiDtor(Taxi_t *this)
{
    printf("Taxi::Dtor()\n");

    /* Dtor to base (PublicTransportation_t) */
    PublicTransportationTDtor((PublicTransportation_t*)this);
}

void MinibusDtor(Minibus_t *this)
{
    printf("Minibus::Dtor()\n");

    /* Dtor to base (PublicTransportation_t) */
    PublicTransportationTDtor((PublicTransportation_t*)this);
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
    ((vtable_Minibus_t*)(m_pt1->PublicTransportation.vtable))->dtor(m_pt1);
    free(m_pt1);
    this->m_pt1 = NULL;

    /* Dtor to m_pt2 (malloc'd Taxi_t) */
    ((vtable_Taxi_t*)(m_pt2->PublicTransportation.vtable))->dtor(m_pt2);
    free(m_pt2);
    this->m_pt2 = NULL;

    /* Dtor to m_m (Minubus_t) */
    MinibusDtor(&this->m_m);

    /* Dtor to m_m (Taxi_t) */
    TaxiDtor(&this->m_t);

    /* Dtor to base (PublicTransportation_t) */
    PublicTransportationTDtor((PublicTransportation_t*)this);
}

/******************************************************************************/
/*** CCtors *******************************************************************/
/******************************************************************************/

void PublicTransportationTCCtor(PublicTransportation_t *this, PublicTransportation_t *other)
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
    vtable_PublicTransportation.dtor = PublicTransportationTDtor;
    vtable_PublicTransportation.display = PublicTransportDisplay;

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

int GetID(PublicTransportation_t* this)
{
    return this->m_license_plate;
}

static void PrintCount()
{
    printf("s_count: %d\n", s_count);
}

void MinibusWash(Minibus_t *this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n", minutes, get_ID((PublicTransportation_t*)this));
}

void PublicTransportDisplay(PublicTransportation_t *this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void MinibusDisplay(Minibus_t *this)
{
    printf("Minibus::display() ID: %d", get_ID((PublicTransportation_t*)this));
    printf(" num seats: %d\n", this->m_numSeats);
}

void TaxiDisplay(Taxi_t *this)
{
    printf("Taxi::display() ID: %d\n", get_ID((PublicTransportation_t*)this));
}

void SpecialTaxiDisplay(SpecialTaxi_t *this)
{
    printf("SpecialTaxi::display() ID: %d\n", get_ID((PublicTransportation_t*)this));
}

void PublicConvoyDisplay()
{
    // m_pt1->display();
    // m_pt2->display();
    // m_m.display();
    // m_t.display();
}

void TaxiDisplayGlobal(Taxi_t s)
{
    //s.PublicTransportation.vtable->
}

void print_info(PublicTransport &a)
{
    // a.display();
}

void print_info()
{
    // PublicTransport::print_count();
}

void print_info(Minibus &m)
{
    // m.wash(3);
}

PublicTransport_t print_info(int i)
{
    // Minibus ret;
    // cout << "print_info(int i)\n";
    // ret.display();
    // return ret;
}
