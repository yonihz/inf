#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#define UNUSED(x) (void)(x)

static int s_count = 0;

/******************************************************************************/
/*** typedef to structs *******************************************************/
/******************************************************************************/

typedef struct {
    void *vtable;
    int (*get_id)(void *this);
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
    void (*dtor)(void *this);
    void (*display)(void *this);
    void (*print_count)(void);
} vtable_PublicTransport_t;

typedef struct {
    void (*dtor)(void *this);
    void (*display)(void *this);
    void (*print_count)(void);
} vtable_Taxi_t;

typedef struct {
    void (*dtor)(void *this);
    void (*display)(void *this);
    void (*print_count)(void);
    void (*wash)(void *this, int minutes);
} vtable_Minibus_t;

typedef struct {
    void (*dtor)(void *this);
    void (*display)(void *this);
    void (*print_count)(void);
} vtable_SpecialTaxi_t;

typedef struct {
    void (*dtor)(void *this);
    void (*display)(void *this);
    void (*print_count)(void);
} vtable_PublicConvoy_t;

vtable_PublicTransport_t vtable_PublicTransport;
vtable_Taxi_t vtable_Taxi;
vtable_Minibus_t vtable_Minibus;
vtable_SpecialTaxi_t vtable_SpecialTaxi;
vtable_PublicConvoy_t vtable_PublicConvoy;

/******************************************************************************/
/*** function declarations ****************************************************/
/******************************************************************************/

void PublicTransportCtor(PublicTransport_t *this);
void TaxiCtor(Taxi_t *this);
void MinibusCtor(Minibus_t *this);
void SpecialTaxiCtor(Taxi_t *this);
void PublicConvoyCtor(PublicConvoy_t *this);

void PublicTransportDtor(void *this);
void TaxiDtor(void *this);
void MinibusDtor(void *this);
void SpecialTaxiDtor(void *this);
void PublicConvoyDtor(void *this);

void InitVTables(void);
int GetID(void* this);
static void PrintCount();
void MinibusWash(void *this, int minutes);
void PublicTransportDisplay(void *this);
void MinibusDisplay(void *this);
void TaxiDisplay(void *this);
void SpecialTaxiDisplay(void *this);
void PublicConvoyDisplay(void *this);
void TaxiDisplayGlobal(Taxi_t s);
void PrintInfoPublicTransport(PublicTransport_t *a);
void PrintInfoCount();
void PrintInfoMinibus(Minibus_t *m);
PublicTransport_t PrintInfoInt(int i);

/******************************************************************************/
/*** Ctors ********************************************************************/
/******************************************************************************/

void PublicTransportCtor(PublicTransport_t *this)
{
    this->vtable = &vtable_PublicTransport;
    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::Ctor()\n");
}

void TaxiCtor(Taxi_t *this)
{
    PublicTransportCtor((PublicTransport_t*)this);
    this->PublicTransport.vtable = &vtable_Taxi;
    printf("Taxi::Ctor()\n");
}

void MinibusCtor(Minibus_t *this)
{
    PublicTransportCtor((PublicTransport_t*)this);
    this->PublicTransport.vtable = &vtable_Minibus;
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void SpecialTaxiCtor(Taxi_t *this)
{
    PublicTransportCtor((PublicTransport_t*)this);
    this->PublicTransport.vtable = &vtable_SpecialTaxi;
    printf("SpecialTaxi::Ctor()\n");
}

void PublicConvoyCtor(PublicConvoy_t *this)
{
    PublicTransportCtor((PublicTransport_t*)this);
    this->PublicTransport.vtable = &vtable_PublicConvoy;

    this->m_pt1 = malloc(sizeof(Minibus_t));
    MinibusCtor((Minibus_t*)(this->m_pt1));

    this->m_pt2 = malloc(sizeof(Taxi_t));
    TaxiCtor((Taxi_t*)(this->m_pt2));
}

/******************************************************************************/
/*** Dtors ********************************************************************/
/******************************************************************************/

void PublicTransportDtor(void *this)
{
    PublicTransport_t* this_p = this;
    --s_count;
    printf("PublicTransport::Dtor() %d\n", this_p->m_license_plate);
}

void TaxiDtor(void *this)
{
    Taxi_t *this_t = (Taxi_t*)this;
    printf("Taxi::Dtor()\n");

    /* Dtor to base (PublicTransport_t) */
    PublicTransportDtor((PublicTransport_t*)this_t);
}

void MinibusDtor(void *this)
{
    Minibus_t *this_m = (Minibus_t*)this;
    printf("Minibus::Dtor()\n");

    /* Dtor to base (PublicTransport_t) */
    PublicTransportDtor((PublicTransport_t*)this_m);
}

void SpecialTaxiDtor(void *this)
{
    SpecialTaxi_t* this_s = (SpecialTaxi_t*)this;
    printf("SpecialTaxi::Dtor()\n");

    /* Dtor to base (Taxi_t) */
    TaxiDtor((Taxi_t*)this_s);
}

void PublicConvoyDtor(void *this)
{
    PublicConvoy_t *this_p = (PublicConvoy_t*)this;
    Minibus_t* m_pt1 = (Minibus_t*)this_p->m_pt1;
    Taxi_t* m_pt2 = (Taxi_t*)this_p->m_pt2;

    /* Dtor to m_pt1 (malloc'd Minubus_t) */
    ((vtable_Minibus_t*)(m_pt1->PublicTransport.vtable))->dtor(m_pt1);
    free(m_pt1);
    this_p->m_pt1 = NULL;

    /* Dtor to m_pt2 (malloc'd Taxi_t) */
    ((vtable_Taxi_t*)(m_pt2->PublicTransport.vtable))->dtor(m_pt2);
    free(m_pt2);
    this_p->m_pt2 = NULL;

    /* Dtor to m_m (Minubus_t) */
    MinibusDtor(&this_p->m_m);

    /* Dtor to m_m (Taxi_t) */
    TaxiDtor(&this_p->m_t);

    /* Dtor to base (PublicTransport_t) */
    PublicTransportDtor((PublicTransport_t*)this);
}

/******************************************************************************/
/*** CCtors *******************************************************************/
/******************************************************************************/

void PublicTransportCCtor(PublicTransport_t *this, PublicTransport_t *other)
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
    UNUSED(this);
    UNUSED(other);

    printf("Taxi::CCtor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi_t *this, SpecialTaxi_t *other)
{
    UNUSED(this);
    UNUSED(other);

    printf("SpecialTaxi::CCtor()\n");
}

/******************************************************************************/
/*** methods and global functions *********************************************/
/******************************************************************************/

void InitVTables(void)
{
    vtable_PublicTransport.dtor = PublicTransportDtor;
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

int GetID(void* this)
{
    PublicTransport_t *this_p = (PublicTransport_t*)this;
    return this_p->m_license_plate;
}

/* static member function - global in c */
static void PrintCount()
{
    printf("s_count: %d\n", s_count);
}

void MinibusWash(void *this, int minutes)
{
    Minibus_t *this_m = (Minibus_t*)this;
    printf("Minibus::wash(%d) ID: %d\n", minutes, GetID((PublicTransport_t*)this_m));
}

void PublicTransportDisplay(void *this)
{
    PublicTransport_t *this_p = (PublicTransport_t*)this;
    printf("PublicTransport::display(): %d\n", this_p->m_license_plate);
}

void MinibusDisplay(void *this)
{
    Minibus_t *this_m = (Minibus_t*)this;
    printf("Minibus::display() ID: %d", GetID((PublicTransport_t*)this_m));
    printf(" num seats: %d\n", this_m->m_numSeats);
}

void TaxiDisplay(void *this)
{
    Taxi_t *this_t = (Taxi_t*)this;
    printf("Taxi::display() ID: %d\n", GetID((PublicTransport_t*)this_t));
}

void SpecialTaxiDisplay(void *this)
{
    SpecialTaxi_t *this_s = (SpecialTaxi_t*)this;
    printf("SpecialTaxi::display() ID: %d\n", GetID((PublicTransport_t*)this_s));
}

void PublicConvoyDisplay(void *this)
{
    PublicConvoy_t *this_p = (PublicConvoy_t*)this;
    Minibus_t* m_pt1 = (Minibus_t*)this_p->m_pt1;
    Taxi_t* m_pt2 = (Taxi_t*)this_p->m_pt2;
    Minibus_t m_m = this_p->m_m;
    Taxi_t m_t = this_p->m_t;

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
    MinibusDtor(&ret); // need to call dtor before function ends
    return ret.PublicTransport;
}

int main()
{
    InitVTables();

    // Minibus m;
    Minibus_t m;
    MinibusCtor(&m);

    // print_info(m);
    PrintInfoMinibus(&m);

    // print_info(3).display();
    PublicTransport_t temp;
    temp = PrintInfoInt(3);
    ((vtable_PublicTransport_t*)(temp.vtable))->display(&temp);

    // PublicTransport *array[] = { new Minibus(), new Taxi(), new Minibus() };
    Minibus_t *minibus1_ptr;
    minibus1_ptr = malloc(sizeof(Minibus_t));
    MinibusCtor(minibus1_ptr);

    Taxi_t *taxi_ptr;
    taxi_ptr = malloc(sizeof(Taxi_t));
    TaxiCtor(taxi_ptr);
    
    Minibus_t *minibus2_ptr;
    minibus2_ptr = malloc(sizeof(Minibus_t));
    MinibusCtor(minibus2_ptr);

    // PublicTransport_t *array[] = {minibus1_ptr, taxi_ptr, minibus2_ptr};

    // for (int i = 0; i < 3; ++i) {
    //     array[i]->display();
    // }

    // for (int i = 0; i < 3; ++i) {
    //     if (i == 0 && i == 2)
    //     {
    //         ((vtable_Minibus_t*)(array[i]->vtable))->display(array[i]);
    //     }

    //     else if (i == 1)
    //     {
    //         ((vtable_Taxi_t*)(array[i]->vtable))->display(array[i]);
    //     }
    // }

    // for (int i = 0; i < 3; ++i) {
    //     delete array[i];
    // }

    // for (int i = 0; i < 3; ++i) {
    //     if (i == 0 && i == 2)
    //     {
    //         ((vtable_Minibus_t*)(array[i]->vtable))->dtor(array[i]);
    //     }
    //     else if (i == 1)
    //     {
    //         ((vtable_Taxi_t*)(array[i]->vtable))->dtor(array[i]);
    //     }
        
    //     free(array[i]);
    // }

    // PublicTransport arr2[] = { Minibus(), Taxi(), PublicTransport() };
    // Minibus_t minibus1;
    // MinibusCtor(&minibus1);

    // Taxi_t taxi1;
    // TaxiCtor(&taxi1);

    // PublicTransport_t publict1;
    // PublicTransportCtor(&publict1);

    // PublicTransport_t *arr2[] = {&minibus1, &taxi1, &publict1};

    // for (int i = 0; i < 3; ++i) {
    //     arr2[i].display();
    // }
    // print_info(arr2[0]);

    // PublicTransport::print_count();
    // Minibus m2;
    // m2.print_count();

    // Minibus arr3[4];
    // Taxi *arr4 = new Taxi[4];
    // delete[] arr4;

    // std::cout << max_func(1, 2) << "\n";
    // std::cout << max_func<int>(1, 2.0f)<< "\n";
    // SpecialTaxi st;
    // taxi_display(st);

    // PublicConvoy *ts1 = new PublicConvoy();
    // PublicConvoy *ts2 = new PublicConvoy(*ts1);
    // ts1->display();
    // ts2->display();
    // delete ts1;
    // ts2->display(); 
    // delete ts2;

    return 0;
}
