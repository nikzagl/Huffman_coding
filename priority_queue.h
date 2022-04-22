#pragma once
#include <string>
struct node
{
    int letter_code;
    int frequency;
    std::string bin_code;
    node* next, *left, *right;
};
node* add_in_priority(node* old_list, node* new_list);
node* make_tree_from_list(node* list);
void get_code(node* list, std::string* arr);
void print_all(node* list);