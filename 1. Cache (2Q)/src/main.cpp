#include "../include/2q_cache.hpp"
#include "../include/cache_test.hpp"

//#define GENERATE_TEST

int main()
{

#ifdef GENERATE_TEST
    cch::CacheTest<int> test(10000, 800);
    cch::Cache_2Q<int>  cache(800);

    std::ofstream fout;
    fout.open("../tests/10k.txt");

    //test.print_data();
    test.test_cache(cache);
    test.print_test_file(cache, fout);

    //cache.print();

    fout.close();

#else

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

    std::cout << "=======================================";
    std::cout << std::endl << "Test started:" << std::endl;

    std::cout << n_hits <<  "  hits" << std::endl;
    std::cout << n_tests << " tests" << std::endl;

#endif

    return 0;
}
