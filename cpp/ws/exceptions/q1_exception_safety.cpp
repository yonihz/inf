void Foo(boolean goKaboomEarly)
{
    int *arr1 = new int[10];

    if (goKaboomEarly)
    {
        Bar(arr1);
    }

    int *arr2 = new int[100];

    Fishi();
    Bar(arr2);
    Dodo();

    delete[] arr2;
    delete[] arr1;
}