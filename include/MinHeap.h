#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_map>
#include <optional>
template <typename T, typename CompFuncT = std::less<T>>
class MinHeap {
    using IndexType = typename std::vector<T>::size_type;
    private:
        std::vector<T> container;
        std::unordered_map<T, IndexType> elem_to_index;
        CompFuncT comp_func;
        void bubble_up(IndexType i) {
            while (true) {
                std::optional<T> op_parent = get_parent(i);
                if (!op_parent.has_value()) {
                    return;
                }
                if (op_parent.value() > container[i]) {
                    swap(i, (i - 1) / 2);
                    i = (i - 1) / 2;
                } else {
                    return;
                }
            }
        };
        void sink_down(IndexType i) {
            while (true) {
                auto op_left = get_left_child(i);
                auto op_right = get_right_child(i);

                if (!op_left.has_value() and !op_right.has_value()) {
                    return;
                } else {
                    T min_child = op_left.value();
                    if (op_right.has_value()) {
                        if (op_right.value() < min_child) {
                            min_child = op_right.value();
                        }
                    }
                    if (min_child < container[i]) {
                        if (min_child == op_left.value()) {
                            swap(i, 2 * i + 1);
                            i = 2 * i + 1;
                        } else {
                            swap(i, 2 * i + 2);
                            i = 2 * i + 2;
                        }
                    } else {
                        return;
                    }
                }
            }
        };
        void swap(IndexType i, IndexType j) {
            if (i >= container.size() || j >= container.size()) {
                return;
            }
            if (i == j) {
                return;
            }
            auto temp = container[i];
            container[i] = container[j];
            container[j] = temp;

            elem_to_index.insert_or_assign(container[i], i);
            elem_to_index.insert_or_assign(container[j], j);
        };
        std::optional<T> get_left_child(IndexType i) {
            if (2 * i + 1 >= container.size()) {
                return std::optional<T>();
            }
            return std::optional(container[2 * i + 1]);
        };
        std::optional<T> get_right_child(IndexType i) {
            if (2 * i + 2 >= container.size()) {
                return std::optional<T>();
            }
            return std::optional(container[2 * i + 2]);
        };
        std::optional<T> get_parent(IndexType i) {
            if (i == 0) {
                return std::optional<T>();
            }
            return std::optional(container[(i - 1) / 2]);
        };
    public:
        MinHeap() : comp_func(std::less<T>()) {};
        MinHeap(CompFuncT comp_func) : comp_func(comp_func) {}; // pass in a functor

        std::optional<T> peek() {
            if (container.size() < 1) {
                return std::optional<T>();
            }
            return std::optional(container[0]);
        };
        std::optional<T> extract_min() {
            if (container.size() < 1) {
                return std::optional<T>();
            } 
            auto min_elem = container[0];
            swap(0, container.size() - 1);
            container.erase(container.end() - 1);
            elem_to_index.erase(min_elem);

            if (container.size() > 0) {
                sink_down(0);
            }
            return std::optional(min_elem);
        }
        void update_key(T old_elem, T new_elem) {
            IndexType i = elem_to_index[old_elem];
            container[i] = new_elem;
            elem_to_index.erase(old_elem);
            elem_to_index.insert(new_elem, i);
            if (new_elem > old_elem) {
                bubble_up(i);
            } else {
                sink_down(i);
            }
        }; // update old to new
        void push(T elem) {
            container.push_back(elem);
            elem_to_index.insert({elem, container.size() - 1});
            bubble_up(container.size() - 1);
        };
        IndexType size() {
            return container.size();
        };
};