#include <iostream>
#include <fstream>
#include <vector>
#include <parallel/algorithm>
#include <parallel/numeric>
#include <algorithm>
#include <execution>
#include <ranges>

using namespace std;

int getLineCount(const string &file_name);

template <std::ranges::range R>
constexpr auto
to_vector(R &&r){
    using elem_t = std::decay_t<std::ranges::range_value_t<R>>;
    return vector<elem_t>{r.begin(),r.end()};
}

auto
count_lines_imperative(vector<string> file_names){
    vector<int> line_counts; // local/global state
    for (auto& file_name : file_names){ // external loop
        int line_count = getLineCount(file_name);
        line_counts.push_back(line_count); // mutate state
    }
    return line_counts;
}

auto
count_lines_declarative(vector<string> file_names)  {
    vector<int> line_counts(file_names.size()); // local/global state
    // internal loop, higher-order function
    transform(execution::par,file_names.begin(),file_names.end(),line_counts.begin(),getLineCount);
    return line_counts;
}

int getLineCount(const string &file_name) {
    ifstream  input_file(file_name);
    char c;
    auto line_count = 0; // state
    while (input_file.get(c)){ // loop
        if (c== '\n')
            line_count++; // mutate state
    }
    return line_count;
}

struct topla { // function -> operator()
    int operator() (int x,int y){
        return x+y;
    }
};

auto
fun(int x,int y){
    return x+y;
}

auto
open_file(const string& file){
    cout << "open_file(" << file << ")" << endl;
    return ifstream(file);
}

int
count_lines_in_file(ifstream input_file){
    cout << "count_lines_in_file()" << endl;
    return count(istreambuf_iterator<char>(input_file),istreambuf_iterator<char>(),'\n');
}

auto
count_lines_declarative_ranges(vector<string> &files){
    // vector<string> -> vector<ifstream> -> vector<int>
    return to_vector(
            // 1-PASS
            files | std::ranges::views::transform(open_file) // vector<string> -> vector<ifstream>
                    | std::ranges::views::transform(count_lines_in_file) // vector<ifstream> -> vector<int>
            );
    // ranges (c++) -> C# LINQ -> Java Stream API
    // HoF -> Filter/Map (transform)/ Reduce (accumulate)

    // python, js -> generator function
}

int main() {
    vector<string> files{
        string("c:\\tmp\\dictionary-eng.txt"),
        string("c:\\tmp\\dictionary-tur.txt"),
        string("c:\\tmp\\cluster-info.txt"),
        string("c:\\tmp\\algotrading-market-apis.txt"),
        string("c:\\tmp\\war-and-peace.txt")
    };
    // imperative programming: procedural (like in C), or oop (like c++)
    auto total_line_count = 0; // local/global state
    // external loop
    for (auto& line_count : count_lines_imperative(files)){
        total_line_count += line_count; // state mutation
    }
    cout << "total line count: " << total_line_count << endl;

    // declarative programming: functional programming (since c++11)
    auto count_lines = count_lines_declarative(files);
    // internal loop,  I) higher-order function,
    //                II) pure functions:
    //                     i) c-like function
    //                    ii) lambda expression -> function object
    //                   iii) function object
    total_line_count = accumulate(count_lines.begin(),count_lines.end(),0,
                                  [](auto acc,auto count){
                                            return acc+count;
                                           }
                                  );
    total_line_count = accumulate(count_lines.begin(),count_lines.end(),int(), topla());
    total_line_count = accumulate(count_lines.begin(),count_lines.end(),int(), plus<int>());
    total_line_count = accumulate(count_lines.begin(),count_lines.end(),int(), fun);
    cout << "total line count: " << total_line_count << endl;
    // declarative programming
    auto line_counts = count_lines_declarative_ranges(files);
    total_line_count = accumulate(line_counts.begin(),line_counts.end(),int(), fun);
    cout << "total line count: " << total_line_count << endl;
    return 0;
}
