/*
This file is part of Ionlib.  Copyright (C) 2016  Tim Sweet

Ionlib is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Ionlib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Ionlib.If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ION_QUEUE_H_
#define ION_QUEUE_H_
#include "error.h"

namespace ion
{
    //This queue is only threadsafe with one producer and one consumer
    template <class T, uint32_t QUEUE_LEN>
    class Queue
    {
    public:
        Queue() : max_capacity_(QUEUE_LEN+1)
        {
            while (max_capacity_ == 0); //this is an error
            head_ = 0;
            tail_ = 0;
            push_drops_ = 0;
            pop_waits_ = 0;
            memset(queue_, 0xFFFFFFFF, sizeof(T) * max_capacity_);
        }
        void Push(T& data)
        {
            if (head_ < tail_)
            {
                if (tail_ - head_ == 1) //This is a simplified version of: head + capacity - tail == capacity-1
                {
                    //discard the data
                    return;
                }
            } else if ((head_ - tail_) == (max_capacity_ - 1))
            {
                //discard the data
                push_drops_++;
                return;
            }
            queue_[head_] = data;
            head_ = (head_ + 1);
            if (head_ == max_capacity_)
            {
                head_ = 0;
            }
        }
        void Pop(T* item = nullptr)
        {
            //check if the queue is empty
            uint32_t unwrapped_head = head_;
            bool waited = false;
            if (head_ < tail_)
            {
                //the cursors wrapped around, so make a logical cursor which simulates the queue being of infinite length
                unwrapped_head += max_capacity_;
            }
            max_depth_ = max(unwrapped_head - tail_,max_depth_);
            while (head_ == tail_)
            {
                if (!waited)
                {
                    waited = true;
                    pop_waits_++;
                    Serial.print("Frame: ");
                    Serial.print(*item);
                    Serial.print(" push_drops: ");
                    Serial.print(push_drops_);
                    Serial.print(" pop_waits: ");
                    Serial.println(pop_waits_);
                }
                //Serial.print("head==tail: ");
                //Serial.print(head_);
                //Serial.print("count=");
                //Serial.println(unwrapped_head - tail_);
            }
            if (item)
            {
                *item = queue_[tail_];
            }

            tail_ =(tail_ + 1) % max_capacity_;

        }
        size_t size()
        {
            return head_ - tail_;
        }
    private:
        T queue_[QUEUE_LEN+1];
        uint16_t max_capacity_;
    public:
        volatile uint16_t head_; //The next index to be written
        uint16_t tail_; //The next index to be read
        uint16_t max_depth_; //The fullest the queue has ever been, according to pop
        uint32_t push_drops_;
        uint32_t pop_waits_;
    };
};
#endif //ION_QUEUE_H_