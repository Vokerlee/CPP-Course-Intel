#include "../include/2q_cache.hpp"
#include "../include/cache_test.hpp"

int main()
{
    size_t size = 10;

    cch::Cache_2Q<int> cache(size);

    cch::CacheTest<int> test(size);

    //test.print_data();
    test.fill_cache(cache);
    test.test_cache(cache);


    return 0;
}