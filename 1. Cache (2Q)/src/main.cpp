#include "../include/2q_cache.hpp"
#include "../include/cache_test.hpp"

int main()
{
    //cch::CacheTest<int> test(1000000);
    //cch::Cache_2Q<int> cache(2000);

    //test.print_data();
    //test.test_cache(cache);

    //cache.print();

    size_t cache_size = 0;
    size_t n_tests    = 0;
    
    std::cin >> cache_size;
    std::cin >> n_tests;

    cch::Cache_2Q<int> cache(cache_size);
    int test_id = 0;
    int n_hits  = 0;

    for (size_t i = 0; i < n_tests; ++i)
    {
        std::cin >> test_id;
        n_hits += cache.handle_page(test_id);
    }

    std::cout << n_hits << std::endl;


    return 0;
}