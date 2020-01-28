#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#define UNUSED(x) (void)(x)

// #define MAX_FUNC(t1, t2) (((t1) > (t2)) ? (t1) : (t2))

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
void PublicTransportdisplayVoid(PublicTransport_t *const this);
int PublicTransportget_IDVoid(PublicTransport_t *const this);
static void PublicTransportprint_countVoid();

void MinibusCtor(Minibus_t *const this);
void MinibusCCtor(Minibus_t *const this, Minibus_t *const other);
void MinibusDtor(PublicTransport_t *const this);
void MinibuswashVoid(Minibus_t *const this, int minutes);
void MinibusdisplayVoid(PublicTransport_t *const this);

void TaxiCtor(Taxi_t *const this);
void TaxiCCtor(Taxi_t *const this, Taxi_t *const other);
void TaxiDtor(PublicTransport_t *const this);
void TaxidisplayVoid(PublicTransport_t *const this);

void SpecialTaxiCtor(SpecialTaxi_t *const this);
void SpecialTaxiCCtor(SpecialTaxi_t *const this, SpecialTaxi_t *const other);
void SpecialTaxiDtor(PublicTransport_t *const this);
void SpecialTaxidisplayVoid(PublicTransport_t *const this);

void PublicConvoyCtor(PublicConvoy_t *const this);
void PublicConvoyCCtor(PublicConvoy_t *const this, PublicConvoy_t *const other);
void PublicConvoyDtor(PublicTransport_t *const this);
void PublicConvoydisplayVoid(PublicTransport_t *const this);

void taxi_displayTaxi(Taxi_t s);
void print_infoPublicTransport(PublicTransport_t *a);
void print_infoVoid();
void print_infoMinibus(Minibus_t *m);
void print_infoInt(PublicTransport_t* ret_publict, int i);

/******************************************************************************/
/*** vtables init *************************************************************/
/******************************************************************************/

vtable_PublicTransport_t vtable_PublicTransport = {
    .dtor = PublicTransportDtor,
    .display = PublicTransportdisplayVoid};

vtable_Taxi_t vtable_Taxi = {
    .dtor = TaxiDtor,
    .display = TaxidisplayVoid};

vtable_Minibus_t vtable_Minibus = {
    .dtor = MinibusDtor,
    .display = MinibusdisplayVoid,
    .wash = MinibuswashVoid};

vtable_SpecialTaxi_t vtable_SpecialTaxi = {
    .dtor = SpecialTaxiDtor,
    .display = SpecialTaxidisplayVoid};

vtable_PublicConvoy_t vtable_PublicConvoy = {
    .dtor = PublicConvoyDtor,
    .display = PublicConvoydisplayVoid};

/******************************************************************************/
/*** PublicTransport methods **************************************************/
/******************************************************************************/

void PublicTransportCtor(PublicTransport_t *const this)
{
    this->vtable = &vtable_PublicTransport;

    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::Ctor() %d\n", this->m_license_plate);
}

void PublicTransportCCtor(PublicTransport_t *const this, PublicTransport_t *const other)
{
    UNUSED(other);
    this->vtable = &vtable_PublicTransport;

    ++s_count;
    this->m_license_plate = s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void PublicTransportDtor(PublicTransport_t *const this)
{
    --s_count;
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
}

void PublicTransportdisplayVoid(PublicTransport_t *const this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

int PublicTransportget_IDVoid(PublicTransport_t *const this)
{
    return this->m_license_plate;
}

static void PublicTransportprint_countVoid()
{
    printf("s_count: %d\n", s_count);
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

    this->vtable = &vtable_PublicTransport;
    PublicTransportDtor(this);
}

void MinibusdisplayVoid(PublicTransport_t *const this)
{
    Minibus_t *this_m = (Minibus_t*)this;
    printf("Minibus::display() ID: %d", PublicTransportget_IDVoid(this));
    printf(" num seats: %d\n", this_m->m_numSeats);
}

void MinibuswashVoid(Minibus_t *const this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n", minutes, PublicTransportget_IDVoid((PublicTransport_t*)this));
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

    this->vtable = &vtable_PublicTransport;
    PublicTransportDtor(this);
}

void TaxidisplayVoid(PublicTransport_t *const this)
{
    printf("Taxi::display() ID: %d\n", PublicTransportget_IDVoid(this));
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

    this->vtable = &vtable_Taxi;
    TaxiDtor(this);
}

void SpecialTaxidisplayVoid(PublicTransport_t *const this)
{
    printf("SpecialTaxi::display() ID: %d\n", PublicTransportget_IDVoid(this));
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

    this->vtable = &vtable_PublicTransport;
    PublicTransportDtor(this);
}

void PublicConvoydisplayVoid(PublicTransport_t *const this)
{
    PublicConvoy_t *this_p = (PublicConvoy_t*)this;

    ((vtable_Minibus_t*)(this_p->m_pt1->vtable))->display(this_p->m_pt1);
    ((vtable_Taxi_t*)(this_p->m_pt2->vtable))->display(this_p->m_pt2);

    MinibusdisplayVoid((PublicTransport_t*)&this_p->m_m);
    TaxidisplayVoid((PublicTransport_t*)&this_p->m_t);
}

/******************************************************************************/
/*** global functions *********************************************************/
/******************************************************************************/

void taxi_displayTaxi(Taxi_t s)
{
    TaxidisplayVoid((PublicTransport_t*)&s);
}

void print_infoPublicTransport(PublicTransport_t *a)
{
    ((vtable_PublicTransport_t*)(a->vtable))->display(a);
}

void print_infoVoid()
{
    PublicTransportprint_countVoid();
}

void print_infoMinibus(Minibus_t *m)
{
    ((vtable_Minibus_t*)(m->PublicTransport.vtable))->wash(m, 3);
}

void print_infoInt(PublicTransport_t *ret_pt, int i)
{
    UNUSED(i);
    Minibus_t ret;
    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    MinibusdisplayVoid((PublicTransport_t*)&ret);
    PublicTransportCCtor(ret_pt, (PublicTransport_t*)&ret);
    MinibusDtor((PublicTransport_t*)&ret);
}

/******************************************************************************/
/*** service functions ********************************************************/
/******************************************************************************/

PublicTransport_t *NewPublicTransport()
{
    PublicTransport_t *new = malloc(sizeof(PublicTransport_t));
    PublicTransportCtor(new);
    return new;
}

Minibus_t *NewMinibus()
{
    Minibus_t *new = malloc(sizeof(Minibus_t));
    MinibusCtor(new);
    return new;
}

Taxi_t *NewArrTaxi(size_t nmemb)
{
    size_t i = 0;
    void *new_arr = malloc(sizeof(size_t) + nmemb * sizeof(Taxi_t));
    
    *(size_t*)new_arr = nmemb;

    for (i = 0; i < nmemb; ++i)
    {
        TaxiCtor((Taxi_t*)((char*)new_arr + sizeof(size_t) + i * sizeof(Taxi_t)));
    }

    return (Taxi_t*)((char*)new_arr + sizeof(size_t));
}

void DeleteArrTaxi(Taxi_t *arr)
{
    size_t i = 0;
    size_t size = *(size_t*)((char*)arr - sizeof(size_t));

    for (i = 0; i < size; ++i)
    {
        ((vtable_Taxi_t*)(arr[size - 1 - i].PublicTransport.vtable))->dtor((PublicTransport_t*)&arr[size - 1 - i]);
    }

    free((char*)arr - sizeof(size_t));
}

Taxi_t *NewTaxi()
{
    Taxi_t *new = malloc(sizeof(Taxi_t));
    TaxiCtor(new);
    return new;
}

SpecialTaxi_t *NewSpecialTaxi()
{
    SpecialTaxi_t *new = malloc(sizeof(SpecialTaxi_t));
    SpecialTaxiCtor(new);
    return new;
}

PublicConvoy_t *NewPublicConvoy()
{
    PublicConvoy_t *new = malloc(sizeof(PublicConvoy_t));
    PublicConvoyCtor(new);
    return new;
}

PublicConvoy_t *NewPublicConvoyCopy(PublicConvoy_t *const other)
{
    PublicConvoy_t *new = malloc(sizeof(PublicConvoy_t));
    PublicConvoyCCtor(new, other);
    return new;
}

void DeletePublicTransport(PublicTransport_t *to_delete)
{
    ((vtable_PublicTransport_t*)(to_delete->vtable))->dtor((PublicTransport_t *)to_delete);
    free(to_delete);
}

void DeleteMinibus(Minibus_t *to_delete)
{
    ((vtable_Minibus_t*)(to_delete->PublicTransport.vtable))->dtor((PublicTransport_t *)to_delete);
    free(to_delete);
}

void DeleteTaxi(Taxi_t *to_delete)
{
    ((vtable_Taxi_t*)(to_delete->PublicTransport.vtable))->dtor((PublicTransport_t *)to_delete);
    free(to_delete);
}

void DeleteSpecialTaxi(SpecialTaxi_t *to_delete)
{
    ((vtable_SpecialTaxi_t*)(to_delete->Taxi.PublicTransport.vtable))->dtor((PublicTransport_t *)to_delete);
    free(to_delete);
}

void DeletePublicConvoy(PublicConvoy_t *to_delete)
{
    ((vtable_PublicConvoy_t*)(to_delete->PublicTransport.vtable))->dtor((PublicTransport_t *)to_delete);
    free(to_delete);
}

/******************************************************************************/
/*** main *********************************************************************/
/******************************************************************************/

int main()
{
    union temp_t {
        PublicTransport_t pt;
        Minibus_t m;
        Taxi_t t;
        SpecialTaxi_t st;
        PublicConvoy_t pc;
    } temp;

    // Minibus m;

    Minibus_t m;
    MinibusCtor(&m);

    // print_info(m);

    print_infoMinibus(&m);

    // print_info(3).display();

    print_infoInt(&temp.pt, 3);
    PublicTransportdisplayVoid(&temp.pt);
    ((vtable_PublicTransport_t*)(temp.pt.vtable))->dtor(&temp.pt);

    // PublicTransport *array[] = { new Minibus(), new Taxi(), new Minibus() };
    
    PublicTransport_t *array[3];
    
    array[0] = (PublicTransport_t *)NewMinibus();
    array[1] = (PublicTransport_t *)NewTaxi();
    array[2] = (PublicTransport_t *)NewMinibus();

    // for (int i = 0; i < 3; ++i) {
    //     array[i]->display();
    // }

    ((vtable_Minibus_t*)(array[0]->vtable))->display(array[0]);
    ((vtable_Taxi_t*)(array[1]->vtable))->display(array[1]);
    ((vtable_Minibus_t*)(array[2]->vtable))->display(array[2]);

    // for (int i = 0; i < 3; ++i) {
    //     delete array[i];
    // }

    DeleteMinibus((Minibus_t*)array[0]);
    DeleteTaxi((Taxi_t*)array[1]);
    DeleteMinibus((Minibus_t*)array[2]);

    // PublicTransport arr2[] = { Minibus(), Taxi(), PublicTransport() };
    PublicTransport_t arr2[3];
    
    MinibusCtor(&temp.m);
    PublicTransportCCtor(&arr2[0], (PublicTransport_t*)&temp.m);
    ((vtable_Minibus_t*)(temp.m.PublicTransport.vtable))->dtor((PublicTransport_t*)&temp.m);

    TaxiCtor(&temp.t);
    PublicTransportCCtor(&arr2[1], (PublicTransport_t*)&temp.t);
    ((vtable_Taxi_t*)(temp.t.PublicTransport.vtable))->dtor((PublicTransport_t*)&temp.t);

    PublicTransportCtor(&arr2[2]);

    // for (int i = 0; i < 3; ++i) {
    //     arr2[i].display();
    // }

    PublicTransportdisplayVoid(&arr2[0]);
    PublicTransportdisplayVoid(&arr2[1]);
    PublicTransportdisplayVoid(&arr2[2]);
  
    // print_info(arr2[0]);

    print_infoPublicTransport(&arr2[0]);

    // PublicTransport::print_count();

    PublicTransportprint_countVoid();

    // Minibus m2;

    Minibus_t m_2;
    MinibusCtor(&m_2);

    // m2.print_count();

    PublicTransportprint_countVoid();

    // Minibus arr3[4];

    Minibus_t arr3[4];
    
    MinibusCtor(&arr3[0]);
    MinibusCtor(&arr3[1]);
    MinibusCtor(&arr3[2]);
    MinibusCtor(&arr3[3]);

    // Taxi *arr4 = new Taxi[4];
    // delete[] arr4;

    Taxi_t *arr4 = NewArrTaxi(4);
    DeleteArrTaxi(arr4);

    // std::cout << max_func(1, 2) << "\n";
    // std::cout << max_func<int>(1, 2.0f)<< "\n";

    printf("%d\n", (((1) > (2)) ? (1) : (2)));
    printf("%d\n", ((1) > ((int)2.0f)) ? (1) : ((int)2.0f));

    // SpecialTaxi st;
    // taxi_display(st);

    SpecialTaxi_t st;
    SpecialTaxiCtor(&st);

    TaxiCCtor(&temp.t, (Taxi_t*)&st);
    taxi_displayTaxi(temp.t);
    ((vtable_Taxi_t*)(temp.t.PublicTransport.vtable))->dtor((PublicTransport_t*)&temp.t);

    // PublicConvoy *ts1 = new PublicConvoy();
    // PublicConvoy *ts2 = new PublicConvoy(*ts1);

    PublicConvoy_t *ts1 = NewPublicConvoy();
    PublicConvoy_t *ts2 = NewPublicConvoyCopy(ts1);

    // ts1->display();
    // ts2->display();

    ((vtable_PublicConvoy_t*)(ts1->PublicTransport.vtable))->display((PublicTransport_t*)ts1);
    ((vtable_PublicConvoy_t*)(ts2->PublicTransport.vtable))->display((PublicTransport_t*)ts2);

    // delete ts1;

    DeletePublicConvoy(ts1);

    // ts2->display();

    ((vtable_PublicConvoy_t*)(ts2->PublicTransport.vtable))->display((PublicTransport_t*)ts2);

    // delete ts2;

    DeletePublicConvoy(ts2);

    // clean-up
    
    ((vtable_SpecialTaxi_t*)(st.Taxi.PublicTransport.vtable))->dtor((PublicTransport_t*)&st);

    ((vtable_Minibus_t*)(arr3[3].PublicTransport.vtable))->dtor((PublicTransport_t*)&arr3[3]);
    ((vtable_Minibus_t*)(arr3[2].PublicTransport.vtable))->dtor((PublicTransport_t*)&arr3[2]);
    ((vtable_Minibus_t*)(arr3[1].PublicTransport.vtable))->dtor((PublicTransport_t*)&arr3[1]);
    ((vtable_Minibus_t*)(arr3[0].PublicTransport.vtable))->dtor((PublicTransport_t*)&arr3[0]);

    ((vtable_Minibus_t*)(m_2.PublicTransport.vtable))->dtor((PublicTransport_t*)&m_2);

    ((vtable_PublicTransport_t*)(arr2[2].vtable))->dtor((PublicTransport_t*)&arr2[2]);
    ((vtable_PublicTransport_t*)(arr2[1].vtable))->dtor((PublicTransport_t*)&arr2[1]);
    ((vtable_PublicTransport_t*)(arr2[0].vtable))->dtor((PublicTransport_t*)&arr2[0]);

    ((vtable_Minibus_t*)(m.PublicTransport.vtable))->dtor((PublicTransport_t*)&m);

    return 0;
}
