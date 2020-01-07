#define UNUSED(x) (void)(x)

typedef struct List List;
typedef struct Person Person;

struct Person { int age; };
struct List { };

void *ll_find(List* ll, int key);

void Foo(List* ll, int key, int age)
{
    void *vv = ll_find(ll, key);
    // Person *p = (Person*)ll;
    Person *p = static_cast<Person*>(ll);
    p->age = age;
}

void *ll_find(List* ll, int key)
{
    UNUSED(ll);
    UNUSED(key);

    return ll;
}

int main()
{

}