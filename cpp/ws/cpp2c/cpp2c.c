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
    int (*get_id)(PublicTransport_t *const this);
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
    void (*dtor)(PublicTransport_t *const this);
    void (*display)(PublicTransport_t *const this);
} vtable_PublicTransport_t;

typedef struct {
    void (*dtor)(PublicTransport_t *const this);
    void (*display)(PublicTransport_t *const this);
} vtable_Taxi_t;

typedef struct {
    void (*dtor)(PublicTransport_t *const this);
    void (*display)(PublicTransport_t *const this);
    void (*wash)(Minibus_t *const this, int minutes);
} vtable_Minibus_t;

typedef struct {
    void (*dtor)(PublicTransport_t *const this);
    void (*display)(PublicTransport_t *const this);
} vtable_SpecialTaxi_t;

typedef struct {
    void (*dtor)(PublicTransport_t *const this);
    void (*display)(PublicTransport_t *const this);
} vtable_PublicConvoy_t;

/******************************************************************************/
/*** function declarations ****************************************************/
/******************************************************************************/

void PublicTransportCtor(PublicTransport_t *const this);
void PublicTransportCCtor(PublicTransport_t *const this, PublicTransport_t *const other);
void PublicTransportDtor(PublicTransport_t *const this);
void PublicTransportDisplay(PublicTransport_t *const this);

void TaxiCtor(Taxi_t *const this);
void TaxiCCtor(Taxi_t *const this, Taxi_t *const other);
void TaxiDtor(PublicTransport_t *const this);
void TaxiDisplay(PublicTransport_t *const this);

void MinibusCtor(Minibus_t *const this);
void MinibusCCtor(Minibus_t *const this, Minibus_t *const other);
void MinibusDtor(PublicTransport_t *const this);
void MinibusWash(Minibus_t *const this, int minutes);
void MinibusDisplay(PublicTransport_t *const this);

void SpecialTaxiCtor(SpecialTaxi_t *const this);
void SpecialTaxiCCtor(SpecialTaxi_t *const this, SpecialTaxi_t *const other);
void SpecialTaxiDtor(PublicTransport_t *const this);
void SpecialTaxiDisplay(PublicTransport_t *const this);

void PublicConvoyCtor(PublicConvoy_t *const this);
void PublicConvoyCCtor(PublicConvoy_t *const this, PublicConvoy_t *const other);
void PublicConvoyDtor(PublicTransport_t *const this);
void PublicConvoyDisplay(PublicTransport_t *const this);

int GetID(PublicTransport_t *const this);
static void PrintCount();
void TaxiDisplayTaxi(Taxi_t s);
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
/*** PublicTransport methods **************************************************/
/******************************************************************************/

void PublicTransportCtor(PublicTransport_t *const this)
{
    this->vtable = &vtable_PublicTransport;
    this->print_count = PrintCount;
    this->get_id = GetID;

    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::Ctor() %d\n", this->m_license_plate);
}

void PublicTransportCCtor(PublicTransport_t *const this, PublicTransport_t *const other)
{
    UNUSED(other);
    this->vtable = &vtable_PublicTransport;
    this->print_count = PrintCount;
    this->get_id = GetID;

    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void PublicTransportDtor(PublicTransport_t *const this)
{
    --s_count;
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
}

void PublicTransportDisplay(PublicTransport_t *const this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

int GetID(PublicTransport_t *const this)
{
    return this->m_license_plate;
}

/* static member function - global in c */
static void PrintCount()
{
    printf("s_count: %d\n", s_count);
}

/******************************************************************************/
/*** Taxi methods *************************************************************/
/******************************************************************************/

void TaxiCtor(Taxi_t *const this)
{
    PublicTransportCtor((PublicTransport_t*)this);
    this->PublicTransport.vtable = &vtable_Taxi;

    printf("Taxi::Ctor()\n");
}

void TaxiCCtor(Taxi_t *const this, Taxi_t *const other)
{
    PublicTransportCCtor((PublicTransport_t*)this,(PublicTransport_t*)other);
    this->PublicTransport.vtable = &vtable_Taxi;

    printf("Taxi::CCtor()\n");
}

void TaxiDtor(PublicTransport_t *const this)
{
    printf("Taxi::Dtor()\n");

    PublicTransportDtor(this);
}

void TaxiDisplay(PublicTransport_t *const this)
{
    printf("Taxi::display() ID: %d\n", GetID(this));
}

/******************************************************************************/
/*** Minibus methods **********************************************************/
/******************************************************************************/

void MinibusCtor(Minibus_t *const this)
{
    PublicTransportCtor((PublicTransport_t*)this);
    this->PublicTransport.vtable = &vtable_Minibus;

    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void MinibusCCtor(Minibus_t *const this, Minibus_t *const other)
{
    PublicTransportCCtor((PublicTransport_t*)this,(PublicTransport_t*)other);
    this->PublicTransport.vtable = &vtable_Minibus;

    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void MinibusDtor(PublicTransport_t *const this)
{
    printf("Minibus::Dtor()\n");

    PublicTransportDtor(this);
}

void MinibusDisplay(PublicTransport_t *const this)
{
    Minibus_t *this_m = (Minibus_t*)this;
    printf("Minibus::display() ID: %d", GetID(this));
    printf(" num seats: %d\n", this_m->m_numSeats);
}

void MinibusWash(Minibus_t *const this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n", minutes, GetID((PublicTransport_t*)this));
}

/******************************************************************************/
/*** SpecialTaxi methods ******************************************************/
/******************************************************************************/

void SpecialTaxiCtor(SpecialTaxi_t *const this)
{
    TaxiCtor((Taxi_t*)this);
    this->Taxi.PublicTransport.vtable = &vtable_SpecialTaxi;

    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi_t *const this, SpecialTaxi_t *const other)
{
    TaxiCCtor((Taxi_t*)this,(Taxi_t*)other);
    this->Taxi.PublicTransport.vtable = &vtable_SpecialTaxi;

    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxiDtor(PublicTransport_t *const this)
{
    printf("SpecialTaxi::Dtor()\n");

    TaxiDtor(this);
}

void SpecialTaxiDisplay(PublicTransport_t *const this)
{
    printf("SpecialTaxi::display() ID: %d\n", GetID(this));
}

/******************************************************************************/
/*** PublicConvoy methods *****************************************************/
/******************************************************************************/

void PublicConvoyCtor(PublicConvoy_t *const this)
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

void PublicConvoyCCtor(PublicConvoy_t *const this, PublicConvoy_t *const other)
{
    PublicTransportCCtor((PublicTransport_t*)this,(PublicTransport_t*)other);
    this->PublicTransport.vtable = &vtable_PublicConvoy;

    this->m_pt1 = other->m_pt1;
    this->m_pt2 = other->m_pt2;
    MinibusCCtor(&(this->m_m), &(other->m_m));
    TaxiCCtor(&(this->m_t), &(other->m_t));
}

void PublicConvoyDtor(PublicTransport_t *const this)
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

void PublicConvoyDisplay(PublicTransport_t *const this)
{
    PublicConvoy_t *this_p = (PublicConvoy_t*)this;

    ((vtable_Minibus_t*)(this_p->m_pt1->vtable))->display(this_p->m_pt1);
    ((vtable_Taxi_t*)(this_p->m_pt2->vtable))->display(this_p->m_pt2);

    MinibusDisplay((PublicTransport_t*)&this_p->m_m);
    TaxiDisplay((PublicTransport_t*)&this_p->m_t);
    // ((vtable_Minibus_t*)(this_p->m_m.PublicTransport.vtable))->display((PublicTransport_t*)&this_p->m_m);
    // ((vtable_Taxi_t*)(this_p->m_t.PublicTransport.vtable))->display((PublicTransport_t*)&this_p->m_t);
}

/******************************************************************************/
/*** global functions *********************************************************/
/******************************************************************************/

void TaxiDisplayTaxi(Taxi_t s)
{
    TaxiDisplay((PublicTransport_t*)&s);
    // ((vtable_Taxi_t*)(s.PublicTransport.vtable))->display((PublicTransport_t*)&s);
}

void PrintInfoPublicTransport(PublicTransport_t *a)
{
    ((vtable_PublicTransport_t*)(a->vtable))->display(a);
}

void PrintInfoVoid()
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

    printf("%d\n", (((1) > (2)) ? (1) : (2)));
    printf("%d\n", (((int)1) > ((int)2.0f)) ? ((int)1) : ((int)2.0f));

    // SpecialTaxi st;
    // taxi_display(st);

    SpecialTaxi_t st;
    SpecialTaxiCtor(&st);

    Taxi_t st_t;
    TaxiCCtor(&st_t, (Taxi_t*)&st);
    TaxiDisplayTaxi(st_t);
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
