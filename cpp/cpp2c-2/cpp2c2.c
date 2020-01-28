#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

enum {dtor = 0, display = 1, wash = 2} vtable_index_t;
int s_count = 0;

typedef struct PublicTransport PublicTransport_t;
typedef struct Minibus Minibus_t;
typedef struct Taxi Taxi_t;
typedef struct SpecialTaxi SpecialTaxi_t;
typedef struct PublicConvoy PublicConvoy_t;

/******************************************************************************/
/**** declarations ************************************************************/
/******************************************************************************/

void PublicTransport_Ctor(PublicTransport_t *const this);
void PublicTransport_CCtor(PublicTransport_t *const this, PublicTransport_t *const other);
void PublicTransport_Dtor(PublicTransport_t *const this);
void PublicTransport_display_void(PublicTransport_t *const this);
void PublicTransport_print_count_void(void);
int PublicTransport_get_ID_void(PublicTransport_t *const this);

void Minibus_Ctor(Minibus_t *const this);
void Minibus_CCtor(Minibus_t *const this, Minibus_t *const other);
void Minibus_Dtor(Minibus_t *const this);
void Minibus_display_void(Minibus_t *const this);
void Minibus_wash_int(Minibus_t *const this, int minutes);

void Taxi_Ctor(Taxi_t *const this);
void Taxi_CCtor(Taxi_t *const this, Taxi_t *const other);
void Taxi_Dtor(Taxi_t *const this);
void Taxi_display_void(Taxi_t *const this);

void SpecialTaxi_Ctor(SpecialTaxi_t *const this);
void SpecialTaxi_CCtor(SpecialTaxi_t *const this, SpecialTaxi_t *const other);
void SpecialTaxi_Dtor(SpecialTaxi_t *const this);
void SpecialTaxi_display_void(SpecialTaxi_t *const this);

void PublicConvoy_Ctor(PublicConvoy_t *const this);
void PublicConvoy_CCtor(PublicConvoy_t *const this, PublicConvoy_t *const other);
void PublicConvoy_Dtor(PublicConvoy_t *const this);
void PublicConvoy_display_void(PublicConvoy_t *const this);

void print_info_PublicTransport(PublicTransport_t *a);
void print_info_void();
void print_infoMinibus(Minibus_t *m);
void print_info_int(PublicTransport_t *pt, int i);
void taxi_display_Taxi(Taxi_t *s);

Minibus_t *NewMinibus();
void DeleteMinibus(Minibus_t *const this);
Taxi_t *NewTaxi();
void DeleteTaxi(Taxi_t *const this);
PublicConvoy_t *NewPublicConvoy();
PublicConvoy_t *NewCCtorPublicConvoy(PublicConvoy_t *const other);
void DeletePublicConvoy(PublicConvoy_t *const this);
Taxi_t *NewArrTaxi(size_t size);
void DeleteArrTaxi(Taxi_t *arr);

/******************************************************************************/
/**** classes definitions *****************************************************/
/******************************************************************************/

struct PublicTransport
{
    void *(**vtable)(void*);
    int m_license_plate;
};

struct Minibus
{
    PublicTransport_t PT; // inherits PublicTransport
    int m_numSeats;
};

struct Taxi
{
    PublicTransport_t PT; // inherits PublicTransport
};

struct SpecialTaxi
{
    Taxi_t T; // inherits Taxi
};

struct PublicConvoy
{
    PublicTransport_t PT; // inherits PublicTransport

    PublicTransport_t *m_pt1;
    PublicTransport_t *m_pt2;
    Minibus_t m_m;
    Taxi_t m_t;
};

void *(*PublicTransport_vtable[2])(void *) = {
    (void*(*)(void*))PublicTransport_Dtor,
    (void*(*)(void*))PublicTransport_display_void};

void *(*Minibus_vtable[3])(void *) = {
    (void*(*)(void*))Minibus_Dtor,
    (void*(*)(void*))Minibus_display_void,
    (void*(*)(void*))Minibus_wash_int};

void *(*Taxi_vtable[2])(void *) = {
    (void*(*)(void*))Taxi_Dtor,
    (void*(*)(void*))Taxi_display_void};

void *(*SpecialTaxi_vtable[2])(void *) = {
    (void*(*)(void*))SpecialTaxi_Dtor,
    (void*(*)(void*))SpecialTaxi_display_void};

void *(*PublicConvoy_vtable[2])(void *) = {
    (void*(*)(void*))PublicConvoy_Dtor,
    (void*(*)(void*))PublicConvoy_display_void};

/******************************************************************************/
/**** PublicTransport methods *************************************************/
/******************************************************************************/

void PublicTransport_Ctor(PublicTransport_t *const this)
{
    this->vtable = PublicTransport_vtable;

    this->m_license_plate = ++s_count;
    printf("PublicTransport::Ctor() %d\n", this->m_license_plate);
}

void PublicTransport_CCtor(PublicTransport_t *const this, PublicTransport_t *const other)
{
    (void)(other);
    this->vtable = PublicTransport_vtable;

    this->m_license_plate = ++s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void PublicTransport_Dtor(PublicTransport_t *const this)
{
    --s_count;
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
}

void PublicTransport_display_void(PublicTransport_t *const this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void PublicTransport_print_count_void(void)
{
    printf("s_count: : %d\n", s_count);
}

int PublicTransport_get_ID_void(PublicTransport_t *const this)
{
    return this->m_license_plate;
}

/******************************************************************************/
/**** Minibus methods *********************************************************/
/******************************************************************************/

void Minibus_Ctor(Minibus_t *const this)
{
    PublicTransport_Ctor(&this->PT);
    ((PublicTransport_t*)this)->vtable = Minibus_vtable;

    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void Minibus_CCtor(Minibus_t *const this, Minibus_t *const other)
{
    PublicTransport_CCtor(&this->PT, &other->PT);
    ((PublicTransport_t*)this)->vtable = Minibus_vtable;

    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void Minibus_Dtor(Minibus_t *const this)
{
    printf("Minibus::Dtor()\n");

    ((PublicTransport_t*)this)->vtable = PublicTransport_vtable;
    ((void (*)(PublicTransport_t*))this->PT.vtable[dtor])((PublicTransport_t*)this);
}

void Minibus_display_void(Minibus_t *const this)
{
    printf("Minibus::display() ID: %d",
    PublicTransport_get_ID_void((PublicTransport_t*)this));

    printf(" num seats: %d\n", this->m_numSeats);
}

void Minibus_wash_int(Minibus_t *const this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n",
    minutes, PublicTransport_get_ID_void(&this->PT));
}

/******************************************************************************/
/**** Taxi methods ************************************************************/
/******************************************************************************/

void Taxi_Ctor(Taxi_t *const this)
{
    PublicTransport_Ctor(&this->PT);
    ((PublicTransport_t*)this)->vtable = Taxi_vtable;

    printf("Taxi::Ctor()\n");
}

void Taxi_CCtor(Taxi_t *const this, Taxi_t *const other)
{
    PublicTransport_CCtor(&this->PT, &other->PT);
    ((PublicTransport_t*)this)->vtable = Taxi_vtable;

    printf("Taxi::CCtor()\n");
}

void Taxi_Dtor(Taxi_t *const this)
{
    printf("Taxi::Dtor()\n");

    ((PublicTransport_t*)this)->vtable = PublicTransport_vtable;
    ((void (*)(PublicTransport_t*))this->PT.vtable[dtor])((PublicTransport_t*)this);
}

void Taxi_display_void(Taxi_t *const this)
{
    printf("Taxi::display() ID: %d \n",
    PublicTransport_get_ID_void(&this->PT));
}

/******************************************************************************/
/**** SpecialTaxi methods *****************************************************/
/******************************************************************************/

void SpecialTaxi_Ctor(SpecialTaxi_t *const this)
{
    Taxi_Ctor(&this->T);
    ((PublicTransport_t*)this)->vtable = SpecialTaxi_vtable;

    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxi_CCtor(SpecialTaxi_t *const this, SpecialTaxi_t *const other)
{
    Taxi_CCtor(&this->T, &other->T);
    ((PublicTransport_t*)this)->vtable = SpecialTaxi_vtable;

    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxi_Dtor(SpecialTaxi_t *const this)
{
    printf("SpecialTaxi::Dtor()\n");

    ((PublicTransport_t*)this)->vtable = Taxi_vtable;
    ((void (*)(Taxi_t*))this->T.PT.vtable[dtor])((Taxi_t*)this);
}

void SpecialTaxi_display_void(SpecialTaxi_t *const this)
{
    printf("Taxi::display() ID: %d ",
    PublicTransport_get_ID_void(&this->T.PT));
}

/******************************************************************************/
/**** PublicConvoy methods ****************************************************/
/******************************************************************************/

void PublicConvoy_Ctor(PublicConvoy_t *const this)
{
    PublicTransport_Ctor(&this->PT);
    ((PublicTransport_t*)this)->vtable = PublicConvoy_vtable;

    this->m_pt1 = (PublicTransport_t*)NewMinibus();
    this->m_pt2 = (PublicTransport_t*)NewTaxi();

    Minibus_Ctor(&this->m_m);
    Taxi_Ctor(&this->m_t);
}

void PublicConvoy_CCtor(PublicConvoy_t *const this, PublicConvoy_t *const other)
{
    PublicTransport_CCtor(&this->PT, &other->PT);
    ((PublicTransport_t*)this)->vtable = PublicConvoy_vtable;

    this->m_pt1 = other->m_pt1;
    this->m_pt2 = other->m_pt2;

    Minibus_CCtor(&(this->m_m), &(other->m_m));
    Taxi_CCtor(&(this->m_t), &(other->m_t));
}

void PublicConvoy_Dtor(PublicConvoy_t *const this)
{
    DeleteMinibus((Minibus_t*)this->m_pt1);
    DeleteTaxi((Taxi_t*)this->m_pt2);

    ((void (*)(Taxi_t*))this->m_t.PT.vtable[dtor])(&this->m_t);
    ((void (*)(Minibus_t*))this->m_m.PT.vtable[dtor])(&this->m_m);

    ((PublicTransport_t*)this)->vtable = PublicTransport_vtable;
    ((void (*)(PublicTransport_t*))this->PT.vtable[dtor])((PublicTransport_t*)this);
}

void PublicConvoy_display_void(PublicConvoy_t *const this)
{
    ((void (*)(Minibus_t*))this->m_pt1->vtable[display])((Minibus_t*)this->m_pt1);   
    ((void (*)(Taxi_t*))this->m_pt2->vtable[display])((Taxi_t*)this->m_pt2);

    Minibus_display_void(&this->m_m);
    Taxi_display_void(&this->m_t);
}

/******************************************************************************/
/**** global functions ********************************************************/
/******************************************************************************/

void print_info_PublicTransport(PublicTransport_t *a)
{
    ((void (*)(PublicTransport_t*))a->vtable[display])((PublicTransport_t*)a);
}

void print_info_void()
{
    printf("s_count: %d\n", s_count);
}

void print_infoMinibus(Minibus_t *m)
{
    ((void (*)(Minibus_t*, int))m->PT.vtable[wash])(m, 3);
}

void print_info_int(PublicTransport_t *pt, int i)
{
    (void)(i);
    Minibus_t ret;
    Minibus_Ctor(&ret);
    printf("print_info(int i)\n");
    Minibus_display_void(&ret);
    PublicTransport_CCtor(pt, (PublicTransport_t*)&ret);
    Minibus_Dtor(&ret);
}

void taxi_display_Taxi(Taxi_t *s)
{
    Taxi_display_void(s);
}

/******************************************************************************/
/**** Service functions *******************************************************/
/******************************************************************************/

Minibus_t *NewMinibus()
{
    Minibus_t *new = malloc(sizeof(Minibus_t));
    Minibus_Ctor(new);
    return new;  
}

void DeleteMinibus(Minibus_t *const this)
{
    ((void (*)(Minibus_t*))this->PT.vtable[dtor])((Minibus_t*)this);
    free(this);  
}

Taxi_t *NewTaxi()
{
    Taxi_t *new = malloc(sizeof(Taxi_t));
    Taxi_Ctor(new);
    return new;  
}

void DeleteTaxi(Taxi_t *const this)
{
    ((void (*)(Taxi_t*))this->PT.vtable[dtor])((Taxi_t*)this);
    free(this);  
}

PublicConvoy_t *NewPublicConvoy()
{
    PublicConvoy_t *new = malloc(sizeof(PublicConvoy_t));
    PublicConvoy_Ctor(new);
    return new;  
}

PublicConvoy_t *NewCCtorPublicConvoy(PublicConvoy_t *const other)
{
    PublicConvoy_t *new = malloc(sizeof(PublicConvoy_t));
    PublicConvoy_CCtor(new, other);
    return new;
}

void DeletePublicConvoy(PublicConvoy_t *const this)
{
    ((void (*)(PublicConvoy_t*))this->PT.vtable[dtor])((PublicConvoy_t*)this);
    free(this);  
}

Taxi_t *NewArrTaxi(size_t size)
{
    size_t i = 0;

    void *new_arr = malloc(size * sizeof(Taxi_t) + sizeof(size_t));
    *(size_t*)new_arr = size;

    new_arr = (char*)new_arr + sizeof(size_t);

    for (i = 0; i < size; ++i)
    {
        Taxi_Ctor((Taxi_t*)new_arr + i);
    }

    return new_arr;
}

void DeleteArrTaxi(Taxi_t *arr)
{
    size_t i = 0;
    size_t size = *(size_t*)((char*)arr - sizeof(size_t));

    for (i = 0; i < size; ++i)
    {
        ((void (*)(Taxi_t*))arr[size - 1 - i].PT.vtable[dtor])(&arr[size - 1 - i]);
    }

    free((char*)arr - sizeof(size_t));
}

/******************************************************************************/
/**** main ********************************************************************/
/******************************************************************************/

int main()
{
    union {
        PublicTransport_t pt;
        Minibus_t m;
        Taxi_t t;
        SpecialTaxi_t st;
        PublicConvoy_t pc;
    } temp;

    // Minibus m;

    Minibus_t m;
    Minibus_Ctor(&m);

    // print_info(m);

    print_infoMinibus(&m);

    // print_info(3).display();

    // PublicTransport_Ctor(&temp.pt);
    print_info_int(&temp.pt, 3);
    PublicTransport_display_void(&temp.pt);
    PublicTransport_Dtor(&temp.pt);

    // PublicTransport *array[] = { new Minibus(), new Taxi(), new Minibus() };

    PublicTransport_t *array[3];

    array[0] = (PublicTransport_t*)NewMinibus();
    array[1] = (PublicTransport_t*)NewTaxi();
    array[2] = (PublicTransport_t*)NewMinibus();

    // for (int i = 0; i < 3; ++i) {
    //     array[i]->display();
    // }

    ((void (*)(Minibus_t*))array[0]->vtable[display])((Minibus_t*)array[0]);
    ((void (*)(Taxi_t*))array[1]->vtable[display])((Taxi_t*)array[1]);
    ((void (*)(Minibus_t*))array[2]->vtable[display])((Minibus_t*)array[2]);

    // for (int i = 0; i < 3; ++i) {
    //     delete array[i];
    // }

    DeleteMinibus((Minibus_t*)array[0]);
    DeleteTaxi((Taxi_t*)array[1]);
    DeleteMinibus((Minibus_t*)array[2]);

    // PublicTransport arr2[] = { Minibus(), Taxi(), PublicTransport() };

    PublicTransport_t arr2[3];

    Minibus_Ctor(&temp.m);
    PublicTransport_CCtor(&arr2[0], (PublicTransport_t*)&temp.m);
    Minibus_Dtor(&temp.m);

    Taxi_Ctor(&temp.t);
    PublicTransport_CCtor(&arr2[1], (PublicTransport_t*)&temp.t);
    Taxi_Dtor(&temp.t);

    PublicTransport_Ctor(&arr2[2]);

    // for (int i = 0; i < 3; ++i) {
    //     arr2[i].display();
    // }

    PublicTransport_display_void(&arr2[0]);
    PublicTransport_display_void(&arr2[1]);
    PublicTransport_display_void(&arr2[2]);

    // print_info(arr2[0]);

    print_info_PublicTransport(&arr2[0]);

    // PublicTransport::print_count();
    // Minibus m2;
    // m2.print_count();

    PublicTransport_print_count_void();

    Minibus_t m_2;
    Minibus_Ctor(&m_2);

    PublicTransport_print_count_void();

    // Minibus arr3[4];

    Minibus_t arr3[4];
    Minibus_Ctor(&arr3[0]);
    Minibus_Ctor(&arr3[1]);
    Minibus_Ctor(&arr3[2]);
    Minibus_Ctor(&arr3[3]);

    // Taxi *arr4 = new Taxi[4];
    // delete[] arr4;

    Taxi_t *arr4 = NewArrTaxi(4);
    DeleteArrTaxi(arr4);

    // std::cout << max_func(1, 2) << "\n";
    // std::cout << max_func<int>(1, 2.0f)<< "\n";

    printf("%d\n", ((1) > (2) ? (1) : (2)));
    printf("%d\n", ((1) > (int)(2) ? (1) : (int)(2)));

    // SpecialTaxi st;
    // taxi_display(st);

    SpecialTaxi_t st;
    SpecialTaxi_Ctor(&st);

    Taxi_CCtor(&temp.t, (Taxi_t*)&st);
    taxi_display_Taxi(&temp.t);
    Taxi_Dtor(&temp.t);

    // PublicConvoy *ts1 = new PublicConvoy();
    // PublicConvoy *ts2 = new PublicConvoy(*ts1);

    PublicConvoy_t *ts1 = NewPublicConvoy();
    PublicConvoy_t *ts2 = NewCCtorPublicConvoy(ts1);

    // ts1->display();
    // ts2->display();

    ((void (*)(PublicConvoy_t*))ts1->PT.vtable[display])((PublicConvoy_t*)ts1);
    ((void (*)(PublicConvoy_t*))ts2->PT.vtable[display])((PublicConvoy_t*)ts2);

    // delete ts1;

    DeletePublicConvoy(ts1);

    // ts2->display(); 

    ((void (*)(PublicConvoy_t*))ts2->PT.vtable[display])((PublicConvoy_t*)ts2);

    // delete ts2;

    DeletePublicConvoy(ts2);

    // clean-up

    ((void (*)(SpecialTaxi_t*))st.T.PT.vtable[dtor])((SpecialTaxi_t*)&st);

    ((void (*)(Minibus_t*))arr3[3].PT.vtable[dtor])((Minibus_t*)&arr3[3]);
    ((void (*)(Minibus_t*))arr3[2].PT.vtable[dtor])((Minibus_t*)&arr3[2]);
    ((void (*)(Minibus_t*))arr3[1].PT.vtable[dtor])((Minibus_t*)&arr3[1]);
    ((void (*)(Minibus_t*))arr3[0].PT.vtable[dtor])((Minibus_t*)&arr3[0]);

    ((void (*)(Minibus_t*))m_2.PT.vtable[dtor])((Minibus_t*)&m_2);

    ((void (*)(Minibus_t*))arr2[2].vtable[dtor])((Minibus_t*)&arr2[2]);
    ((void (*)(Minibus_t*))arr2[1].vtable[dtor])((Minibus_t*)&arr2[1]);
    ((void (*)(Minibus_t*))arr2[0].vtable[dtor])((Minibus_t*)&arr2[0]);

    ((void (*)(Minibus_t*))m.PT.vtable[dtor])((Minibus_t*)&m);

    return 0;
}