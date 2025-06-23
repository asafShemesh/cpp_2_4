// asaf0604@gmail.com    325362457
#pragma once

#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <memory>

namespace ariel
{

    /**
     * @brief A generic container class that supports various iteration orders.
     *
     * @tparam T Type of elements stored in the container.
     */
    template <typename T>
    class MyContainer
    {
    private:
        std::vector<T> data;

    public:
        /**
         * @brief Add an element to the container.
         *
         * @param val Element to add.
         */
        void addElement(const T &val)
        {
            data.push_back(val);
        }

        /**
         * @brief Remove an element from the container.
         *
         * @param val Element to remove.
         * @throws std::runtime_error if element is not found.
         */
        void removeElement(const T &val)
        {
            auto it = std::find(data.begin(), data.end(), val);
            if (it != data.end())
                data.erase(it);
            else
                throw std::runtime_error("Element not found");
        }

        /**
         * @brief Get the number of elements in the container.
         *
         * @return size_t Number of elements.
         */
        size_t size() const { return data.size(); }

        /**
         * @brief Get the internal data vector (read-only).
         *
         * @return const std::vector<T>& Reference to the data vector.
         */
        const std::vector<T> &get_data() const { return data; }

        // ----------- Iterator classes and methods ----------- //

        /**
         * @brief Iterator over elements in ascending order.
         */
        class AscendingOrder
        {
            std::shared_ptr<std::vector<T>> sorted;
            size_t index;

        public:
            AscendingOrder(const MyContainer &c, bool end = false)
            {
                sorted = std::make_shared<std::vector<T>>(c.data);
                std::sort(sorted->begin(), sorted->end());
                index = end ? sorted->size() : 0;
            }
            T operator*() const { return sorted->at(index); }
            AscendingOrder &operator++()
            {
                ++index;
                return *this;
            }
            bool operator!=(const AscendingOrder &other) const { return index != other.index; }

            bool operator==(const AscendingOrder &other) const
            {
                return index == other.index;
            }
        };
        AscendingOrder begin_ascending_order() const { return AscendingOrder(*this, false); }
        AscendingOrder end_ascending_order() const { return AscendingOrder(*this, true); }

        /**
         * @brief Iterator over elements in descending order.
         */
        class DescendingOrder
        {
            std::shared_ptr<std::vector<T>> sorted;
            size_t index;

        public:
            DescendingOrder(const MyContainer &c, bool end = false)
            {
                sorted = std::make_shared<std::vector<T>>(c.data);
                std::sort(sorted->begin(), sorted->end(), std::greater<T>());
                index = end ? sorted->size() : 0;
            }
            T operator*() const { return sorted->at(index); }
            DescendingOrder &operator++()
            {
                ++index;
                return *this;
            }
            bool operator!=(const DescendingOrder &other) const { return index != other.index; }
        };
        DescendingOrder begin_descending_order() const { return DescendingOrder(*this, false); }
        DescendingOrder end_descending_order() const { return DescendingOrder(*this, true); }

        /**
         * @brief Iterator that alternates from smallest to largest (cross pattern).
         */
        class SideCrossOrder
        {
            std::shared_ptr<std::vector<T>> cross;
            size_t index;

        public:
            SideCrossOrder(const MyContainer &c, bool end = false)
            {
                std::vector<T> sorted = c.data;
                std::sort(sorted.begin(), sorted.end());
                cross = std::make_shared<std::vector<T>>();
                size_t left = 0, right = sorted.size() - 1;
                while (left <= right)
                {
                    if (left == right)
                        cross->push_back(sorted[left]);
                    else
                    {
                        cross->push_back(sorted[left]);
                        cross->push_back(sorted[right]);
                    }
                    ++left;
                    --right;
                }
                index = end ? cross->size() : 0;
            }
            T operator*() const { return cross->at(index); }
            SideCrossOrder &operator++()
            {
                ++index;
                return *this;
            }
            bool operator!=(const SideCrossOrder &other) const { return index != other.index; }
        };
        SideCrossOrder begin_side_cross_order() const { return SideCrossOrder(*this, false); }
        SideCrossOrder end_side_cross_order() const { return SideCrossOrder(*this, true); }

        /**
         * @brief Iterator in reverse (insertion) order.
         */
        class ReverseOrder
        {
            std::shared_ptr<std::vector<T>> reversed;
            size_t index;

        public:
            ReverseOrder(const MyContainer &c, bool end = false)
            {
                reversed = std::make_shared<std::vector<T>>(c.data);
                std::reverse(reversed->begin(), reversed->end());
                index = end ? reversed->size() : 0;
            }
            T operator*() const { return reversed->at(index); }
            ReverseOrder &operator++()
            {
                ++index;
                return *this;
            }
            bool operator!=(const ReverseOrder &other) const { return index != other.index; }
        };
        ReverseOrder begin_reverse_order() const { return ReverseOrder(*this, false); }
        ReverseOrder end_reverse_order() const { return ReverseOrder(*this, true); }

        /**
         * @brief Iterator in original insertion order.
         */
        class Order
        {
            std::shared_ptr<std::vector<T>> ref;
            size_t index;

        public:
            Order(const MyContainer &c, bool end = false)
            {
                ref = std::make_shared<std::vector<T>>(c.data);
                index = end ? ref->size() : 0;
            }
            T operator*() const { return ref->at(index); }
            Order &operator++()
            {
                ++index;
                return *this;
            }
            bool operator!=(const Order &other) const { return index != other.index; }
        };
        Order begin_order() const { return Order(*this, false); }
        Order end_order() const { return Order(*this, true); }

        /**
         * @brief Iterator that starts from the middle and moves outward: middle, outermost right, outermost left, etc.
         */
        class MiddleOutOrder
        {
            std::shared_ptr<std::vector<T>> middle;
            size_t index;

        public:
            MiddleOutOrder(const MyContainer &c, bool end = false)
            {
                std::vector<T> sorted = c.data;
                std::sort(sorted.begin(), sorted.end());
                middle = std::make_shared<std::vector<T>>();

                int n = sorted.size();
                int mid = n / 2;
                middle->push_back(sorted[mid]);

                for (int offset = 1; mid - offset >= 0 || mid + offset < n; ++offset)
                {
                    if (mid + offset < n)
                        middle->push_back(sorted[n - offset]);
                    if (mid - offset >= 0)
                        middle->push_back(sorted[offset - 1]);
                }

                index = end ? middle->size() : 0;
            }
            T operator*() const { return middle->at(index); }
            MiddleOutOrder &operator++()
            {
                ++index;
                return *this;
            }
            bool operator!=(const MiddleOutOrder &other) const { return index != other.index; }
        };
        MiddleOutOrder begin_middle_out_order() const { return MiddleOutOrder(*this, false); }
        MiddleOutOrder end_middle_out_order() const { return MiddleOutOrder(*this, true); }
    };

}
