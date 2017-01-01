#include <stdio.h>
#include <curl/curl.h>

int square(int x)
{
        return x * 5;
}

int main()
{
        printf("%i\n", square(10));
        curl_global_init(CURL_GLOBAL_ALL);
        return 0;
}
