#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cstring>

// структуру ListNode модифицировать нельзя
struct ListNode {
    ListNode *prev;
    ListNode *next;
    ListNode *rand;
    std::string data;
};

// Simple struct for serialize
struct SerializeNode{
    size_t size;
    char* data;
    int ref;
};

class List {
public:
    void Serialize(FILE *file)
    {
        if (file == nullptr)
            return;

        std::unordered_map<ListNode*, int> indexes;
        auto iter {this->head};
        for (auto i {0}; i < this->count; ++i)
        {
            indexes.insert({iter, i});
            iter = iter->next;
        }

        iter = this->head;
        auto* serialize_array {new SerializeNode[this->count]};
        for(auto i {0}; i < count; ++i)
        {
            size_t len = iter->data.length() + 1;
            auto array = strcpy(new char[len], iter->data.c_str());
            std::copy(std::begin(iter->data), std::end(iter->data), array);

            if (iter->rand == nullptr)
            {
                serialize_array[i] = {len, array, -1};
            }
            else
            {
                auto find_iter = std::find_if(std::begin(indexes), std::end(indexes), [&iter](auto& elem){
                    return elem.first->data == iter->rand->data && elem.first->prev == iter->rand->prev;
                });
                serialize_array[i] = {len, array, find_iter->second};
            }
            iter = iter->next;
        }

        fwrite(&this->count, sizeof(int), 1, file);
        for (auto i {0}; i < this->count; ++i)
        {
            fwrite(&serialize_array[i].size, sizeof(size_t), 1, file);
            fwrite(serialize_array[i].data, sizeof(char), serialize_array[i].size, file);
            fwrite(&serialize_array[i].ref, sizeof(int), 1, file);
        }

        for(auto i {0}; i < count; ++i)
            delete[] serialize_array[i].data;
        delete[] serialize_array;
    }
    void Deserialize(FILE *file)
    {
        if (file == nullptr)
            return;

        fread(&this->count, sizeof(int), 1, file);

        auto iters = new ListNode*[this->count];
        auto* serialize_array = new SerializeNode[this->count];
        for (auto i {0}; i < this->count; ++i)
        {
            fread(&serialize_array[i].size, sizeof(size_t), 1, file);
            serialize_array[i].data = new char[serialize_array[i].size];
            fread(serialize_array[i].data, sizeof(char), serialize_array[i].size, file);
            fread(&serialize_array[i].ref, sizeof(int), 1, file);
        }

        this->head = new ListNode;
        this->head->data = serialize_array[0].data;
        this->head->prev = nullptr;
        iters[0] = this->head;
        auto iter {this->head};
        for(auto i {1}; i < this->count; ++i)
        {
            iter->next = new ListNode{iter, nullptr, nullptr, serialize_array[i].data};
            iter = iter->next;
            iters[i] = iter;
        }
        this->tail = iter;
        iter = this->head;
        for(auto i {0}; i < this->count; ++i)
        {
            if (serialize_array[i].ref != -1)
            {
                iter->rand = iters[serialize_array[i].ref];
            }
            else
            {
                // do nothing
            }
            iter = iter->next;
        }
        for (auto i {0}; i < this->count; ++i)
            delete[] serialize_array[i].data;
        delete[] iters;
    }

private:
    ListNode *head;
    ListNode *tail;
    int count;
};