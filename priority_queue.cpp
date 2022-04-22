#include "priority_queue.h"
#include<iostream>
#include<string>
node* add_in_priority(node* old_list, node * new_elem)
{
    node* temp = old_list;
    if (old_list)
    {
        if (old_list->frequency>= new_elem->frequency)
        {
            new_elem->next = old_list;
            return new_elem;
        }
        while ((old_list->next) && (old_list->next->frequency < new_elem->frequency))
        {
            old_list = old_list->next;
        }
        new_elem->next = old_list->next;
        old_list->next = new_elem;
        return temp;
    }
    return new_elem;

}
void print_all(node* list)
{
    if (list)
    {
        std::cout << list->frequency << " ";
        print_all(list->next);
    }
}

void change_code(node* tree,std::string add_str)
{
    if (tree)
    {
        change_code(tree->left,add_str);
        tree->bin_code = add_str + tree->bin_code;
        change_code(tree->right, add_str);
    }
}
node* make_sum(node* elem1, node* elem2)
{
    node* elem_res = new node();
    elem_res->letter_code = 0;
    elem_res->frequency = elem1->frequency + elem2->frequency;
    elem_res->left = elem1;
    change_code(elem_res->left,"0");
    elem_res->right = elem2;
    change_code(elem_res->right, "1");
    elem_res->next = 0;
    return elem_res;
}

node* make_tree_from_list(node* list)
{
    while (list->next)
    {
        node* new_sum = make_sum(list, list->next);
        list = list->next->next;
        list=add_in_priority(list, new_sum);
    }
    return list;
}
void get_code(node* list,std::string* arr)
{
    if (list)
    {
        get_code(list->left, arr);
        if (list->letter_code)
        {
            arr[list->letter_code] = list->bin_code;
        }
        get_code(list->right, arr);
    }
}
