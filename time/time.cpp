int TestTime()
{
    // 获取当前时间的 UTC 秒数.
    time_t now;
    time(&now);

    std::cout << "now: " << now << std::endl;

    auto PrintDate = [](struct tm* ttm,const char* key)->char*{
        char buf[32] = {0};
        sprintf(buf, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d", ttm->tm_year+1900,
                ttm->tm_mon + 1, ttm->tm_mday, ttm->tm_hour, ttm->tm_min,
                ttm->tm_sec);
        std::cout <<  key  <<" date: " << buf << std::endl;
        return strdup(buf);
    };

    // 把UTC时间转换为 tm 结构体, 注意不是本地时间，是世界统一时间，全时间的时间都一样.
    struct tm utc_tm1 = *gmtime(&now);
    auto utc_str = PrintDate(&utc_tm1,"utc");

    // 本地日期, 也就是当前时区的日期.
    auto local_t1 = localtime(&now);
    PrintDate(local_t1,"local");

    // 知道UTC的日期转换为本地日期
    time_t tt = _mkgmtime64(&utc_tm1);
    auto local_t2 = localtime(&tt);
    PrintDate(local_t2,"utc->local");

    // 知道本地日期转换为UTC日期
    auto utc_time = mktime(local_t1);
    auto ttm1 = gmtime(&utc_time);
    PrintDate(ttm1,"local->utc");

    return 0;
}
