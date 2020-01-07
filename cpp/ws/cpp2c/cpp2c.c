#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#define UNUSED(x) (void)(x)

#define MAX_FUNC(t1, t2) (((t1) > (t2)) ? (t1) : (t2))

static int s_count = 0;

/******************************************************************************/
/*** structs ******************************************************************/
/******************************************************************************/

typedef struct PublicTransport PublicTransport_t;
typedef struct Taxi Taxi_t;
typedef struct Minibus Minibus_t;
typedef struct SpecialTaxi SpecialTaxi_t;
typedef struct PublicConvoy PublicConvoy_t;

struct PublicTransport {
    void *vtable;
    int (*get_id)(PublicTransport_t *this);
    void (*print_count)(void);
    int m_license_plate;
};

struct Taxi {
    PublicTransport_t PublicTransport;
};

struct Minibus {
    PublicTransport_t PublicTransport;
    int m_numSeats;
};

struct SpecialTaxi {
    Taxi_t Taxi;
};

struct PublicConvoy {
    PublicTransport_t PublicTransport;
    PublicTransport_t *m_pt1;
    PublicTransport_t *m_pt2;
    Minibus_t m_m;
    Taxi_t m_t;
};

/******************************************************************************/
/*** vtables ******************************************************************/
/******************************************************************************/

typedef struct {
    void (*dtor)(PublicTransport_t *this);
    void (*display)(PublicTransport_t *this);
} vtable_PublicTransport_t;

typedef struct {
    void (*dtor)(PublicTransport_t *this);
    void (*display)(PublicTransport_t *this);
} vtable_Taxi_t;

typedef struct {
    void (*dtor)(PublicTransport_t *this);
    void (*display)(PublicTransport_t *this);
    void (*wash)(Minibus_t *this, int minutes);
} vtable_Minibus_t;

typedef struct {
    void (*dtor)(PublicTransport_t *this);
    void (*display)(PublicTransport_t *this);
} vtable_SpecialTaxi_t;

typedef struct {
    void (*dtor)(PublicTransport_t *this);
    void (*display)(PublicTransport_t *this);
} vtable_PublicConvoy_t;

/******************************************************************************/
/*** function declarations ****************************************************/
/******************************************************************************/

void PublicTransportCtor(PublicTransport_t *this);
void TaxiCtor(Taxi_t *this);
void MinibusCtor(Minibus_t *this);
void SpecialTaxiCtor(SpecialTaxi_t *this);
void PublicConvoyCtor(PublicConvoy_t *this);

void PublicTransportDtor(PublicTransport_t *this);
void TaxiDtor(PublicTransport_t *this);
void MinibusDtor(PublicTransport_t *this);
void SpecialTaxiDtor(PublicTransport_t *this);
void PublicConvoyDtor(PublicTransport_t *this);

void PublicTransportCCtor(PublicTransport_t *this, PublicTransport_t *other);
void MinibusCCtor(Minibus_t *this, Minibus_t *other);
void TaxiCCtor(Taxi_t *this, Taxi_t *other);
void SpecialTaxiCCtor(SpecialTaxi_t *this, SpecialTaxi_t *other);
void PublicConvoyCCtor(PublicConvoy_t *this, PublicConvoy_t *other);

int GetID(PublicTransport_t* this);
static void PrintCount();
void MinibusWash(Minibus_t *this, int minutes);
void PublicTransportDisplay(PublicTransport_t *this);
void MinibusDisplay(PublicTransport_t *this);
void TaxiDisplay(PublicTransport_t *this);
void SpecialTaxiDisplay(PublicTransport_t *this);
void PublicConvoyDisplay(PublicTransport_t *this);
void TaxiDisplayGlobal(Taxi_t s);
void PrintInfoPublicTransport(PublicTransport_t *a);
void PrintInfoCount();
void PrintInfoMinibus(Minibus_t *m);
void PrintInfoInt(PublicTransport_t* ret_publict, int i);

/******************************************************************************/
/*** vtables init *************************************************************/
/******************************************************************************/

vtable_PublicTransport_t vtable_PublicTransport = {
    .dtor = PublicTransportDtor,
    .display = PublicTransportDisplay};

vtable_Taxi_t vtable_Taxi = {
    .dtor = TaxiDtor,
    .display = TaxiDisplay};

vtable_Minibus_t vtable_Minibus = {
    .dtor = MinibusDtor,
    .display = MinibusDisplay,
    .wash = MinibusWash};

vtable_SpecialTaxi_t vtable_SpecialTaxi = {
    .dtor = SpecialTaxiDtor,
    .display = SpecialTaxiDisplay};

vtable_PublicConvoy_t vtable_PublicConvoy = {
    .dtor = PublicConvoyDtor,
    .display = PublicConvoyDisplay};

/******************************************************************************/
/*** Ctors ********************************************************************/
/******************************************************************************/

void PublicTransportCtor(PublicTransport_t *this)
{
    this->vtable = &vtable_PublicTransport;
    this->print_count = PrintCount;
    this->get_id = GetID;

    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::Ctor() %d\n", this->m_license_plate);
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

void SpecialTaxiCtor(SpecialTaxi_t *this)
{
    TaxiCtor((Taxi_t*)this);
    this->Taxi.PublicTransport.vtable = &vtable_SpecialTaxi;

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

    MinibusCtor(&(this->m_m));

    TaxiCtor(&(this->m_t));
}

/******************************************************************************/
/*** Dtors ********************************************************************/
/******************************************************************************/

void PublicTransportDtor(PublicTransport_t *this)
{
    --s_count;
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
}

void TaxiDtor(PublicTransport_t *this)
{
    printf("Taxi::Dtor()\n");

    PublicTransportDtor(this);
}

void MinibusDtor(PublicTransport_t *this)
{
    printf("Minibus::Dtor()\n");

    PublicTransportDtor(this);
}

void SpecialTaxiDtor(PublicTransport_t *this)
{
    printf("SpecialTaxi::Dtor()\n");

    TaxiDtor(this);
}

void PublicConvoyDtor(PublicTransport_t *this)
{
    PublicConvoy_t *this_p = (PublicConvoy_t*)this;

    /* Dtor to m_pt1 (malloc'd Minubus_t) */
    ((vtable_Minibus_t*)(this_p->m_pt1->vtable))->dtor(this_p->m_pt1);
    free(this_p->m_pt1);
    this_p->m_pt1 = NULL;

    /* Dtor to m_pt2 (malloc'd Taxi_t) */
    ((vtable_Taxi_t*)(this_p->m_pt2->vtable))->dtor(this_p->m_pt2);
    free(this_p->m_pt2);
    this_p->m_pt2 = NULL;

    /* Dtor to m_t (Taxi_t) */
    TaxiDtor((PublicTransport_t*)&this_p->m_t);

    /* Dtor to m_m (Minubus_t) */
    MinibusDtor((PublicTransport_t*)&this_p->m_m);

    PublicTransportDtor(this);
}

/******************************************************************************/
/*** CCtors *******************************************************************/
/******************************************************************************/

void PublicTransportCCtor(PublicTransport_t *this, PublicTransport_t *other)
{
    UNUSED(other);
    this->vtable = &vtable_PublicTransport;
    this->print_count = PrintCount;
    this->get_id = GetID;

    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void MinibusCCtor(Minibus_t *this, Minibus_t *other)
{
    PublicTransportCCtor((PublicTransport_t*)this,(PublicTransport_t*)other);
    this->PublicTransport.vtable = &vtable_Minibus;

    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void TaxiCCtor(Taxi_t *this, Taxi_t *other)
{
    PublicTransportCCtor((PublicTransport_t*)this,(PublicTransport_t*)other);
    this->PublicTransport.vtable = &vtable_Taxi;

    printf("Taxi::CCtor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi_t *this, SpecialTaxi_t *other)
{
    TaxiCCtor((Taxi_t*)this,(Taxi_t*)other);
    this->Taxi.PublicTransport.vtable = &vtable_SpecialTaxi;

    printf("SpecialTaxi::CCtor()\n");
}

void PublicConvoyCCtor(PublicConvoy_t *this, PublicConvoy_t *other)
{
    PublicTransportCCtor((PublicTransport_t*)this,(PublicTransport_t*)other);
    this->PublicTransport.vtable = &vtable_PublicConvoy;

    this->m_pt1 = other->m_pt1;
    this->m_pt2 = other->m_pt2;
    MinibusCCtor(&(this->m_m), &(other->m_m));
    TaxiCCtor(&(this->m_t), &(other->m_t));
}

/******************************************************************************/
/*** function definitions *****************************************************/
/******************************************************************************/

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
    printf("Minibus::wash(%d) ID: %d\n", minutes, GetID((PublicTransport_t*)this));
}

void PublicTransportDisplay(PublicTransport_t *this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void MinibusDisplay(PublicTransport_t *this)
{
    Minibus_t *this_m = (Minibus_t*)this;
    printf("Minibus::display() ID: %d", GetID(this));
    printf(" num seats: %d\n", this_m->m_numSeats);
}

void TaxiDisplay(PublicTransport_t *this)
{
    printf("Taxi::display() ID: %d\n", GetID(this));
}

void SpecialTaxiDisplay(PublicTransport_t *this)
{
    printf("SpecialTaxi::display() ID: %d\n", GetID(this));
}

void PublicConvoyDisplay(PublicTransport_t *this)
{
    PublicConvoy_t *this_p = (PublicConvoy_t*)this;

    ((vtable_Minibus_t*)(this_p->m_pt1->vtable))->display(this_p->m_pt1);
    ((vtable_Taxi_t*)(this_p->m_pt2->vtable))->display(this_p->m_pt2);

    MinibusDisplay((PublicTransport_t*)&this_p->m_m);
    TaxiDisplay((PublicTransport_t*)&this_p->m_t);
    // ((vtable_Minibus_t*)(this_p->m_m.PublicTransport.vtable))->display((PublicTransport_t*)&this_p->m_m);
    // ((vtable_Taxi_t*)(this_p->m_t.PublicTransport.vtable))->display((PublicTransport_t*)&this_p->m_t);
}

void TaxiDisplayGlobal(Taxi_t s)
{
    TaxiDisplay((PublicTransport_t*)&s);
    // ((vtable_Taxi_t*)(s.PublicTransport.vtable))->display((PublicTransport_t*)&s);
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

void PrintInfoInt(PublicTransport_t* ret_publict, int i)
{
    UNUSED(i);
    Minibus_t ret;
    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    MinibusDisplay((PublicTransport_t*)&ret);
    // ((vtable_Minibus_t*)(ret.PublicTransport.vtable))->display((PublicTransport_t*)&ret);
    PublicTransportCCtor(ret_publict, (PublicTransport_t*)&ret);
    MinibusDtor((PublicTransport_t*)&ret);
}

/******************************************************************************/
/*** main *********************************************************************/
/******************************************************************************/

int main()
{
    // Minibus m;
    Minibus_t m;
    MinibusCtor(&m);

    // print_info(m);
    PrintInfoMinibus(&m);

    // print_info(3).display();
    PublicTransport_t temp_p; // no ctor since cctor will be called next
    PrintInfoInt(&temp_p, 3);
    PublicTransportDisplay(&temp_p);
    // ((vtable_PublicTransport_t*)(temp_p.vtable))->display(&temp_p);
    ((vtable_PublicTransport_t*)(temp_p.vtable))->dtor(&temp_p);

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

    PublicTransport_t *array[] = {
        (PublicTransport_t *)minibus1_ptr,
        (PublicTransport_t *)taxi_ptr,
        (PublicTransport_t *)minibus2_ptr};

    // for (int i = 0; i < 3; ++i) {
    //     array[i]->display();
    // }

    for (int i = 0; i < 3; ++i) {
        if (i == 0 || i == 2)
        {
            ((vtable_Minibus_t*)(array[i]->vtable))->display(array[i]);
        }

        else if (i == 1)
        {
            ((vtable_Taxi_t*)(array[i]->vtable))->display(array[i]);
        }
    }

    // for (int i = 0; i < 3; ++i) {
    //     delete array[i];
    // }

    for (int i = 0; i < 3; ++i) {
        if (i == 0 || i == 2)
        {
            ((vtable_Minibus_t*)(array[i]->vtable))->dtor(array[i]);
        }
        else if (i == 1)
        {
            ((vtable_Taxi_t*)(array[i]->vtable))->dtor(array[i]);
        }
        
        free(array[i]);
    }

    // PublicTransport arr2[] = { Minibus(), Taxi(), PublicTransport() };
    Minibus_t minibus1;
    MinibusCtor(&minibus1);
    PublicTransport_t minibus1_p;
    PublicTransportCCtor(&minibus1_p, (PublicTransport_t*)&minibus1);
    ((vtable_Minibus_t*)(minibus1.PublicTransport.vtable))->dtor((PublicTransport_t*)&minibus1);

    Taxi_t taxi1;
    TaxiCtor(&taxi1);
    PublicTransport_t taxi1_p;
    PublicTransportCCtor(&taxi1_p, (PublicTransport_t*)&taxi1);
    ((vtable_Taxi_t*)(taxi1.PublicTransport.vtable))->dtor((PublicTransport_t*)&taxi1);

    PublicTransport_t publict1;
    PublicTransportCtor(&publict1);

    PublicTransport_t arr2[] = {minibus1_p, taxi1_p, publict1};

    // for (int i = 0; i < 3; ++i) {
    //     arr2[i].display();
    // }

    for (int i = 0; i < 3; ++i) {
        PublicTransportDisplay(&arr2[i]);
        // ((vtable_PublicTransport_t*)(arr2[i].vtable))->display(&arr2[i]);
    }   

    // print_info(arr2[0]);

    PrintInfoPublicTransport(&arr2[0]);

    // PublicTransport::print_count();

    PrintCount();

    // Minibus m2;

    Minibus_t m_2;
    MinibusCtor(&m_2);

    // m2.print_count();

    m_2.PublicTransport.print_count();

    // Minibus arr3[4];
    // Taxi *arr4 = new Taxi[4];
    // delete[] arr4;

    Minibus_t arr3[4];
    for (int i = 0; i < 4; ++i) {
        MinibusCtor(&arr3[i]);
    }

    Taxi_t *arr4 = malloc(4 * sizeof(Taxi_t));
    for (int i = 0; i < 4; ++i) {
        TaxiCtor(&arr4[i]);
    }

    for (int i = 0; i < 4; ++i) {
        ((vtable_Taxi_t*)(arr4[4 - 1 - i].PublicTransport.vtable))->dtor((PublicTransport_t*)&arr4[4 - 1 - i]);
    }
    
    free(arr4);
    arr4 = NULL;

    // std::cout << max_func(1, 2) << "\n";
    // std::cout << max_func<int>(1, 2.0f)<< "\n";

    printf("%d\n", MAX_FUNC(1, 2));
    printf("%d\n", MAX_FUNC((int)1, (int)2.0f));

    // SpecialTaxi st;
    // taxi_display(st);

    SpecialTaxi_t st;
    SpecialTaxiCtor(&st);

    Taxi_t st_t;
    TaxiCCtor(&st_t, (Taxi_t*)&st);
    TaxiDisplayGlobal(st_t);
    ((vtable_Taxi_t*)(st_t.PublicTransport.vtable))->dtor((PublicTransport_t*)&st_t);

    // PublicConvoy *ts1 = new PublicConvoy();
    // PublicConvoy *ts2 = new PublicConvoy(*ts1);

    PublicConvoy_t *ts1 = malloc(sizeof(PublicConvoy_t));
    PublicConvoyCtor(ts1);

    PublicConvoy_t *ts2 = malloc(sizeof(PublicConvoy_t));
    PublicConvoyCCtor(ts2, ts1);

    // ts1->display();
    // ts2->display();

    ((vtable_PublicConvoy_t*)(ts1->PublicTransport.vtable))->display((PublicTransport_t*)ts1);
    ((vtable_PublicConvoy_t*)(ts2->PublicTransport.vtable))->display((PublicTransport_t*)ts2);

    // delete ts1;

    ((vtable_PublicConvoy_t*)(ts1->PublicTransport.vtable))->dtor((PublicTransport_t*)ts1);
    free(ts1);
    ts1 = NULL;

    // ts2->display();

    ((vtable_PublicConvoy_t*)(ts2->PublicTransport.vtable))->display((PublicTransport_t*)ts2);

    // delete ts2;

    ((vtable_PublicConvoy_t*)(ts2->PublicTransport.vtable))->dtor((PublicTransport_t*)ts2);
    free(ts2);
    ts2 = NULL;

    // clean-up
    
    ((vtable_SpecialTaxi_t*)(st.Taxi.PublicTransport.vtable))->dtor((PublicTransport_t*)&st);

    for (int i = 0; i < 4; ++i) {
        ((vtable_Minibus_t*)(arr3[4 - 1 - i].PublicTransport.vtable))->dtor((PublicTransport_t*)&arr3[4 - 1 - i]);
    }

    ((vtable_Minibus_t*)(m_2.PublicTransport.vtable))->dtor((PublicTransport_t*)&m_2);

    for (int i = 0; i < 3; ++i) {
        ((vtable_PublicTransport_t*)(arr2[4 - 1 - i].vtable))->dtor((PublicTransport_t*)&arr2[3 - 1 - i]);
    }

    // ((vtable_PublicTransport_t*)(publict1.vtable))->dtor(&publict1);
    // ((vtable_PublicTransport_t*)(taxi1_p.vtable))->dtor(&taxi1_p);
    // ((vtable_PublicTransport_t*)(minibus1_p.vtable))->dtor(&minibus1_p);
    ((vtable_Minibus_t*)(m.PublicTransport.vtable))->dtor((PublicTransport_t*)&m);

    return 0;
}
