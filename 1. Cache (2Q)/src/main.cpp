#include "2q_cache.hpp"

//#define LOG_ON

int main()
{

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
        n_hits += cache.handle_page(cch::Page<int>(test_id));     
    }

    std::cout << n_hits << std::endl;

#ifdef LOG_ON

    auto now       = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %r");

    std::ofstream log;
    log.open("cache_log " + ss.str());

    cache.dump(log);

    log.close();

#endif

    return 0;
}
