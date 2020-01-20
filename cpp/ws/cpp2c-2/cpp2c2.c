#include "stdio.h"

enum {dtor = 0, display = 1, wash = 2} vtable_index_t;
int s_count = 0;

typedef struct PublicTransport PublicTransport_t;
typedef struct Minibus Minibus_t;
typedef struct Taxi Taxi_t;
typedef struct SpecialTaxi SpecialTaxi_t;
typedef struct PublicConvoy PublicConvoy_t;

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
    (generic_fp)Taxi_Dtor,
    (generic_fp)Taxi_display_void};

void *(*SpecialTaxi_vtable[2])(void *) = {
    (generic_fp)SpecialTaxi_vtable_Dtor,
    (generic_fp)SpecialTaxi_vtable_display_void};

void *(*PublicConvoy_vtable[2])(void *) = {
    (generic_fp)PublicConvoy_Dtor,
    (generic_fp)PublicConvoy_display_void};

/******************************************************************************/
/**** PublicTransport methods *************************************************/
/******************************************************************************/

void PublicTransport_Ctor(PublicTransport_t *this)
{
    this->vtable = PublicTransport_vtable;

    this->m_license_plate = ++s_count;
    printf("PublicTransport::Ctor() %d\n", this->m_license_plate);
}

void PublicTransport_CCtor(PublicTransport_t *this, PublicTransport_t *other)
{
    this->vtable = PublicTransport_vtable;

    this->m_license_plate = ++s_count;
    printf("PublicTransport::Ctor() %d\n", this->m_license_plate);
}

void PublicTransport_Dtor(PublicTransport_t *this)
{
    --s_count;
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
}

void PublicTransport_display_void(PublicTransport_t *this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

void PublicTransport_print_count_void(void)
{
    printf("s_count: : %d\n", s_count);
}

int PublicTransport_get_ID_void(PublicTransport_t *this)
{
    return this->m_license_plate;
}

/******************************************************************************/
/**** Minibus methods *********************************************************/
/******************************************************************************/

void Minibus_Ctor(Minibus_t *this)
{
    PublicTransport_Ctor(&this->PT);
    ((PublicTransport_t*)this)->vtable = Minibus_vtable;

    this->m_numSeats = 20;
    printf("Minibus::Ctor\n");
}

void Minibus_CCtor(Minibus_t *this, Minibus_t *other)
{
    PublicTransport_CCtor(&this->PT, &other->PT);
    ((PublicTransport_t*)this)->vtable = Minibus_vtable;

    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void Minibus_Dtor(Minibus_t *this)
{
    printf("Minibus::Dtor()\n");

    ((PublicTransport_t*)this)->vtable = PublicTransport_vtable;
    (void (*)(PublicTransport_t*))this->PT.vtable[dtor]((PublicTransport_t*)this);
}

void Minibus_display_void(Minibus_t *this)
{
    printf("Minibus::display() ID: %d ",
    PublicTransport_get_ID_void((PublicTransport_t*)this));

    printf(" num seats: %d\n", this->m_numSeats);
}

void Minibus_wash_int(Minibus_t *this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n",
    minutes, PublicTransport_get_ID_void(&this->PT));
}

/******************************************************************************/
/**** Taxi methods ************************************************************/
/******************************************************************************/

void Taxi_Ctor(Taxi_t *this)
{
    PublicTransport_Ctor(&this->PT);
    ((PublicTransport_t*)this)->vtable = Taxi_vtable;

    printf("Taxi::Ctor\n");
}

void Taxi_CCtor(Taxi_t *this, Taxi_t *other)
{
    PublicTransport_CCtor(&this->PT, &other->PT);
    ((PublicTransport_t*)this)->vtable = Taxi_vtable;

    printf("Taxi::CCtor()\n");
}

void Taxi_Dtor(Taxi_t *this)
{
    printf("Taxi::Dtor()\n");

    ((PublicTransport_t*)this)->vtable = PublicTransport_vtable;
    (void (*)(PublicTransport_t*))this->PT.vtable[dtor]((PublicTransport_t*)this);
}

void Taxi_display_void(Taxi_t *this)
{
    printf("Taxi::display() ID: %d ",
    PublicTransport_get_ID_void(&this->PT));
}

/******************************************************************************/
/**** SpecialTaxi methods *****************************************************/
/******************************************************************************/

void SpecialTaxi_Ctor(SpecialTaxi_t *this)
{
    Taxi_Ctor(&this->T);
    ((PublicTransport_t*)this)->vtable = SpecialTaxi_vtable;

    printf("SpecialTaxi::Ctor\n");
}

void SpecialTaxi_CCtor(SpecialTaxi_t *this, SpecialTaxi_t *other)
{
    Taxi_CCtor(&this->T, &other->T);
    ((PublicTransport_t*)this)->vtable = SpecialTaxi_vtable;

    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxi_Dtor(SpecialTaxi_t *this)
{
    printf("SpecialTaxi::Dtor()\n");

    ((PublicTransport_t*)this)->vtable = Taxi_vtable;
    (void (*)(Taxi_t*))this->T.PT.vtable[dtor]((Taxi_t*)this);
}

void SpecialTaxi_display_void(SpecialTaxi_t *this)
{
    printf("Taxi::display() ID: %d ",
    PublicTransport_get_ID_void(&this->T.PT));
}

/******************************************************************************/
/**** PublicConvoy methods ****************************************************/
/******************************************************************************/

void PublicConvoy_Ctor(PublicConvoy_t *this)
{
    PublicTransport_Ctor(&this->PT);
    ((PublicTransport_t*)this)->vtable = PublicConvoy_vtable;

    this->m_pt1 = malloc(sizeof(Minibus_t));
    Minibus_Ctor(this->m_pt1);
    this->m_pt2 = malloc(sizeof(Taxi_t));
    Taxi_Ctor(this->m_pt2);

    Minibus_Ctor(&this->m_m);
    Taxi_Ctor(&this->m_t);
}

void PublicConvoy_Dtor(PublicConvoy_t *this)
{
    (void (*)(Minibus_t*))this->m_pt1->vtable[dtor]((Minibus_t*)this);
    free(this->m_pt1);

    (void (*)(Taxi_t*))this->m_pt2->vtable[dtor]((Taxi_t*)this);
    free(this->m_pt2);

    ((PublicTransport_t*)this)->vtable = PublicTransport_vtable;
    (void (*)(PublicTransport_t*))this->PT.vtable[dtor]((PublicTransport_t*)this);
}

void PublicConvoy_display_void(PublicConvoy_t *this)
{
    (void (*)(Minibus_t*))this->m_pt1->vtable[display]((Minibus_t*)this);   
    (void (*)(Taxi_t*))this->m_pt2->vtable[display]((Taxi_t*)this);   
    (void (*)(Minibus_t*))this->m_m.PT.vtable[display]((Minibus_t*)this);   
    (void (*)(Taxi_t*))this->m_t.PT.vtable[display]((Taxi_t*)this);   
}

/******************************************************************************/
/**** global functions ********************************************************/
/******************************************************************************/

void print_info_PublicTransport(PublicTransport_t *a)
{

}

void print_info_Void()
{

}

void print_info(Minibus_t *m)
{

}

PublicTransport_t print_info(PublicTransport_t *pt, int i)
{

}

void taxi_display(Taxi_t *s)
{

}

/******************************************************************************/
/**** main ********************************************************************/
/******************************************************************************/

int main()
{
    // Minibus m;
    // print_info(m);
    // print_info(3).display();
    // PublicTransport *array[] = { new Minibus(), new Taxi(), new Minibus() };

    // for (int i = 0; i < 3; ++i) {
    //     array[i]->display();
    // }

    // for (int i = 0; i < 3; ++i) {
    //     delete array[i];
    // }

    // PublicTransport arr2[] = { Minibus(), Taxi(), PublicTransport() };

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

    // return 0;
}