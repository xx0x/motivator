byte numPlaces(unsigned long n)
{
    if (n < 0)
        return numPlaces((n == LONG_MIN) ? LONG_MAX : -n);
    if (n < 10)
        return 1;
    return 1 + numPlaces(n / 10);
}