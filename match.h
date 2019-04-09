// from Ben Deane, scraped from Compiler Exploror April 9 2019.
// All his oen work!
//
#include <utility>

using parse_result_t = std::pair<bool, const char*>;

template <auto Low, auto High>
constexpr auto range_matcher = [] (const char *c) -> parse_result_t {
    if (*c >= Low and *c <= High)
        return {true, ++c};
    return {false, c};
};

constexpr auto end_matcher = [] (const char *c) -> parse_result_t {
    return {*c == 0, c};
};

constexpr auto many = [] (auto&& p) {
    return [p = std::forward<decltype(p)>(p)] (const char* c) -> parse_result_t {
        while (true) {
            const auto result = p(c);
            if (not result.first) return {true, c};
            c = result.second;
        };
    };
};

constexpr auto many1 = [] (auto&& p) {
    return [p = std::forward<decltype(p)>(p)] (const char* c) -> parse_result_t {
        const auto start = c;
        const auto result = many(p)(c);
        return {start < result.second, result.second};
    };
};

constexpr auto sequence = [] (auto&& p1, auto&& p2) {
    return [p1 = std::forward<decltype(p1)>(p1), 
            p2 = std::forward<decltype(p2)>(p2)] (const char* c) -> parse_result_t {
        const auto result = p1(c);
        if (not result.first) return {false, c};
        return p2(result.second);
    };
};

//constexpr
bool match(const char* c)
{
    constexpr auto alpha_matcher = range_matcher<'a', 'z'>;
    constexpr auto digit_matcher = range_matcher<'0', '9'>;
    constexpr auto parser = sequence(many1(alpha_matcher), 
                                     many1(digit_matcher));
    return sequence(parser, end_matcher)(c).first;
}

/*
static_assert(match("az09"));
static_assert(match("abc0"));
static_assert(match("a123"));

static_assert(!match(""));
static_assert(!match("a"));
static_assert(!match("0"));
static_assert(!match("a0a"));
static_assert(!match("a/0"));
static_assert(!match("/a0"));
static_assert(!match("a0/"));
*/
