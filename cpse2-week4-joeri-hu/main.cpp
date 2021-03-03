#include <set>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <algorithm>

using clist = std::vector<unsigned char>;

auto load_file(std::string const& filename) -> clist;
auto print_character_count(clist const& contents) -> void;
auto print_line_count(clist const& contents) -> void;
auto print_letter_count(clist const& contents) -> void;
auto print_letter_info(clist const& contents) -> void;
auto print_word_info(clist const& contents, int count = 10) -> void;

auto main() -> int {
    try {
        auto contents = load_file("10-0.txt");
        print_character_count(contents);
        print_line_count(contents);
        print_letter_count(contents);
        std::transform(contents.cbegin(), contents.cend(), contents.begin(), ::tolower);
        print_letter_info(contents);
        print_word_info(contents);
    } catch (std::runtime_error const& exc) {
        std::cerr << exc.what();
        return 1;
    } catch (std::exception const& exc) {
        std::cerr << "unexpected error occured: " << exc.what();
        return 2;
    }
    return 0;
}

auto load_file(std::string const& filename) -> clist {
    auto input = std::ifstream{filename, std::ios::binary | std::ios::ate};

    if (not input) {
        throw std::runtime_error("unable to open file: " + filename);
    }
    auto const end = input.tellg();
    input.seekg(0, std::ios::beg);
    auto const size = std::size_t(end - input.tellg());

    if (size == 0) {
        throw std::runtime_error("file appears to be empty: " + filename);
    }
    clist buffer(size);

    if (not input.read(reinterpret_cast<char*>(buffer.data()), buffer.size())) {
        throw std::runtime_error("unable to read from file: " + filename);
    }
    return buffer;
}

auto print_character_count(clist const& contents) -> void {
    std::cout << "character count: " << std::setw(8) << contents.size() << std::endl;
}

auto print_line_count(clist const& contents) -> void {
    auto const count = std::count_if(contents.cbegin(), contents.cend(),
        [](auto const symbol) {
            return symbol == '\n';
        });
    std::cout << "line count: " << std::setw(13) << count << std::endl;
}

auto print_letter_count(clist const& contents) -> void {
    auto const count = std::count_if(contents.cbegin(), contents.cend(), ::isalpha);
    std::cout << "letter count: " << std::setw(11) << count << std::endl;
}

auto print_letter_info(clist const& contents) -> void {
    std::map<unsigned char, int> letters;
    std::for_each(contents.cbegin(), contents.cend(), [&](auto const symbol) {
        if (std::isalpha(symbol)) {
            ++letters[symbol];
        }
    });
    std::set<std::pair<int, unsigned char>> sorted_letters;

    for (auto const [key, value] : letters) {
        std::cout << key << ':' << std::setw(23) << value << std::endl;
        sorted_letters.emplace(value, key);
    }
    for (auto const [value, key] : sorted_letters) {
        std::cout << key << ':' << std::setw(23) << value << std::endl;
    }
}

auto print_word_info(clist const& contents, int count) -> void {
    std::map<std::string, int> words;

    for (auto begin = contents.cbegin(); begin not_eq contents.cend();) {
        auto const end = find_if_not(begin, contents.cend(), ::isalpha);
        ++words[std::string(begin, end)];
        begin = find_if(end, contents.cend(), ::isalpha);
    }
    std::set<std::pair<int, std::string>> sorted_words;

    for (auto&& [key, value] : words) {
        sorted_words.emplace(value, std::move(key));
    }
    for (auto iter = sorted_words.crbegin(); iter not_eq sorted_words.crend(); ++iter) {
        if (--count < 0) {
            break;
        }
        std::cout << iter->second << ':' << std::setw(24 - iter->second.size())
            << iter->first << std::endl;
    }
}
