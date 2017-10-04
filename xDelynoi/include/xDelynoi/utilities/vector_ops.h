#ifndef XDELYNOI_VECTOR_OPS_H
#define XDELYNOI_VECTOR_OPS_H

#include <vector>
#include <utilities/UniqueList.h>

namespace vector_ops{
    template <class T>
    std::vector<T> mergeVectors(std::vector<std::vector<T>> lists){
        UniqueList<T> result;

        for(std::vector<T> l: lists){
            result.push_list(l);
        }

        return result.getList();
    }

    template <class T>
    std::vector<T> difference(std::vector<T> list1, std::vector<T> list2){
        UniqueList<int> list;
        list.push_list(list1);

        for (T i: list2){
            list.delete_element(i);
        }

        return list.getList();
    }
}

#endif